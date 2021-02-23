#pragma once
#include <Global/Global.h>
#include <Framework/Net/Handler/UNetHandler.h>
#include <Framework/Net/Socket/ListeningSocket/UListeningSocket.h>

/*
* Handle the Forwarding logic
* 
*/

class UServer : public UNetHandler
{
public:
	UServer();
	virtual ~UServer();

private:
	// The listening socket
	class UListeningSocket ListeningSocket;

	// Maintain all the connections created with clients.
	std::unordered_map<std::string, std::shared_ptr<class UNetConnection>> NetConnections;

	// Buffer that ready to send.
	std::vector<std::shared_ptr<class UNetPackage>> Out;

	// Buffer that ready to receive.
	std::vector<std::shared_ptr<class UNetPackage>> In;

private:
	// Accept client's request.
	void _Accept();

	// Release ending client connections.
	void _Release();

public:
	virtual void Init() override;

	virtual void Tick(float DeltaTime) override;

public:
	void Broadcast(std::vector<std::string> Targets, std::shared_ptr<std::string> ContentPtr);
	//void Unicast();

private:
	WSADATA _WSAData;

	fd_set ListeningSocketSet;

};

