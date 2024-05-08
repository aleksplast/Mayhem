// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: engine.proto

#include "engine.pb.h"
#include "engine.grpc.pb.h"

#include <functional>
#include <grpcpp/support/async_stream.h>
#include <grpcpp/support/async_unary_call.h>
#include <grpcpp/impl/channel_interface.h>
#include <grpcpp/impl/client_unary_call.h>
#include <grpcpp/support/client_callback.h>
#include <grpcpp/support/message_allocator.h>
#include <grpcpp/support/method_handler.h>
#include <grpcpp/impl/rpc_service_method.h>
#include <grpcpp/support/server_callback.h>
#include <grpcpp/impl/server_callback_handlers.h>
#include <grpcpp/server_context.h>
#include <grpcpp/impl/service_type.h>
#include <grpcpp/support/sync_stream.h>
namespace enginePackage {

static const char* MainServerEngine_method_names[] = {
  "/enginePackage.MainServerEngine/placeCard",
  "/enginePackage.MainServerEngine/playAction",
  "/enginePackage.MainServerEngine/endTurn",
  "/enginePackage.MainServerEngine/initClient",
  "/enginePackage.MainServerEngine/GetFile",
};

std::unique_ptr< MainServerEngine::Stub> MainServerEngine::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< MainServerEngine::Stub> stub(new MainServerEngine::Stub(channel, options));
  return stub;
}

