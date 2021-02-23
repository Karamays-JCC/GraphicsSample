#include "UServer.h"
#include <Framework/Net/Dispatcher/UDispatcher.h>
#include <Framework/Net/NetConnection/UNetConnection.h>
#include <Framework/Net/NetPackage/UNetPackage.h>

UServer::UServer()
{
}

UServer::~UServer()
{
}

void UServer::Init()
{
	int iRet = 0;

	iRet = WSAStartup(MAKEWORD(2, 2), &_WSAData);

	if (iRet != 0)
	{
		std::cout << "execute failed" << std::endl;
		return;
	}

	if (LOBYTE(_WSAData.wVersion) != 2 || HIBYTE(_WSAData.wVersion) != 2)
	{
		WSACleanup();
		std::cout << "version is not correct" << std::endl;
		return;
	}

	ListeningSocket.Init(100);
	ListeningSocket.Bind(666);
	ListeningSocket.Listen();
}

void UServer::Tick(float DeltaTime)
{
	//Server Logic
	_Accept(); // Create NetConnection
	_Release(); // Release NetConnection

	// Tick NetConnection (Do real Sending/Receiving)
	for (auto& Elem : NetConnections)
	{
		Elem.second->Tick(DeltaTime);
	}
}

void UServer::Broadcast(std::vector<std::string> Targets, std::shared_ptr<std::string> ContentPtr)
{
	for (auto& Elem : Targets)
	{
		auto It = NetConnections.find(Elem);
		if (It != NetConnections.end())
		{
			auto NewPackagePtr = std::make_shared<UNetPackage>();
			NewPackagePtr->Command = ECommand::Type::ClientUpdate;
			NewPackagePtr->Content = *ContentPtr;
			
			It->second->Send(NewPackagePtr);
		}
	}
}

void UServer::_Accept()
{
	// Check the socket
	//std::cout << "Checking client requests ..." << std::endl;
	FD_ZERO(&ListeningSocketSet);
	FD_SET(ListeningSocket.GetFD(), &ListeningSocketSet);
	timeval Time = { 0 ,0 };
	int Ret = select(0, &ListeningSocketSet, NULL, NULL, &Time);

	if (Ret <= 0) {
		//std::cout << "time out" << std::endl;
		return;
	}

	// Check down, then turn into accept(), and get the new socket fd.
	int AddrLen = sizeof SOCKADDR;
	SOCKADDR_IN LocalSocketAddr;
	SOCKADDR_IN RemoteSocketAddr;
	SOCKET NewLocalSocketFD = accept(ListeningSocket.GetFD(), (SOCKADDR*)&RemoteSocketAddr, &AddrLen);
	if (NewLocalSocketFD == SOCKET_ERROR) return;

	// Create a new net connection by the new socket fd and remote socket addr.
	std::cout << "Server accept a new client request and now is initing it." << std::endl;
	std::shared_ptr<UNetConnection> NewNetConnection = std::make_shared<UNetConnection>();
	NewNetConnection->CreateConnection(NewLocalSocketFD, LocalSocketAddr, RemoteSocketAddr);
	if (!NewNetConnection->IsValid()) {
		std::cout << "The new connection is valid, it will be discarded." << std::endl;
		return;
	}

	// Add the new valid connection into the container.
	std::cout << "A connection for this request has been created." << std::endl;
	NetConnections.insert({ NewNetConnection->GetGUID(), NewNetConnection });
}

void UServer::_Release()
{
}
