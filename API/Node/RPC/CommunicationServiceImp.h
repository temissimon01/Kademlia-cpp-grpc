#pragma once

#pragma region GRPC_PROTO

#include <grpc++/grpc++.h>
#include <protos/kademlia.pb.h>
#include <protos/kademlia.grpc.pb.h>

#pragma endregion

class CommunicationServiceImp : public kademlia_rpc::Communication::Service
{
public:
	CommunicationServiceImp(class Server* server);

	virtual ::grpc::Status ping(::grpc::ServerContext* context, const ::kademlia_rpc::PingQuery* request, ::kademlia_rpc::PingReply* response) override;
	virtual ::grpc::Status find_node(::grpc::ServerContext* context, const ::kademlia_rpc::FindNodeQuery* request, ::kademlia_rpc::FindNodeReply* response) override;
	virtual ::grpc::Status store(::grpc::ServerContext* context, const ::kademlia_rpc::StoreQuery* request, ::kademlia_rpc::StoreReply* response) override;
	virtual ::grpc::Status get(::grpc::ServerContext* context, const ::kademlia_rpc::GetQuery* request, ::kademlia_rpc::GetReply* response) override;

private:
	class Server* __self;
};

