#include "UNetPackage.h"
#include <Framework/GameInstance/UGameInstance.h>
#include <Framework/Level/ULevel.h>
#include <Framework/RenderableObject/RenderableObject.h>

UNetPackage::UNetPackage()
{
}

UNetPackage::~UNetPackage()
{
}

std::string UNetPackage::Serialize()
{
	nlohmann::json tempJson;

	tempJson["Command"] = CommandToString(Command);
	tempJson["Content"] = Content;
	
	std::string NetPackageContent(tempJson.dump());
	return NetPackageContent;
}

void UNetPackage::Deserialize(const std::string& Str)
{
	nlohmann::json tempJson = nlohmann::json::parse(Str);

	std::string command = tempJson.at("Command").get<std::string>();
	std::string content = tempJson.at("Content").get<std::string>();
	
	std::cout << command << std::endl;
	std::cout << content << std::endl;
	
	nlohmann::json t2 = nlohmann::json::parse(content);
	int x = t2.at("x").get<int>();
	int y = t2.at("y").get<int>();
	int z = t2.at("z").get<int>();

	std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;


	auto Group = GEngine->GameInstance->GetCurrentLevel()->GetRenderableObjectGroup();
	for (auto It = Group.begin(); It != Group.end(); ++It)
	{
		if ((*It)->GetGUID() == "1")
		{
			(*It)->GetPosition().x = x;
			(*It)->GetPosition().y = y;
			(*It)->GetPosition().z = z;
		}
	}

}

std::string ECommand::CommandToString(ECommand::Type Command)
{
	switch (Command)
	{
	case Type::ClientLogin:
		return "ClientLogin";
	case Type::ClientLogout:
		return "ClientLogout";
	case Type::ClientRPC:
		return "ClientRPC";
	case Type::ClientUpdate:
		return "ClientUpdate";
	default:
		return "";
	}
}

ECommand::Type ECommand::StringToCommand(const std::string& Str)
{
	if (Str == "ClientLogin")
		return Type::ClientLogin;
	if (Str == "ClientLogout")
		return Type::ClientLogout;
	if (Str == "ClientRPC")
		return Type::ClientRPC;
	if (Str == "ClientUpdate")
		return Type::ClientUpdate;

	return Type::Null;
}
