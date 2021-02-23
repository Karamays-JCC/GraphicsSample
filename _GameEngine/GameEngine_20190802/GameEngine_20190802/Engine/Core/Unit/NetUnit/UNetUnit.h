#pragma once
#include <Global/Global.h>

class UNetUnit
{
public:
	UNetUnit();
	UNetUnit(bool bAsServer = false);
	virtual ~UNetUnit();

protected:
	// Specify this unit's type(server/client)
	bool bServer;

	// The handler pointer(server/client)
	// Including how to accept/send message.
	std::shared_ptr<class UNetHandler> NetHandler;

	// The dispatcher that decides how to update the object by the message package.
	// Including how to handle the " In packages ".
	std::shared_ptr<class UDispatcher> Dispatcher;

	// Remote spot' packages which are gonna using to update the engine.
	std::vector<std::shared_ptr<class UNetPackage>> In;

	// The engine's packages which are gonna sending to remote spots. 
	std::vector<std::shared_ptr<class UNetPackage>> Out;
	
public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

	virtual void Shutdown();

private: // Per frame work 
	void _FetchPackagesFromNetHandler();

	void _PushPackagesIntoNetHandler();

public: 
	/*
	* @ Called by Tick().
	* Check the local object pool.
	* Collect all levels's objects in the engine.
	*/
	void CheckAndUpdateRemoteObjects();

	/*
	* @ Called by Tick().
	* Check net buffer.
	* And parse all the net packages to update all objects.
	*/ 
	void CheckAndUpdateLocalObjects();

	/*
	* Check your specific objects
	* @SpecificObject SharedPtr for UObject
	*/
	void ForceCheckAndUpdateRemoteObject(std::shared_ptr<class UObject> SpecificObjectPtr);

	/*
	* Check
	* @SpecificObject SharedPtr for UObject
	*/
	void ForceCheckAndUpdateLocalObjects(std::shared_ptr<class UObject> SpecificObjectPtr);

public:
	std::shared_ptr<Engine> GEngine;

};

