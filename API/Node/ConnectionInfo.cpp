#include "ConnectionInfo.h"

ConnectionInfo::ConnectionInfo() : __id(0), __ip_addr(""), __port(0){}
ConnectionInfo::ConnectionInfo(Identifier id, std::string ip, uint32_t port) : __id(id), __ip_addr(ip), __port(port){}
ConnectionInfo::~ConnectionInfo(){}

Identifier ConnectionInfo::id() const
{
	return __id;
}

std::string ConnectionInfo::ip() const
{
	return __ip_addr;
}

uint32_t ConnectionInfo::port() const
{
	return __port;
}

bool operator==(const ConnectionInfo& A, const ConnectionInfo& B)
{
	return A.__ip_addr.compare(B.__ip_addr) == 0 && A.__port == B.__port && A.__id == B.__id;
}

bool operator!=(const ConnectionInfo& A, const ConnectionInfo& B)
{
	return A.__ip_addr.compare(B.__ip_addr) != 0 || A.__port != B.__port || A.__id != B.__id;;
}
