#include "CommunicationClientImp.h"

#include <API/QueryModels/FindNodeAnswer.h>

CommunicationClientImp::CommunicationClientImp(std::shared_ptr<grpc::Channel> channel, Server* self) : __stub(channel), __self(self){}

bool CommunicationClientImp::ping(kademlia_rpc::PingQuery query)
{
    grpc::ClientContext context;

    kademlia_rpc::PingReply reply;
    if (!__stub.ping(&context, query, &reply).ok()) {
        return false;
    }

    return query.magic() == reply.magic();
}

FindNodeAnswer CommunicationClientImp::find_node(kademlia_rpc::FindNodeQuery query)
{
    grpc::ClientContext context;

    kademlia_rpc::FindNodeReply reply;
    grpc::Status result = __stub.find_node(&context, query, &reply);
    if (!result.ok()) {
        std::cout << result.error_code() << ": " << result.error_message() << std::endl;
        return FindNodeAnswer();
    }

    FindNodeAnswer answer(Identifier::FromString(query.destination()));

    for (int i = 0; i < reply.closest_size(); i++) {
        kademlia_rpc::ConnectionInfo info = reply.closest().Get(i);
        answer.add(ConnectionInfo(Identifier::FromString(info.id()), info.ip(), info.port()));
    }

    return answer;
}

bool CommunicationClientImp::store(kademlia_rpc::StoreQuery query)
{
    grpc::ClientContext context;

    kademlia_rpc::StoreReply reply;
    if (!__stub.store(&context, query, &reply).ok()) {
        return false;
    }

    return query.magic() == reply.magic();
}

std::string CommunicationClientImp::get(kademlia_rpc::GetQuery query)
{
    grpc::ClientContext context;

    kademlia_rpc::GetReply reply;
    grpc::Status result = __stub.get(&context, query, &reply);
    if (!result.ok()) {
        throw result.error_message();
    }

    return reply.value();
}
