#include "Server.h"

#pragma region RPC_CLIENT_SERVICES

#include <API/Node/RPC/CommunicationClientImp.h>

#pragma endregion

Server::Server(Identifier id) : __id(id), __routingTable(id), __alive(false), __repository(id){}

Server::~Server()
{
	if (__serverThread) {
		if (__serverThread->joinable()) {
			__serverThread->join();
		}
	}

	if (__processingThread) {
		if (__processingThread->joinable()) {
			__processingThread->join();
		}
	}
}

void Server::start(std::string ip, uint32_t port)
{
	__alive = true;

	__address = ConnectionInfo(__id, ip, port);

	
	// Load all the services
	__services.push_back(std::shared_ptr<CommunicationServiceImp>(new CommunicationServiceImp(this)));

	__builder.reset(new grpc::ServerBuilder);
	__builder->AddListeningPort(ip + ":" + std::to_string(port), grpc::InsecureServerCredentials());

	// Register all the services
	for (int i = 0; i < __services.size(); i++) {
		__builder->RegisterService(__services[i].get());
	}

	__server = std::move(__builder->BuildAndStart());

	__serverThread.reset(new std::thread([this]() {
		__server->Wait();
	}));

	// Create the processing thread
	__processingThread.reset(new std::thread([this]() {

		while (isAlive()) {

			refreshReferenceNodes();

			pingAndUpdate(__referenceNodes);

			std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
			std::chrono::steady_clock::time_point end;
			do {
				end = std::chrono::steady_clock::now();

				if (!isAlive()) {
					break;
				}

			} while (std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() < Kademlia::PROCESS_MILLISECONDS_INTERVAL);
		}
	}));
}

void Server::stop()
{
	__server->Shutdown();
	if (__serverThread->joinable()) {
		__serverThread->join();
	}

	__serverThread.reset<std::thread>(nullptr);

	__alive = false;
	if (__processingThread->joinable()) {
		__processingThread->join();
	}

	__processingThread.reset<std::thread>(nullptr);
}

Identifier Server::id() const
{
	return __id;
}

bool Server::ping(const ConnectionInfo& info)
{
	std::shared_ptr<grpc::Channel> clientChannel;

	try {
		std::string endpoint = info.ip() + ":" + std::to_string(info.port());

		clientChannel = grpc::CreateChannel(endpoint, grpc::InsecureChannelCredentials());
	}
	catch (...){
		return false;
	}

	CommunicationClientImp pipe(clientChannel, this);

	kademlia_rpc::PingQuery query;

	query.set_magic(Utils::generate_magic());

	return pipe.ping(query);
}

FindNodeAnswer Server::findNode(const ConnectionInfo& caller, const ConnectionInfo& node, const Identifier& destination)
{
	if (node.id() != __id) {
		__routingTable.update(node);
	}

	FindNodeAnswer closestPeers = __routingTable.findClosest(destination);

	FindNodeAnswer prevClosestPeers;

	while (!closestPeers.found() && prevClosestPeers != closestPeers) {
		prevClosestPeers = closestPeers;

		FindNodeAnswer postSearch(destination);

		for (auto peer : closestPeers) {

			std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peer.ip() + ":" + std::to_string(peer.port()), grpc::InsecureChannelCredentials());

			CommunicationClientImp communication(channel, this);

			kademlia_rpc::FindNodeQuery findQuery;
			kademlia_rpc::ConnectionInfo* caller_alloc = new kademlia_rpc::ConnectionInfo();

			caller_alloc->set_id(caller.id());
			caller_alloc->set_ip(caller.ip());
			caller_alloc->set_port(caller.port());

			findQuery.set_allocated_caller(caller_alloc);


			findQuery.set_destination(destination);

			postSearch.merge(communication.find_node(findQuery));
		}

		closestPeers.merge(postSearch);
	}

	return closestPeers;
}

