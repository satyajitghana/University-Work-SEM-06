#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>

#include "zirconiumbank.grpc.pb.h"

// gRPC namespaces
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

// zirconium grpc-proto namespaces
using zirconium::bank::WebService;
using zirconium::bank::AuthUser;
using zirconium::bank::RequestAmount;
using zirconium::bank::Balance;

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

        ClientContext context;

        // The actual RPC
        Status status = stub_->BalanceEnquiry(&context, authuser_req, &balance_res);

        if (status.ok()) {
            return std::string("user: " + user + ": balance = " + std::to_string(balance_res.value()));
        } else {
            std::cerr << status.error_code() << ": " << status.error_message() << "\n";
            return "RPC failed";
        }
    }

    private:
    std::unique_ptr<WebService::Stub> stub_;
};

int main(int argc, char* argv[]) {
    std::string server_addr("localhost:50051");
    ZirconiumClient zirconium_bank(grpc::CreateChannel(server_addr, grpc::InsecureChannelCredentials()));

    std::string user("shadowleaf");
    std::string pin("123456");

    std::string reply = zirconium_bank.BalanceEnquiry(user, pin);

    std::cout << reply << "\n";

    return 0;
}