MainServerEngine::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_placeCard_(MainServerEngine_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_playAction_(MainServerEngine_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_endTurn_(MainServerEngine_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_initClient_(MainServerEngine_method_names[3], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_GetFile_(MainServerEngine_method_names[4], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status MainServerEngine::Stub::placeCard(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_placeCard_, context, request, response);
}

void MainServerEngine::Stub::async::placeCard(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_placeCard_, context, request, response, std::move(f));
}

void MainServerEngine::Stub::async::placeCard(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_placeCard_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::PrepareAsyncplaceCardRaw(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::placeCardArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_placeCard_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::AsyncplaceCardRaw(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncplaceCardRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MainServerEngine::Stub::playAction(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_playAction_, context, request, response);
}

void MainServerEngine::Stub::async::playAction(::grpc::ClientContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_playAction_, context, request, response, std::move(f));
}

void MainServerEngine::Stub::async::playAction(::grpc::ClientContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_playAction_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::PrepareAsyncplayActionRaw(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::playActionArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_playAction_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::AsyncplayActionRaw(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncplayActionRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MainServerEngine::Stub::endTurn(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_endTurn_, context, request, response);
}

void MainServerEngine::Stub::async::endTurn(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_endTurn_, context, request, response, std::move(f));
}

void MainServerEngine::Stub::async::endTurn(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_endTurn_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::PrepareAsyncendTurnRaw(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::endTurnArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_endTurn_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::AsyncendTurnRaw(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncendTurnRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MainServerEngine::Stub::initClient(::grpc::ClientContext* context, const ::enginePackage::ClientNetInfo& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::ClientNetInfo, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_initClient_, context, request, response);
}

void MainServerEngine::Stub::async::initClient(::grpc::ClientContext* context, const ::enginePackage::ClientNetInfo* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::ClientNetInfo, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_initClient_, context, request, response, std::move(f));
}

void MainServerEngine::Stub::async::initClient(::grpc::ClientContext* context, const ::enginePackage::ClientNetInfo* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_initClient_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::PrepareAsyncinitClientRaw(::grpc::ClientContext* context, const ::enginePackage::ClientNetInfo& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::ClientNetInfo, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_initClient_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* MainServerEngine::Stub::AsyncinitClientRaw(::grpc::ClientContext* context, const ::enginePackage::ClientNetInfo& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncinitClientRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status MainServerEngine::Stub::GetFile(::grpc::ClientContext* context, const ::enginePackage::FileRequest& request, ::enginePackage::FileResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::FileRequest, ::enginePackage::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_GetFile_, context, request, response);
}

void MainServerEngine::Stub::async::GetFile(::grpc::ClientContext* context, const ::enginePackage::FileRequest* request, ::enginePackage::FileResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::FileRequest, ::enginePackage::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetFile_, context, request, response, std::move(f));
}

void MainServerEngine::Stub::async::GetFile(::grpc::ClientContext* context, const ::enginePackage::FileRequest* request, ::enginePackage::FileResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_GetFile_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::FileResponse>* MainServerEngine::Stub::PrepareAsyncGetFileRaw(::grpc::ClientContext* context, const ::enginePackage::FileRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::FileResponse, ::enginePackage::FileRequest, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_GetFile_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::FileResponse>* MainServerEngine::Stub::AsyncGetFileRaw(::grpc::ClientContext* context, const ::enginePackage::FileRequest& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncGetFileRaw(context, request, cq);
  result->StartCall();
  return result;
}

MainServerEngine::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MainServerEngine_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MainServerEngine::Service, ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MainServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::placeCardArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->placeCard(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MainServerEngine_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MainServerEngine::Service, ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MainServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::playActionArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->playAction(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MainServerEngine_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MainServerEngine::Service, ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MainServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::endTurnArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->endTurn(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MainServerEngine_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MainServerEngine::Service, ::enginePackage::ClientNetInfo, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MainServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::ClientNetInfo* req,
             ::enginePackage::ServerResponse* resp) {
               return service->initClient(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      MainServerEngine_method_names[4],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< MainServerEngine::Service, ::enginePackage::FileRequest, ::enginePackage::FileResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](MainServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::FileRequest* req,
             ::enginePackage::FileResponse* resp) {
               return service->GetFile(ctx, req, resp);
             }, this)));
}

MainServerEngine::Service::~Service() {
}

::grpc::Status MainServerEngine::Service::placeCard(::grpc::ServerContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MainServerEngine::Service::playAction(::grpc::ServerContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MainServerEngine::Service::endTurn(::grpc::ServerContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MainServerEngine::Service::initClient(::grpc::ServerContext* context, const ::enginePackage::ClientNetInfo* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status MainServerEngine::Service::GetFile(::grpc::ServerContext* context, const ::enginePackage::FileRequest* request, ::enginePackage::FileResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


static const char* SlaveServerEngine_method_names[] = {
  "/enginePackage.SlaveServerEngine/placeCardSlave",
  "/enginePackage.SlaveServerEngine/playActionSlave",
  "/enginePackage.SlaveServerEngine/endTurnSlave",
};

std::unique_ptr< SlaveServerEngine::Stub> SlaveServerEngine::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< SlaveServerEngine::Stub> stub(new SlaveServerEngine::Stub(channel, options));
  return stub;
}

SlaveServerEngine::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options)
  : channel_(channel), rpcmethod_placeCardSlave_(SlaveServerEngine_method_names[0], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_playActionSlave_(SlaveServerEngine_method_names[1], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_endTurnSlave_(SlaveServerEngine_method_names[2], options.suffix_for_stats(),::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status SlaveServerEngine::Stub::placeCardSlave(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_placeCardSlave_, context, request, response);
}

void SlaveServerEngine::Stub::async::placeCardSlave(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_placeCardSlave_, context, request, response, std::move(f));
}

void SlaveServerEngine::Stub::async::placeCardSlave(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_placeCardSlave_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::PrepareAsyncplaceCardSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::placeCardArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_placeCardSlave_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::AsyncplaceCardSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::placeCardArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncplaceCardSlaveRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status SlaveServerEngine::Stub::playActionSlave(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_playActionSlave_, context, request, response);
}

void SlaveServerEngine::Stub::async::playActionSlave(::grpc::ClientContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_playActionSlave_, context, request, response, std::move(f));
}

void SlaveServerEngine::Stub::async::playActionSlave(::grpc::ClientContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_playActionSlave_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::PrepareAsyncplayActionSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::playActionArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_playActionSlave_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::AsyncplayActionSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::playActionArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncplayActionSlaveRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status SlaveServerEngine::Stub::endTurnSlave(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::enginePackage::ServerResponse* response) {
  return ::grpc::internal::BlockingUnaryCall< ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), rpcmethod_endTurnSlave_, context, request, response);
}

void SlaveServerEngine::Stub::async::endTurnSlave(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall< ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_endTurnSlave_, context, request, response, std::move(f));
}

void SlaveServerEngine::Stub::async::endTurnSlave(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response, ::grpc::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create< ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(stub_->channel_.get(), stub_->rpcmethod_endTurnSlave_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::PrepareAsyncendTurnSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderHelper::Create< ::enginePackage::ServerResponse, ::enginePackage::endTurnArgs, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(channel_.get(), cq, rpcmethod_endTurnSlave_, context, request);
}

::grpc::ClientAsyncResponseReader< ::enginePackage::ServerResponse>* SlaveServerEngine::Stub::AsyncendTurnSlaveRaw(::grpc::ClientContext* context, const ::enginePackage::endTurnArgs& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncendTurnSlaveRaw(context, request, cq);
  result->StartCall();
  return result;
}

SlaveServerEngine::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SlaveServerEngine_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SlaveServerEngine::Service, ::enginePackage::placeCardArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SlaveServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::placeCardArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->placeCardSlave(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SlaveServerEngine_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SlaveServerEngine::Service, ::enginePackage::playActionArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SlaveServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::playActionArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->playActionSlave(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      SlaveServerEngine_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< SlaveServerEngine::Service, ::enginePackage::endTurnArgs, ::enginePackage::ServerResponse, ::grpc::protobuf::MessageLite, ::grpc::protobuf::MessageLite>(
          [](SlaveServerEngine::Service* service,
             ::grpc::ServerContext* ctx,
             const ::enginePackage::endTurnArgs* req,
             ::enginePackage::ServerResponse* resp) {
               return service->endTurnSlave(ctx, req, resp);
             }, this)));
}

SlaveServerEngine::Service::~Service() {
}

::grpc::Status SlaveServerEngine::Service::placeCardSlave(::grpc::ServerContext* context, const ::enginePackage::placeCardArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SlaveServerEngine::Service::playActionSlave(::grpc::ServerContext* context, const ::enginePackage::playActionArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status SlaveServerEngine::Service::endTurnSlave(::grpc::ServerContext* context, const ::enginePackage::endTurnArgs* request, ::enginePackage::ServerResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace enginePackage

