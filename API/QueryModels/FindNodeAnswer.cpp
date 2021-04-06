#include "FindNodeAnswer.h"

FindNodeAnswer::FindNodeAnswer(){}
FindNodeAnswer::FindNodeAnswer(const Identifier& destinationId) : __destinationId(destinationId){}
FindNodeAnswer::~FindNodeAnswer(){}

std::vector<ConnectionInfo> FindNodeAnswer::getNodes() const
{
	return __closestNodes;
}

int FindNodeAnswer::size() const {
	return __closestNodes.size();
}

void FindNodeAnswer::remove(const ConnectionInfo& element)
{
	std::vector<ConnectionInfo>::iterator element_iterator = std::find_if(__closestNodes.begin(), __closestNodes.end(), [element](const ConnectionInfo& current)->bool {
		return current.id() == element.id();
		});

	if (element_iterator != __closestNodes.end()) {
		__closestNodes.erase(element_iterator);
	}
}

void FindNodeAnswer::add(const ConnectionInfo& connection_info)
{
	__closestNodes.push_back(connection_info);
}

void FindNodeAnswer::merge(const FindNodeAnswer& other)
{
	for (auto iterator = other.cbegin(); iterator != other.cend(); iterator++) {

		if (!contains(*iterator)) {
			__closestNodes.push_back(*iterator);
		}

	}
}

void FindNodeAnswer::prepare()
{
	std::sort(__closestNodes.begin(), __closestNodes.end(), [this](const ConnectionInfo& A, const ConnectionInfo& B)->bool {
		return A.id().distance(__destinationId) < B.id().distance(__destinationId);
		});

	if (__closestNodes.size() > Kademlia::FIND_NODE_SIZE) {
		__closestNodes.erase(__closestNodes.begin() + Kademlia::FIND_NODE_SIZE, __closestNodes.begin() + __closestNodes.size());
	}
}

bool FindNodeAnswer::found() const
{
	if (size() < 1) {
		return false;
	}

	return __closestNodes[0].id().distance(__destinationId) == 0;
}

bool FindNodeAnswer::contains(const ConnectionInfo& connection_info) const
{
	auto iterator = std::find_if(__closestNodes.begin(), __closestNodes.end(), [connection_info](const ConnectionInfo &element)->bool {
		return element == connection_info;
		});

	return iterator != __closestNodes.end();
}

std::vector<ConnectionInfo>::iterator FindNodeAnswer::begin()
{
	return __closestNodes.begin();
}

std::vector<ConnectionInfo>::iterator FindNodeAnswer::end()
{
	return __closestNodes.end();
}

std::vector<ConnectionInfo>::const_iterator FindNodeAnswer::cbegin() const
{
	return __closestNodes.cbegin();
}

std::vector<ConnectionInfo>::const_iterator FindNodeAnswer::cend() const
{
	return __closestNodes.cend();
}

bool operator==(const FindNodeAnswer& A, const FindNodeAnswer& B)
{
	if (A.__destinationId != B.__destinationId) {
		return false;
	}

	if (A.size() != B.size()) {
		return false;
	}

	for (int i = 0; i < A.size(); i++) {
		if (!B.contains(A.__closestNodes[i])) {
			return false;
		}
	}
	

	return true;
}

bool operator!=(const FindNodeAnswer& A, const FindNodeAnswer& B)
{
	return !(A==B);
}
