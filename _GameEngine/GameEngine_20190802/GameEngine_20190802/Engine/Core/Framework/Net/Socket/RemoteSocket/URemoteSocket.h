#pragma once
#include <Global/Global.h>

class URemoteSocket
{
public:
	URemoteSocket();
	virtual ~URemoteSocket();

private:
	sockaddr_in AddrIn;

public:
	virtual void Init(const sockaddr_in& RemoteAddr);

	virtual void Tick(float DeltaTime);

public:
	std::string GetAddrString();

	FORCEINLINE const SOCKADDR_IN GetOriginalAddr() const { return AddrIn; };
	
};

