#include <iostream>
#include <stdio.h>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "engine.pb.h"
#include "engine.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

class SlaveServerEngineServiceImpl final : public enginePackage::SlaveServerEngine::Service {
    Status placeCard(::grpc::ServerContext* /*context*/, const ::enginePackage::placeCardArgs* /*request*/, ::enginePackage::ServerResponse* /*response*/) override {
        std::cout << "Placing card, because MainServer said" << std::endl;
        return Status::OK;
    };
};

class MainServerEngineClient {
    public:
    MainServerEngineClient(std::shared_ptr<Channel> channel) : stub_(enginePackage::MainServerEngine::NewStub(channel)) {};

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
            std::cout << "GetFeature rpc failed." << std::endl;
            std::cout << "Cur status " << status.error_code() << std::endl;
            return;
        }

        std::cout << "Get response: " << engineResponse.status() << std::endl;

    };

    void initClient(uint32_t port) {
        ClientContext context;
        enginePackage::ClientNetInfo net_info;
        net_info.set_port(port);
        enginePackage::ServerResponse engine_response;
        Status status = stub_->initClient(&context, net_info, &engine_response);

        if (!status.ok()) {
            std::cout << "GetFeature rpc failed." << std::endl;
            return;
        }

    };

    private:
      std::unique_ptr<enginePackage::MainServerEngine::Stub> stub_;
};

int main(int argc, char* argv[]) {
    if (argc == 0) {
        std::cout << "error, please enter the client port\n";
        return;
    }

    std::string server_port(argv[1]);
    MainServerEngineClient client(grpc::CreateChannel("localhost:50051",
                          grpc::InsecureChannelCredentials()));

    std::string server_address("localhost:" + server_port);
    SlaveServerEngineServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    client.initClient(std::atoi(argv[1]));
    getchar();

    client.placeCard(0);
    client.placeCard(1);
    client.placeCard(1);
    client.placeCard(1);
    client.placeCard(1);
    client.placeCard(0);
    server->Wait();
}