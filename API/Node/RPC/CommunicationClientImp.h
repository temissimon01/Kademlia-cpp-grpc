#pragma once

#pragma region GRPC_PROTO

#include <grpc++/grpc++.h>
#include <protos/kademlia.pb.h>
#include <protos/kademlia.grpc.pb.h>

#include <API/Node/Server.h>

#pragma endregion

class CommunicationClientImp
{
public:
	CommunicationClientImp(std::shared_ptr<grpc::Channel> channel, Server* self);

	bool ping(kademlia_rpc::PingQuery query);
	class FindNodeAnswer find_node(kademlia_rpc::FindNodeQuery query);
	bool store(kademlia_rpc::StoreQuery query);
	std::string get(kademlia_rpc::GetQuery query);

private:
	kademlia_rpc::Communication::Stub __stub;
	Server* __self;
};

