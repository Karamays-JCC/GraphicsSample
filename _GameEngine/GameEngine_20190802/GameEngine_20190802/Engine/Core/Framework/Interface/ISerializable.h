#pragma once
#include <string>

class ISerializable
{
public:
	virtual void Deserialize(std::string SerializedStream) = 0;
	
	virtual std::string Serialize() = 0;

	virtual std::string GetGUID() = 0;

};

