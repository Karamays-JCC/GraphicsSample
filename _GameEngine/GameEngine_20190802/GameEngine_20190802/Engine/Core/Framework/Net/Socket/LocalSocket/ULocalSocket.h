#pragma once
#include <Global/Global.h>

#define MAX_RECV 1024

enum class E {
	DontRoute = MSG_DONTROUTE,
    
	DontWait,
	OOB = MSG_OOB,
	
	Peek = MSG_PEEK,
	WaitAll = MSG_WAITALL
};

class ULocalSocket
{
	using WinSocket = SOCKET;
	using WinSocketAddrIn = SOCKADDR_IN;
	using WinSocketSet = fd_set;
	using WinTimeValue = timeval;

public:
	ULocalSocket();
	virtual ~ULocalSocket();

private:
	bool bAvailable;

	WinSocket SocketFD;

	WinSocketAddrIn AddrIn;

	
	WinTimeValue SelectInterval;

	WinSocketSet ReadSet;

	WinSocketSet WriteSet;
	
	WinSocketSet ExceptSet;


	std::string RecvBuffer;
	
	std::vector<std::shared_ptr<std::string>> Out;

	std::vector<std::shared_ptr<std::string>> In;

private:
	void _Send();
	
	void _Receive();

	bool _CoreSend(const std::string& Content);

	bool _CoreReceive(std::vector<std::string>& Contents);

public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

public:
	void Send(std::shared_ptr<std::string> MessagePtr);

	std::shared_ptr<std::string> Receive();

	virtual void Init(WinSocket LocalSocketFD, const WinSocketAddrIn& LocalAddr);

	bool IsValid();

	std::string GetAddress();

	void SetSocket();

public:
	FORCEINLINE SOCKET GetSocketFD() const { return SocketFD; };
	
};

