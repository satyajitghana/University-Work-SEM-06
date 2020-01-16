#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "zirconiumbank.grpc.pb.h"

// gRPC namespaces
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

// zirconium grpc-proto namespaces
using zirconium::bank::AuthUser;
using zirconium::bank::Balance;
using zirconium::bank::RequestAmount;
using zirconium::bank::WebService;

class WebServiceImpl final : public WebService::Service {
    Status BalanceEnquiry(ServerContext* context, const AuthUser* auth_user, Balance* balance) override {
        std::cout << "AuthUser [ username: " << auth_user->username() << ", pin: " << auth_user->pin() << " ]" << "\n";
        balance->set_value(100);
        return Status::OK;
    }
};

void RunServer(const std::string& server_addr) {
    WebServiceImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_addr << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char* argv[]) {
    std::string server_addr("0.0.0.0:50051");

    RunServer(server_addr);

    return 0;
}