#include "UNetUnit.h"
#include <Framework/GameInstance/UGameInstance.h>
#include <Framework/Level/ULevel.h>
#include <Framework/Object/UObject.h>
#include <Framework/RenderableObject/RenderableObject.h>
#include <Framework/Net/NetConnection/UNetConnection.h>
#include <Framework/Net/Dispatcher/UDispatcher.h>
#include <Framework/Net/Handler/UNetHandler.h>
#include <Framework/Net/Server/UServer.h>
#include <Framework/Net/Client/UClient.h>

UNetUnit::UNetUnit() :
	bServer(false),
	NetHandler(nullptr),
	Dispatcher(nullptr)
{
}

UNetUnit::UNetUnit(bool bAsServer) :
	bServer(bAsServer),
	NetHandler(nullptr),
	Dispatcher(nullptr)
{
	if(bAsServer)
		std::cout << "Server starting ..." << std::endl;
	else
		std::cout << "Client starting ..." << std::endl;
}

UNetUnit::~UNetUnit()
{
}

void UNetUnit::Init()
{
	if (bServer)
		NetHandler = std::make_shared<UServer>();
	else
		NetHandler = std::make_shared<UClient>();
	
	NetHandler->Init();

	Dispatcher = std::make_shared<UDispatcher>();
	Dispatcher->Init();
}

void UNetUnit::Tick(float DeltaTime)
{
	if (NetHandler.get() != nullptr) {
		NetHandler->Tick(DeltaTime);
	}

	// Check the 'In', and publish task.
	for (auto It = In.begin(); It != In.end(); ++It) {
		Dispatcher->PublishTask(*It);
		In.erase(It);
	}

}

void UNetUnit::Shutdown()
{
}

void UNetUnit::_FetchPackagesFromNetHandler()
{

}

void UNetUnit::_PushPackagesIntoNetHandler()
{
}

void UNetUnit::CheckAndUpdateRemoteObjects()
{
	

}

void UNetUnit::CheckAndUpdateLocalObjects()
{
	
}

void UNetUnit::ForceCheckAndUpdateRemoteObject(std::shared_ptr<class UObject> SpecificObjectPtr)
{
}

void UNetUnit::ForceCheckAndUpdateLocalObjects(std::shared_ptr<class UObject> SpecificObjectPtr)
{
}
