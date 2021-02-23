#pragma once

#include <Global/Global.h>

struct CallbackList
{
public:
	GLFWcursorposfun mouse_callback;
	GLFWscrollfun scroll_callback;
};

class Engine
{
public:
	static Engine* GetInstance();
	virtual ~Engine();

private:
	Engine();

	static Engine* Instance;

public:
	virtual void Init();

	virtual void StartMainLoop();

	virtual void Shutdown();

public:
	bool bShouldExit;

	std::shared_ptr<class UGameInstance> GameInstance;

public:
	std::shared_ptr<class UNetUnit> InternalNetUnit;

	std::shared_ptr<class PhysicsUnit> InternalPhysicsUnit;

	std::shared_ptr<class RenderingUnit> InternalRenderingUnit;
	
};

