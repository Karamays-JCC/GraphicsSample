#pragma once
#include <Global/Global.h>
#include <Framework/Object/UObject.h>

namespace ECommand {
	enum class Type : unsigned int
	{
		Null,

		ClientLogin,
		ClientLogout,
		ClientUpdate,
		ClientRPC
	};

	Type StringToCommand(const std::string& Str);

	std::string CommandToString(Type Command);
}

class UNetPackage : public UObject
{
public:
	UNetPackage();
	virtual ~UNetPackage();

public:
	ECommand::Type Command;

	std::string Content;

public:
	virtual std::string Serialize() override;

	virtual void Deserialize(const std::string& Str) override;

};

