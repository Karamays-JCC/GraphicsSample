#include "UObject.h"

UObject::UObject()
{
	GloballyUniqueIdentifier = GenerateGUID();
}

UObject::~UObject()
{
}

std::string UObject::Serialize()
{
	return std::string();
}

void UObject::Deserialize(const std::string& Content)
{
}

void UObject::SetGUID(const std::string Str)
{
	GloballyUniqueIdentifier = Str;
}

std::string UObject::GenerateGUID()
{
	GUID guid;
	CoCreateGuid(&guid);
	char cBuffer[64] = { 0 };
	sprintf_s(cBuffer, sizeof(cBuffer),
		"{%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
		guid.Data1, guid.Data2,
		guid.Data3, guid.Data4[0],
		guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4],
		guid.Data4[5], guid.Data4[6],
		guid.Data4[7]);
	return std::string(cBuffer);
}

void UObject::Init()
{
}

void UObject::Tick(float DeltaTime)
{
}

void UObject::Serialize(std::string& SerializedStrContainer)
{
/*
	nlohmann::json ParsedStr;
	ParsedStr["GUID"] = "111";

	SerializedStr = std::move(ParsedStr.dump());
*/
}

void UObject::Deserialize(const nlohmann::json& ParsedStr)
{
	/*
	auto CEndIt = ParsedStr.cend();

	if (ParsedStr.find("GUID") != CEndIt)
		GloballyUniqueIdentifier = ParsedStr.at("GUID").get<std::string>();
	*/
}
