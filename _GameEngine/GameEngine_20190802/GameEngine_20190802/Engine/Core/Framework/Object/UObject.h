#pragma once
#include <Global/Global.h>
#include <objbase.h>

class UObject
{
public:
	UObject();
	virtual ~UObject();

private:
	bool bSelfChanged;

public:
	virtual std::string Serialize();

	virtual void Deserialize(const std::string& Content);

	virtual void SetGUID(const std::string Str);

private:
	std::string GloballyUniqueIdentifier;
	
	std::string GenerateGUID();

public:
	FORCEINLINE const std::string& GetGUID() const { return GloballyUniqueIdentifier; };

public:
	virtual void Init();
	virtual void Tick(float DeltaTime);
	virtual void Serialize(std::string& SerializedStrContainer);
	virtual void Deserialize(const nlohmann::json& ParsedStr);

};

