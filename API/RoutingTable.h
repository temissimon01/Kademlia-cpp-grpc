#pragma once

#pragma region STDINCLUDE

#include <vector>

#pragma endregion

#pragma region NOSTDINCLUDE

#include <API/Identifier.h>
#include <API/Bucket.h>
#include <API/Node/ConnectionInfo.h>

#include <API/QueryModels/FindNodeAnswer.h>

#pragma endregion


class RoutingTable
{
public:

	RoutingTable(const Identifier &ownerID);
	~RoutingTable();

	void update(const ConnectionInfo& connection_info);
	void remove(const ConnectionInfo& connection_info);

	FindNodeAnswer findClosest(const Identifier &destinationId);

	std::string toString() const;

private:
	Identifier __ownerId;
	std::vector<Bucket> __buckets;
	std::mutex locker;
};