bool Server::store(std::string key, std::string value)
{
	// Apply sha1 to the key
	Identifier keyHash = Utils::hash_key(key, Kademlia::GUID_SPACE).convert_to<Identifier::numeric_type>();

	// Find the target node
	FindNodeAnswer findResult = this->findNode(address(), address(), keyHash);

	if (findResult.size() < 1) {
		return false;
	}

	ConnectionInfo peer = findResult.getNodes()[0];

	// send a store request
	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peer.ip() + ":" + std::to_string(peer.port()), grpc::InsecureChannelCredentials());
	CommunicationClientImp communication(channel, this);

	kademlia_rpc::ConnectionInfo* caller_alloc = new kademlia_rpc::ConnectionInfo;
	caller_alloc->set_id(__id);
	caller_alloc->set_ip(address().ip());
	caller_alloc->set_port(address().port());

	kademlia_rpc::StoreQuery storeQuery;
	storeQuery.set_key(key);
	storeQuery.set_value(value);
	storeQuery.set_magic(Utils::generate_magic());
	storeQuery.set_allocated_caller(caller_alloc);


	return communication.store(storeQuery);
}

std::string Server::get(std::string key)
{
	// Apply sha1 to the key
	Identifier keyHash = Utils::hash_key(key, Kademlia::GUID_SPACE).convert_to<Identifier::numeric_type>();

	// Find the target node
	FindNodeAnswer findResult = this->findNode(address(), address(), keyHash);

	if (findResult.size() < 1) {
		throw std::runtime_error("E_NO_PEERS");
	}

	ConnectionInfo peer = findResult.getNodes()[0];

	// send a store request
	std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peer.ip() + ":" + std::to_string(peer.port()), grpc::InsecureChannelCredentials());
	CommunicationClientImp communication(channel, this);

	kademlia_rpc::ConnectionInfo* caller_alloc = new kademlia_rpc::ConnectionInfo;
	caller_alloc->set_id(__id);
	caller_alloc->set_ip(address().ip());
	caller_alloc->set_port(address().port());

	kademlia_rpc::GetQuery getQuery;
	getQuery.set_key(key);
	getQuery.set_magic(Utils::generate_magic());
	getQuery.set_allocated_caller(caller_alloc);



	return communication.get(getQuery);
}

ConnectionInfo Server::address() const
{
	return __address;
}

void Server::refreshReferenceNodes()
{
	__referenceNodes.clear();

	std::vector<Identifier> distances = Identifier::GetDirectReferenceIds(__id);

	for (const auto& d : distances) {

		FindNodeAnswer findNodeAnswer = __routingTable.findClosest(d);

		if (findNodeAnswer.size() > 0) {
			__referenceNodes.push_back(findNodeAnswer.getNodes()[0]);
		}
	}

}

void Server::pingAndUpdate(std::vector<ConnectionInfo> targets)
{
	for (auto peer : targets) {

		std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(peer.ip() + ":" + std::to_string(peer.port()), grpc::InsecureChannelCredentials());

		CommunicationClientImp peerCommunication(channel, this);

		kademlia_rpc::PingQuery pingQuery;

		kademlia_rpc::ConnectionInfo* caller_alloc = new kademlia_rpc::ConnectionInfo();

		caller_alloc->set_id(address().id());
		caller_alloc->set_ip(address().ip());
		caller_alloc->set_port(address().port());

		pingQuery.set_magic(Utils::generate_magic());
		pingQuery.set_allocated_caller(caller_alloc);

		if (peerCommunication.ping(pingQuery)) {
			__routingTable.update(peer);
		}
		else {
			__routingTable.remove(peer);
		}
	}
}

void Server::bootstrap(ConnectionInfo bootstrapNodeInfo)
{
	FindNodeAnswer findResult = findNode(address(), bootstrapNodeInfo, __id);

	__routingTable.update(bootstrapNodeInfo);

	pingAndUpdate(findResult.getNodes());

}

RoutingTable& Server::routingTable()
{
	return __routingTable;
}

bool Server::isAlive() const
{
	return __alive;
}

void Server::storeRequested(std::string key, std::string value)
{
	__repository.store(key, value);
}

std::string Server::getRequested(std::string key)
{
	return __repository.get(key);
}
