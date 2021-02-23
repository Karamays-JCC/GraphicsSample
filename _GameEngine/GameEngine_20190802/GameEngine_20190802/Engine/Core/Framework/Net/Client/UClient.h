#pragma once
#include <Global/Global.h>
#include <Framework/Net/Handler/UNetHandler.h>

class UClient : public UNetHandler
{
public:
	UClient();
	virtual ~UClient();

private:
	std::shared_ptr<class UNetConnection> MainNetConnection;

	// Buffer that ready to send.
	std::vector<std::shared_ptr<class UNetPackage>> Out;

	// Buffer that ready to receive.
	std::vector<std::shared_ptr<class UNetPackage>> In;

private:
	void _Send();

	void _Receive();

public:
	void Init() override;

	virtual void Tick(float DeltaTime) override;

public:
	void Connect(std::string IP = "127.0.0.1", unsigned int Port = 666);

	void Send(std::shared_ptr<class UNetPackage> OutPackage);

	std::shared_ptr<class UNetPackage> Recive();

private:
	WSADATA _WSAData;

	int x;
	int y;
	int z;
};

