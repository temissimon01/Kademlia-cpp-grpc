#pragma once


#pragma region NOSTDINCLUDE

#include <API/Identifier.h>

#pragma endregion

class ConnectionInfo
{
private:
	uint32_t __port;
	std::string __ip_addr;
	Identifier __id;

public:
	ConnectionInfo();
	ConnectionInfo(Identifier id, std::string ip, uint32_t port);
	~ConnectionInfo();

	Identifier id() const;
	std::string ip() const;
	uint32_t port() const;

	friend bool operator==(const ConnectionInfo& A, const ConnectionInfo& B);
	friend bool operator!=(const ConnectionInfo& A, const ConnectionInfo& B);
};

