#include "URemoteSocket.h"

URemoteSocket::URemoteSocket()
{
}

URemoteSocket::~URemoteSocket()
{
}

void URemoteSocket::Init(const sockaddr_in& RemoteAddr)
{
	AddrIn = RemoteAddr;
}

void URemoteSocket::Tick(float DeltaTime)
{
	
}

std::string URemoteSocket::GetAddrString()
{
	const size_t IPv4Len = 50;
	char* IPv4Ptr = new char[IPv4Len];
	inet_ntop(AF_INET, &AddrIn.sin_addr, IPv4Ptr, IPv4Len); // cast to char

	return "RemoteAddr : " + std::string(IPv4Ptr) + ":" + std::to_string(AddrIn.sin_port);
}
