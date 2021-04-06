#pragma once

#pragma region STDINCLUDE

#include <vector>
#include <mutex>

#pragma endregion NOSTDINCLUDE

#pragma region NOSTDINCLUDE

#include <API/SysDef.h>
#include <API/Identifier.h>
#include <API/Node/ConnectionInfo.h>

#include <boost/unordered_map.hpp>

#pragma endregion

class Bucket
{
public:
	Bucket();
	Bucket(const Identifier& id);
	~Bucket();

	Identifier getId() const;

	Identifier::numeric_type size() const;

	bool contains(const Identifier& id) const;
	bool contains(const ConnectionInfo& connection_info) const;

	void add(const ConnectionInfo& connection_info);
	void remove(const Identifier& id);
	void remove(const ConnectionInfo& connection_info);

	void pushToFront(const Identifier& id);

	ConnectionInfo get(const Identifier& id);
	const std::vector<Identifier>& getNodeIds() const;

	std::string toString() const;

private:
	Identifier __id;

	std::vector<Identifier> __nodeIds;
	boost::unordered_map<Identifier::numeric_type, ConnectionInfo> __nodesMap;
};

