// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: kademlia.proto

#include "kademlia.pb.h"
#include "kademlia.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace kademlia_rpc {

static const char* Communication_method_names[] = {
  "/kademlia_rpc.Communication/ping",
  "/kademlia_rpc.Communication/find_node",
  "/kademlia_rpc.Communication/store",
  "/kademlia_rpc.Communication/get",
};

std::unique_ptr< Communication::Stub> Communication::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< Communication::Stub> stub(new Communication::Stub(channel));
  return stub;
}

Communication::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_ping_(Communication_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_find_node_(Communication_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_store_(Communication_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_get_(Communication_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status Communication::Stub::ping(::grpc::ClientContext* context, const ::kademlia_rpc::PingQuery& request, ::kademlia_rpc::PingReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ping_, context, request, response);
}

void Communication::Stub::experimental_async::ping(::grpc::ClientContext* context, const ::kademlia_rpc::PingQuery* request, ::kademlia_rpc::PingReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_ping_, context, request, response, std::move(f));
}

void Communication::Stub::experimental_async::ping(::grpc::ClientContext* context, const ::kademlia_rpc::PingQuery* request, ::kademlia_rpc::PingReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_ping_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::PingReply>* Communication::Stub::PrepareAsyncpingRaw(::grpc::ClientContext* context, const ::kademlia_rpc::PingQuery& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::kademlia_rpc::PingReply>::Create(channel_.get(), cq, rpcmethod_ping_, context, request, false);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::PingReply>* Communication::Stub::AsyncpingRaw(::grpc::ClientContext* context, const ::kademlia_rpc::PingQuery& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncpingRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Communication::Stub::find_node(::grpc::ClientContext* context, const ::kademlia_rpc::FindNodeQuery& request, ::kademlia_rpc::FindNodeReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_find_node_, context, request, response);
}

void Communication::Stub::experimental_async::find_node(::grpc::ClientContext* context, const ::kademlia_rpc::FindNodeQuery* request, ::kademlia_rpc::FindNodeReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_find_node_, context, request, response, std::move(f));
}

void Communication::Stub::experimental_async::find_node(::grpc::ClientContext* context, const ::kademlia_rpc::FindNodeQuery* request, ::kademlia_rpc::FindNodeReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_find_node_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::FindNodeReply>* Communication::Stub::PrepareAsyncfind_nodeRaw(::grpc::ClientContext* context, const ::kademlia_rpc::FindNodeQuery& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::kademlia_rpc::FindNodeReply>::Create(channel_.get(), cq, rpcmethod_find_node_, context, request, false);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::FindNodeReply>* Communication::Stub::Asyncfind_nodeRaw(::grpc::ClientContext* context, const ::kademlia_rpc::FindNodeQuery& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncfind_nodeRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Communication::Stub::store(::grpc::ClientContext* context, const ::kademlia_rpc::StoreQuery& request, ::kademlia_rpc::StoreReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_store_, context, request, response);
}

void Communication::Stub::experimental_async::store(::grpc::ClientContext* context, const ::kademlia_rpc::StoreQuery* request, ::kademlia_rpc::StoreReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_store_, context, request, response, std::move(f));
}

void Communication::Stub::experimental_async::store(::grpc::ClientContext* context, const ::kademlia_rpc::StoreQuery* request, ::kademlia_rpc::StoreReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_store_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::StoreReply>* Communication::Stub::PrepareAsyncstoreRaw(::grpc::ClientContext* context, const ::kademlia_rpc::StoreQuery& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::kademlia_rpc::StoreReply>::Create(channel_.get(), cq, rpcmethod_store_, context, request, false);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::StoreReply>* Communication::Stub::AsyncstoreRaw(::grpc::ClientContext* context, const ::kademlia_rpc::StoreQuery& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncstoreRaw(context, request, cq);
  result->StartCall();
  return result;
}

::grpc::Status Communication::Stub::get(::grpc::ClientContext* context, const ::kademlia_rpc::GetQuery& request, ::kademlia_rpc::GetReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_get_, context, request, response);
}

void Communication::Stub::experimental_async::get(::grpc::ClientContext* context, const ::kademlia_rpc::GetQuery* request, ::kademlia_rpc::GetReply* response, std::function<void(::grpc::Status)> f) {
  ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_get_, context, request, response, std::move(f));
}

void Communication::Stub::experimental_async::get(::grpc::ClientContext* context, const ::kademlia_rpc::GetQuery* request, ::kademlia_rpc::GetReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) {
  ::grpc::internal::ClientCallbackUnaryFactory::Create(stub_->channel_.get(), stub_->rpcmethod_get_, context, request, response, reactor);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::GetReply>* Communication::Stub::PrepareAsyncgetRaw(::grpc::ClientContext* context, const ::kademlia_rpc::GetQuery& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::kademlia_rpc::GetReply>::Create(channel_.get(), cq, rpcmethod_get_, context, request, false);
}

::grpc::ClientAsyncResponseReader< ::kademlia_rpc::GetReply>* Communication::Stub::AsyncgetRaw(::grpc::ClientContext* context, const ::kademlia_rpc::GetQuery& request, ::grpc::CompletionQueue* cq) {
  auto* result =
    this->PrepareAsyncgetRaw(context, request, cq);
  result->StartCall();
  return result;
}

Communication::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Communication_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Communication::Service, ::kademlia_rpc::PingQuery, ::kademlia_rpc::PingReply>(
          [](Communication::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kademlia_rpc::PingQuery* req,
             ::kademlia_rpc::PingReply* resp) {
               return service->ping(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Communication_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Communication::Service, ::kademlia_rpc::FindNodeQuery, ::kademlia_rpc::FindNodeReply>(
          [](Communication::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kademlia_rpc::FindNodeQuery* req,
             ::kademlia_rpc::FindNodeReply* resp) {
               return service->find_node(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Communication_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Communication::Service, ::kademlia_rpc::StoreQuery, ::kademlia_rpc::StoreReply>(
          [](Communication::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kademlia_rpc::StoreQuery* req,
             ::kademlia_rpc::StoreReply* resp) {
               return service->store(ctx, req, resp);
             }, this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      Communication_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< Communication::Service, ::kademlia_rpc::GetQuery, ::kademlia_rpc::GetReply>(
          [](Communication::Service* service,
             ::grpc::ServerContext* ctx,
             const ::kademlia_rpc::GetQuery* req,
             ::kademlia_rpc::GetReply* resp) {
               return service->get(ctx, req, resp);
             }, this)));
}

Communication::Service::~Service() {
}

::grpc::Status Communication::Service::ping(::grpc::ServerContext* context, const ::kademlia_rpc::PingQuery* request, ::kademlia_rpc::PingReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Communication::Service::find_node(::grpc::ServerContext* context, const ::kademlia_rpc::FindNodeQuery* request, ::kademlia_rpc::FindNodeReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Communication::Service::store(::grpc::ServerContext* context, const ::kademlia_rpc::StoreQuery* request, ::kademlia_rpc::StoreReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status Communication::Service::get(::grpc::ServerContext* context, const ::kademlia_rpc::GetQuery* request, ::kademlia_rpc::GetReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace kademlia_rpc

