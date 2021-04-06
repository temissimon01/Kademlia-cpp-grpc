#pragma once

#pragma region NOSTDINCLUDE

#include <grpc++/grpc++.h>
#include <API/Node/RPC/CommunicationServiceImp.h>

#include <API/Identifier.h>
#include <API/RoutingTable.h>
#include <API/Node/ConnectionInfo.h>
#include <API/Utils.h>
#include <API/Repository.h>

#pragma endregion

class Server
{
public:
	Server(Identifier id);
	~Server();

	void start(std::string ip, uint32_t port);
	void stop();

	Identifier id() const;

	bool ping(const ConnectionInfo& id);
	FindNodeAnswer findNode(const ConnectionInfo& caller, const ConnectionInfo& node, const Identifier& destination);
	bool store(std::string key, std::string value);
	std::string get(std::string key);

	ConnectionInfo address() const;

	void refreshReferenceNodes();
	void pingAndUpdate(std::vector<ConnectionInfo> targets);
	void bootstrap(ConnectionInfo bootstrapNodeInfo);

	RoutingTable& routingTable();

	bool isAlive() const;

	void storeRequested(std::string key, std::string value);
	std::string getRequested(std::string key);

private:
	RoutingTable __routingTable;
	Identifier __id;
	ConnectionInfo __address;
	
	std::shared_ptr<grpc::Server> __server;
	std::shared_ptr<grpc::ServerBuilder> __builder;
	std::shared_ptr<std::thread> __serverThread;
	std::shared_ptr<std::thread> __processingThread;
	std::vector<std::shared_ptr<grpc::Service>> __services;
	std::vector<ConnectionInfo> __referenceNodes;
	std::atomic_bool __alive;
	Repository<std::string> __repository;
};

