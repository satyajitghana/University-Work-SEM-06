#include <iostream>
#include <memory>
#include <sstream>
#include <string>
// #include <filesystem>

#include <grpcpp/grpcpp.h>

#include "cxxopts.hpp"
// to use c++ style logging
// specifically define this before including loguru.hpp
#define LOGURU_WITH_STREAMS 1

#include "loguru.hpp"
#include "zirconiumbank.grpc.pb.h"

// gRPC namespaces
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

// zirconium grpc-proto namespaces
using zirconium::bank::AuthUser;
using zirconium::bank::Balance;
using zirconium::bank::RequestAmount;
using zirconium::bank::TransferReq;
using zirconium::bank::WebService;

class ZirconiumClient {
   public:
    ZirconiumClient(std::shared_ptr<Channel> channel) : stub_(WebService::NewStub(channel)) {}

    std::string BalanceEnquiry(const std::string& user, const std::string& pin) {
        // Data that we will send to the server
        AuthUser authuser_req;
        authuser_req.set_username(user);
        authuser_req.set_pin(pin);

        // The Response we will get
        Balance balance_res;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        ClientContext context;

        // The actual RPC
        Status status = stub_->BalanceEnquiry(&context, authuser_req, &balance_res);

        return getResponse_(status, user, balance_res);
    }

    std::string UpdateAmount(const std::string& user, const std::string& pin, int update_amt) {
        // the despoit amount request
        RequestAmount update_amt_req;

        LOG_IF_S(WARNING, update_amt == 0) << "update amount = 0";

        LOG_IF_S(WARNING, update_amt < 0) << "Debit Req of Amount: " << update_amt;
        LOG_IF_S(WARNING, update_amt > 0) << "Credit Req of Amount: " << update_amt;

        // create the request payload
        update_amt_req.mutable_user()->set_username(user);
        update_amt_req.mutable_user()->set_pin(pin);
        update_amt_req.set_value(update_amt);

        // The Response we will get
        Balance balance_res;

        ClientContext context;

        // The DepositAmount RPC
        Status status = stub_->UpdateAmount(&context, update_amt_req, &balance_res);

        return getResponse_(status, user, balance_res);
    }

   private:
    std::unique_ptr<WebService::Stub> stub_;

    ClientContext ctx;

    std::string getResponse_(Status status, std::string user, Balance balance_res) {
        if (status.ok()) {
            std::stringstream response;
            response << "STATUS OK [ user: " << user << ", balance: " << std::to_string(balance_res.value()) << " ]";
            LOG_S(INFO) << response.str() << "\n";

            return response.str();
        } else {
            std::stringstream response;
            response << "RPC FAILED [ " << status.error_code() << ": " << status.error_message();

            LOG_S(ERROR) << response.str() << "\n";

            return response.str();
        }
    }
};

int main(int argc, char* argv[]) {
    // turn off the printing thread info in the output
    loguru::g_preamble_thread = false;

    // turn off the uptime in the output
    loguru::g_preamble_uptime = false;

    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint (in this case,
    // localhost at port 50051). We indicate that the channel isn't authenticated
    // (use of InsecureChannelCredentials()).
    std::string server_addr("localhost:50051");
    ZirconiumClient zirconium_bank(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()));

    try {
        cxxopts::Options options("zirconium_client", "A client for Zirconium Bank");

        options
            .positional_help("[optional args]")
            .show_positional_help();

        options.allow_unrecognised_options()
            .add_options()("username", "username", cxxopts::value<std::string>())("pin", "PIN", cxxopts::value<std::string>())("withdraw", "Withdraw a given amount", cxxopts::value<int>()->implicit_value("0"))("deposit", "Deposit a given amount", cxxopts::value<int>()->implicit_value("0"))("balance_enquiry", "Balance Enquiry", cxxopts::value<bool>()->implicit_value("true"))("d,debug", "enable debugging")("h,help", "print help");

        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << "\n";
            exit(0);
        }

        // check if the username or the pin is not given as argument
        if (!(result.count("username") and result.count("pin"))) {
            LOG_S(ERROR) << "username or pin not given"
                         << "\n";
            exit(1);
        }

        // get the given values from the arguments
        std::string username = result["username"].as<std::string>();
        std::string pin = result["pin"].as<std::string>();

        // check if the strings are empty
        if (username.empty() or pin.empty()) {
            LOG_S(ERROR) << "username or pin empty"
                         << "\n";
            exit(1);
        }

        // the username and pin is provided properly

        if (result.count("deposit")) {
            // the deposit amount
            int dep_amt = result["deposit"].as<int>();
            std::string reply = zirconium_bank.UpdateAmount(username, pin, dep_amt);
        }

        if (result.count("withdraw")) {
            // the withdraw amount
            int with_amt = result["withdraw"].as<int>();
            std::string reply = zirconium_bank.UpdateAmount(username, pin, -with_amt);
        }

        if (result["balance_enquiry"].as<bool>()) {
            std::string reply = zirconium_bank.BalanceEnquiry(username, pin);
        }

    } catch (const cxxopts::OptionException& e) {
        LOG_S(ERROR) << "error parsing options: " << e.what() << "\n";
        exit(1);
    }

    return 0;
}
