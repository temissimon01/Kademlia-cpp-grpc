#include "RoutingTable.h"

RoutingTable::RoutingTable(const Identifier& ownerID) : __ownerId(ownerID){
	for (Identifier::numeric_type i = 0; i <= Kademlia::GUID_SPACE; i++) {
		__buckets.push_back(Bucket(i));
	}
}

RoutingTable::~RoutingTable()
{
}

void RoutingTable::update(const ConnectionInfo& connection_info)
{
	locker.lock();

	Identifier::numeric_type connectionBucketIndex = __ownerId.bucketOf(connection_info.id());

	Bucket& targetBucket = __buckets[(int)connectionBucketIndex];

	if (targetBucket.contains(connection_info)) {
		targetBucket.pushToFront(connection_info.id());
	}
	else {
		targetBucket.add(connection_info);
	}

	locker.unlock();
}

void RoutingTable::remove(const ConnectionInfo& connection_info)
{
	locker.lock();
	Identifier::numeric_type connectionBucketIndex = __ownerId.bucketOf(connection_info.id());

	Bucket& targetBucket = __buckets[(int)connectionBucketIndex];

	targetBucket.remove(connection_info);

	locker.unlock();
}

FindNodeAnswer RoutingTable::findClosest(const Identifier& destinationId)
{
	FindNodeAnswer answer(destinationId);

	Identifier::numeric_type connectionBucketIndex = __ownerId.bucketOf(destinationId);
	Bucket& targetBucket = __buckets[(int)connectionBucketIndex];

	for (const auto& id : targetBucket.getNodeIds()) {

		if (id != __ownerId) {
			answer.add(targetBucket.get(id));
		}
	}

	int bucketId = (int)targetBucket.getId().value();

	for (int i = 1; answer.size() < Kademlia::K_SIZE && ((bucketId - i) >= 0 || (bucketId + i) < __buckets.size()); i++) {
		//Check the previous buckets
		if (bucketId - i >= 0) {
			Bucket& prev = __buckets[bucketId - i];

			for (const auto& id : prev.getNodeIds()) {
				answer.add(prev.get(id));
			}
		}
		//Check the next buckets
		if (bucketId + i <= Kademlia::GUID_SPACE) {
			Bucket& next = __buckets[(int)(bucketId + i)];

			for (const auto& id : next.getNodeIds()) {
				answer.add(next.get(id));
			}
		}
	}


	answer.prepare();
	return answer;
}

std::string RoutingTable::toString() const
{
	std::string result;

	result = "[OwnerID=" + (std::string)__ownerId + " ";

	for (int i = 0; i < __buckets.size(); i++) {
		result += __buckets[i].toString() + " ";
	}

	result += "]";

	return result;
}
