#include <grpcpp/grpcpp.h>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <iostream>
#include <memory>
#include <mongocxx/client.hpp>
#include <mongocxx/exception/operation_exception.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <string>

#include "zirconiumbank.grpc.pb.h"

// to use c++ style logging
// specifically define this before including loguru.hpp
#define LOGURU_WITH_STREAMS 1

#include "loguru.hpp"

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

// gRPC namespaces
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::StatusCode;

// zirconium grpc-proto namespaces
using zirconium::bank::AuthUser;
using zirconium::bank::Balance;
using zirconium::bank::RequestAmount;
using zirconium::bank::TransferReq;
using zirconium::bank::WebService;

class WebServiceImpl final : public WebService::Service {
    /**
     * BalanceEnquiry: Gets the balance of a AuthUser
    */
    Status BalanceEnquiry(ServerContext* context, const AuthUser* auth_user, Balance* balance) override {
        // log the auth data from the request
        logAuthData_(auth_user->username(), auth_user->pin());

        // check if the user is authenticated and also fetch the document
        auto [is_authenticated, user] = getAuthData_(auth_user->username(), auth_user->pin());

        if (not is_authenticated) {
            LOG_S(WARNING) << "UNAUTHENTICATED User: " << auth_user.username();
            return Status(StatusCode::UNAUTHENTICATED, "username or pin wrong!");
        }

        // the user is authenticated

        balance->set_value(user->view()["balance"].get_int32());

        return Status::OK;
    }

    /**
     * UpdateAmount : updates the balance of the user with the given amount
    */
    Status UpdateAmount(ServerContext* context, const RequestAmount* update_req, Balance* balance) override {
        const auto auth_user = update_req->user();

        logAuthData_(auth_user.username(), auth_user.pin());

        auto [is_authenticated, user] = getAuthData_(auth_user.username(), auth_user.pin());

        if (not is_authenticated) {
            LOG_S(WARNING) << "UNAUTHENTICATED User: " << auth_user.username();
            return Status(StatusCode::UNAUTHENTICATED, "username or pin wrong!");
        }

        // the user is authenticated

        // create a session and start a transaction
        auto session = client_.start_session();

        session.start_transaction();

        try {
            // update the balance
            auto result = db_["bank"].find_one_and_update(
                user->view(),
                document{} << "$set"
                           << open_document
                           << "balance"
                           << (user->view()["balance"].get_int32() + update_req->value())
                           << close_document
                           << finalize,
                mongocxx::options::find_one_and_update());

            if (not result) {
                return Status(StatusCode::INTERNAL, "Internal Server Error, Cannot Deposit");
            }
        } catch (const mongocxx::operation_exception& oe) {
            LOG_S(ERROR) << "caught error during transaction, aborting";
            session.abort_transaction();
        }

        // commit with retry transaction
        while (true) {
            try {
                session.commit_transaction();
                LOG_S(INFO) << "Transaction commited !";
                break;
            } catch (const mongocxx::operation_exception& oe) {
                // can retry commit
                if (oe.has_error_label("UnknownTransactionCommitResult")) {
                    LOG_S(WARNING) << "UnknownTransactionCommitResult Retrying . . .";
                    continue;
                } else {
                    LOG_S(ERROR) << "Error during commit: " << oe.what();
                    break;
                }
            }
        }

        // fix this, don't do this fix above to return the updated document
        // get the updated document
        auto temp = db_["bank"].find_one(document{} << "username" << auth_user.username() << finalize);

        balance->set_value(temp->view()["balance"].get_int32());

        LOG_S(INFO) << "UPDATED: " << bsoncxx::to_json(*temp) << "\n";

        return Status::OK;
    }

    Status TransferAmount(ServerContext* context, const TransferReq* transfer_req, Balance* balance) override {
        return Status::OK;
    }

   public:
    void initiaize(mongocxx::client client) {
        db_ = client["zirconium"];
        client_ = std::move(client);
    };

   private:
    mongocxx::database db_;
    mongocxx::client client_;

    void logAuthData_(std::string user, std::string pin) {
        LOG_S(INFO) << "Received AuthUser: [ username: " << user << ", pin: " << pin << " ]"
                    << "\n";
    }

    std::tuple<bool, bsoncxx::stdx::optional<bsoncxx::document::value>> getAuthData_(std::string username, std::string pin) {
        bool is_authenticated = false;
        bsoncxx::stdx::optional<bsoncxx::document::value> user = db_["bank"].find_one(document{} << "username" << username << finalize);

        if (user) {
            LOG_S(INFO) << "FOUND USER FROM DB: " << bsoncxx::to_json(*user) << "\n";
            if (pin == user->view()["pin"].get_utf8().value.to_string()) {
                is_authenticated = true;
            }
        } else {
            LOG_S(ERROR) << username << " not found !"
                         << "\n";
        }

        return std::make_tuple(is_authenticated, user);
    }
};

void RunServer(const std::string& server_addr, mongocxx::client& client) {
    WebServiceImpl service;

    // initialize the service with mongo db name "zirconium"
    service.initiaize(std::move(client));

    ServerBuilder builder;

    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());

    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);

    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    LOG_S(INFO) << "Server listening on " << server_addr << "\n";

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char* argv[]) {
    // turn off the printing thread info in the output
    loguru::g_preamble_thread = false;

    // turn off the uptime in the output
    loguru::g_preamble_uptime = false;

    // instantiate the mongo connection
    mongocxx::instance instance{};  // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    mongocxx::client client(uri);

    if (not client) {
        LOG_S(FATAL) << "Couldn't connect to DB !";
        return EXIT_FAILURE;
    } else {
        LOG_S(INFO) << "Connected to DB: "
                    << "mongodb://localhost:27017";
    }

    std::string server_addr("0.0.0.0:50051");

    RunServer(server_addr, client);

    return 0;
}