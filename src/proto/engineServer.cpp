#include <iostream>
#include <grpcpp/grpcpp.h>
#include "engine.pb.h"
#include "engine.grpc.pb.h"
#include "engineClient.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class SlaveServerEngineClient {
    public:
    SlaveServerEngineClient(std::shared_ptr<Channel> channel) : stub_(enginePackage::SlaveServerEngine::NewStub(channel)) {};

    void placeCard(uint16_t baseId) {
        ClientContext context;
        enginePackage::placeCardArgs args;
        args.set_baseid(baseId);
        args.set_cardid(0);
        args.set_playerid(0);
        enginePackage::ServerResponse engineResponse;
        engineResponse.set_status(false);

        Status status = stub_->placeCard(&context, args, &engineResponse);
        if (!status.ok()) {
            std::cout << "SlaveServer placeCard failed." << std::endl;
            std::cout << "Cur status " << status.error_code() << std::endl;
            return;
        }

        std::cout << "Get response: " << engineResponse.status() << std::endl;

    };

    private:
      std::unique_ptr<enginePackage::SlaveServerEngine::Stub> stub_;
};

class MainServerEngineServiceImpl final : public enginePackage::MainServerEngine::Service {

    Status placeCard(::grpc::ServerContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response) override {
        // Implement your logic here to handle the placeCard RPC
        // For example:
        std::cout << "Received placeCard request" << std::endl;
        
        // Example response
        if (request->baseid() == 0)
        {
            response->set_status(1);
            for (auto &player : players_) { //FIXME TYAZH: write better loop
                player.placeCard(1);
            }
        }
        else
            response->set_status(0);

        std::cout << "Sending to all servers" << std::endl;

        return Status::OK;
    }

    Status initClient(::grpc::ServerContext* context, const ::enginePackage::ClientNetInfo* request, ::enginePackage::ServerResponse* response) override {
        std::cout << "New player with port: " << request->port() << " and Ip: " << context->peer() << std::endl;
        add_player(request->port());
        return Status::OK;
    }

    private:
    std::vector<SlaveServerEngineClient> players_;

    void add_player(uint32_t port) {
        std::string server_address("localhost:" + std::to_string(port));
        std::cout << "adding player with address " << server_address << std::endl;
        players_.push_back(SlaveServerEngineClient(grpc::CreateChannel(server_address,
                          grpc::InsecureChannelCredentials())));
    };

};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    MainServerEngineServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();
    return 0;
}
