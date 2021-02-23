#include "UDispatcher.h"
#include <Framework/Net/NetPackage/UNetPackage.h>
#include <Framework/RenderableObject/RenderableObject.h>
#include <Framework/GameInstance/UGameInstance.h>
#include <Framework/Level/ULevel.h>

UDispatcher::UDispatcher()
{
}

UDispatcher::~UDispatcher()
{
}

void UDispatcher::Init()
{

}

void UDispatcher::PublishTask(std::shared_ptr<class UNetPackage> Package)
{
	switch (Package->Command)
	{
	case ECommand::Type::ClientLogin:
		ClientLogin(Package->Content);
		break;
	case ECommand::Type::ClientLogout:

		break;
	case ECommand::Type::ClientRPC:

		break;
	case ECommand::Type::ClientUpdate:
		ClientUpdate(Package->Content);
		break;
	default:
		break;
	}
}

void UDispatcher::ClientUpdate(const std::string& Content)
{
	// Parse the str.
	nlohmann::json tempJson(Content);
	std::string ObjectGUID = tempJson["ObjectGUID"].get<std::string>();
	std::string ObjectContent = tempJson["ObjectContent"].get<std::string>();

	// Check server

	//  Find the target object.
	UObject* UpdatedObject = nullptr;
	auto RenderableObjects = GEngine->GameInstance->GetCurrentLevel()->GetRenderableObjectGroup();
	for (auto It = RenderableObjects.begin(); It != RenderableObjects.end(); ++It) {
		if ((*It)->GetGUID() == ObjectGUID) {
			UpdatedObject = (*It).get();
			break;
		}
	}

	// Try to update the object.
	if (UpdatedObject == nullptr) return;
	UpdatedObject->Deserialize(ObjectContent);
}

void UDispatcher::ClientLogin(const std::string& Content)
{
}
