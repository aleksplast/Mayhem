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

class SlaveServerEngineServiceImpl final : public enginePackage::MainServerEngine::Service {
    Status placeCard(::grpc::ServerContext* /*context*/, const ::enginePackage::placeCardArgs* /*request*/, ::enginePackage::ServerResponse* /*response*/);
};