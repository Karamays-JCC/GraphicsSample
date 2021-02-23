#pragma once
#include <Global/Global.h>
#include <Framework/Object/UObject.h>

class UWorld final : UObject
{
public:
	UWorld();
	~UWorld();

public:
	class ULevel* PersistentLevel;

	std::vector<UObject*> ExtraReferencedObjects;

};

