#include "Bucket.h"

Bucket::Bucket(){}
Bucket::Bucket(const Identifier& id) : __id(id){}
Bucket::~Bucket() {}

Identifier Bucket::getId() const
{
	return __id;
}


Identifier::numeric_type Bucket::size() const
{
	return (Identifier::numeric_type)__nodeIds.size();
}

bool Bucket::contains(const Identifier& id) const
{
	for (int i = 0; i < __nodeIds.size(); i++) {
		if (__nodeIds[i] == id) {
			return true;
		}
	}

	return false;
}

bool Bucket::contains(const ConnectionInfo& connection_info) const
{
	return contains(connection_info.id());
}

void Bucket::add(const ConnectionInfo& connection_info)
{
	// Remove the element if already inserted
	remove(connection_info.id());

	// insert the new id on the nodes ids list
	__nodeIds.insert(__nodeIds.begin(), connection_info.id());

	// insert the new id on the map
	__nodesMap[connection_info.id()] = connection_info;
}

void Bucket::remove(const Identifier& id)
{
	std::vector<Identifier>::iterator ids_iterator = std::find_if(__nodeIds.begin(), __nodeIds.end(), [id](const Identifier& element)->bool {
		return id == element;
	});

	if (ids_iterator != __nodeIds.end()) {
		__nodeIds.erase(ids_iterator);
		__nodesMap.erase(id);
	}
}

void Bucket::remove(const ConnectionInfo& connection_info)
{
	remove(connection_info.id());
}

void Bucket::pushToFront(const Identifier& id)
{

	std::vector<Identifier>::iterator ids_iterator = std::find_if(__nodeIds.begin(), __nodeIds.end(), [id](const Identifier& element)->bool {
		return id == element;
	});

	if (ids_iterator != __nodeIds.end()) {
		__nodeIds.erase(ids_iterator);
		__nodeIds.insert(__nodeIds.begin(), id);
	}

}

ConnectionInfo Bucket::get(const Identifier& id)
{
	if (!contains(id)) {
		throw std::runtime_error("E_UNKNOWN_ID");
	}
	return __nodesMap[id];
}

const std::vector<Identifier>& Bucket::getNodeIds() const
{
	return __nodeIds;
}

std::string Bucket::toString() const
{
	std::string result;

	result += "Bucket [id=" + (std::string)__id + " nodeIds=(";

	for (int i = 0; i < __nodeIds.size(); i++) {
		result += __nodeIds[i];

		if (i < __nodeIds.size() - 1) {
			result += ",";
		}
	}

	result += ")]";

	return result;
}
