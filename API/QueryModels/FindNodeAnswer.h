#pragma once

#pragma STDINCLUDE

#include <vector>

#pragma endregion

#pragma NOSTDINCLUDE

#include <API/Identifier.h>
#include <API/Node/ConnectionInfo.h>

#pragma endregion

class FindNodeAnswer
{
public:
	FindNodeAnswer();
	FindNodeAnswer(const Identifier& destinationId);
	~FindNodeAnswer();

	std::vector<ConnectionInfo> getNodes() const;

	int size() const;

	void remove(const ConnectionInfo& element);

	void add(const ConnectionInfo& connection_info);

	void merge(const FindNodeAnswer& other);

	void prepare();

	bool found() const;

	bool contains(const ConnectionInfo& connection_info) const;

	friend bool operator==(const FindNodeAnswer& A, const FindNodeAnswer& B);
	friend bool operator!=(const FindNodeAnswer& A, const FindNodeAnswer& B);

	std::vector<ConnectionInfo>::iterator begin();
	std::vector<ConnectionInfo>::iterator end();
	std::vector<ConnectionInfo>::const_iterator cbegin() const;
	std::vector<ConnectionInfo>::const_iterator cend() const;


private:
	Identifier __destinationId;
	std::vector<ConnectionInfo> __closestNodes;
};

