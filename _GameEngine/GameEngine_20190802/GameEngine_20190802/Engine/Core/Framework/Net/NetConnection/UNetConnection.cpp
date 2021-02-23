#include "UNetConnection.h"
#include <Framework/Net/Player/UPlayer.h>
#include <Framework/Net/NetPackage/UNetPackage.h>
#include <Framework/Net/NetDriver/UNetDriver.h>
#include <Framework/Net/NetConnection/Channel/UChannel.h>
#include <Framework/Net/NetConnection/Channel/UActorChannel.h>
#include <Framework/Net/NetConnection/Channel/UControlChannel.h>
#include <Framework/Net/NetConnection/Channel/UVoiceChannel.h>

UNetConnection::UNetConnection()
{
}

UNetConnection::~UNetConnection()
{
}

void UNetConnection::CreateConnection(SOCKET LocalSocketFD, const sockaddr_in& LocalAddr, const sockaddr_in& RemoteAddr)
{
	Local.Init(LocalSocketFD, LocalAddr);
	Remote.Init(RemoteAddr);

	std::cout << Local.GetAddress() << std::endl;
	std::cout << Remote.GetAddrString() << std::endl;
}

void UNetConnection::Send(std::shared_ptr<class UNetPackage> OutPackage)
{
	Out.push_back(OutPackage);
}

std::shared_ptr<class UNetPackage> UNetConnection::Receive()
{
	if (In.size() < 1) return nullptr;

	std::shared_ptr<class UNetPackage> PackagePtr = nullptr;
	PackagePtr = *(In.begin());
	
	if (PackagePtr.get() != nullptr)
		In.erase(In.begin());

	return PackagePtr;
}

bool UNetConnection::IsValid()
{
	return true;
}

void UNetConnection::_Send()
{
	for (auto It = Out.begin(); It != Out.end(); ++It)
	{
		Local.Send(std::make_shared<std::string>((*It)->Serialize()));
	}
	Out.clear();
}

void UNetConnection::_Receive()
{
	auto ContentStrPtr = Local.Receive();
	if (ContentStrPtr.get() != nullptr)
	{
		std::cout << "Content: " << *ContentStrPtr << std::endl;
		std::shared_ptr<UNetPackage> PackagePtr = std::make_shared<UNetPackage>();
		PackagePtr->Deserialize(*ContentStrPtr);

		In.push_back(PackagePtr);
	}
}

void UNetConnection::Init()
{
}

void UNetConnection::Tick(float DeltaTime)
{
	Local.Tick(DeltaTime);
	Remote.Tick(DeltaTime);

	_Send();
	_Receive();
}
