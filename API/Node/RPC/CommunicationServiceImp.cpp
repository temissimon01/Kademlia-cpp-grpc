#include "CommunicationServiceImp.h"

#include <API/Node/Server.h>

CommunicationServiceImp::CommunicationServiceImp(Server* server) : __self(server){}

::grpc::Status CommunicationServiceImp::ping(::grpc::ServerContext* context, const::kademlia_rpc::PingQuery* request, ::kademlia_rpc::PingReply* response)
{
	response->set_magic(request->magic());

	ConnectionInfo callerInfo(Identifier::FromString(request->caller().id()), request->caller().ip(), request->caller().port());

	__self->routingTable().update(callerInfo);

	return ::grpc::Status::OK;
}

::grpc::Status CommunicationServiceImp::find_node(::grpc::ServerContext* context, const::kademlia_rpc::FindNodeQuery* request, ::kademlia_rpc::FindNodeReply* response)
{
	try {
		FindNodeAnswer result = __self->routingTable().findClosest(Identifier::FromString(request->destination()));

		for (auto peer : result) {
			kademlia_rpc::ConnectionInfo* connInfo = response->add_closest();

			connInfo->set_id((std::string)peer.id());
			connInfo->set_ip(peer.ip());
			connInfo->set_port(peer.port());
		}

	}
	catch (std::exception& e) {
		return grpc::Status(grpc::StatusCode::INTERNAL, e.what());
	}


	return ::grpc::Status::OK;
}

::grpc::Status CommunicationServiceImp::store(::grpc::ServerContext* context, const::kademlia_rpc::StoreQuery* request, ::kademlia_rpc::StoreReply* response)
{
	response->set_magic(request->magic());

	__self->storeRequested(request->key(), request->value());

	return ::grpc::Status::OK;
}

::grpc::Status CommunicationServiceImp::get(::grpc::ServerContext* context, const::kademlia_rpc::GetQuery* request, ::kademlia_rpc::GetReply* response)
{
	try {
		response->set_magic(request->magic());

		response->set_value(__self->getRequested(request->key()));
	}
	catch (...) {
		return ::grpc::Status(grpc::StatusCode::NOT_FOUND, "Key not found");
	}
	return ::grpc::Status::OK;
}
