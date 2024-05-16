#include "engine.grpc.pb.h"
#include "engine.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class EngineServiceImpl final : public enginePackage::Engine::Service {
    Status placeCard(ServerContext *context, const enginePackage::idInfo *request,
                     enginePackage::answer *response) override {
        // Implement your logic here to handle the placeCard RPC
        // For example:
        std::cout << "Received placeCard request" << std::endl;

        // Example response
        response->set_answer(true);

        return Status::OK;
    }
};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    EngineServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char **argv) {
    RunServer();
    return 0;
}
