#include "Engine.h"
#include <Unit/NetUnit/UNetUnit.h>
#include <Unit/PhysicsUnit/PhysicsUnit.h>
#include <Unit/RenderingUnit/RenderingUnit.h>
#include <Framework/GameInstance/UGameInstance.h>

Engine* Engine::GetInstance()
{
	if (Instance == nullptr)
	{
		Instance = new Engine();
		return Instance;
	}
	return Instance;
}

Engine::~Engine()
{
	if (Instance != nullptr)
	{
		delete Instance;
	}
}

Engine::Engine() :
	InternalPhysicsUnit(),
	InternalRenderingUnit(),
	bShouldExit(false)
{
}

void Engine::Init()
{
	std::cout << "Init as a server ?" << std::endl;
	std::cout << "Y/N :";
	char InitOption;
	bool bInitAsServer = true;
	std::cin >> InitOption;
	if (InitOption == 'Y')
		bInitAsServer = true;
	else if (InitOption == 'N')
		bInitAsServer = false;
		
	// Create the Units
	InternalNetUnit = std::make_shared<UNetUnit>(bInitAsServer);
	InternalPhysicsUnit = std::make_shared<PhysicsUnit>();
	InternalRenderingUnit = std::make_shared<RenderingUnit>();

	// Do the Unit Init work
	InternalNetUnit->GEngine = std::shared_ptr<Engine>(GetInstance());
	InternalNetUnit->Init();

	InternalRenderingUnit->GEngine = std::shared_ptr<Engine>(GetInstance());
	InternalRenderingUnit->InitContext();
	InternalRenderingUnit->InitComponents();
	InternalRenderingUnit->SetUnitOption();

	// Create game instance
	GameInstance = std::make_shared<UGameInstance>();
	GameInstance->Init();
}

void Engine::StartMainLoop()
{
	float DeltaTime = 0.0f;
	float AccumulatedTime = 0.0f;
	int AccumulatedFrameNum = 0;

	while (!bShouldExit)
	{
		//~Begin Time
		std::chrono::steady_clock::time_point TimePointBegin = std::chrono::steady_clock::now();

		//~Begin Core Tick
		InternalNetUnit->Tick(DeltaTime);
		InternalPhysicsUnit->Tick(DeltaTime);
		InternalRenderingUnit->Tick(DeltaTime);
		//~End Core Tick

		std::chrono::steady_clock::time_point TimePointEnd = std::chrono::steady_clock::now();
		std::chrono::duration<float> TimeSpan = std::chrono::duration_cast<std::chrono::duration<float>>(TimePointEnd - TimePointBegin);
		DeltaTime = TimeSpan.count();
		//~End Time

		//~Begin Caculate FPS
		AccumulatedFrameNum++;
		AccumulatedTime += DeltaTime;
		if (AccumulatedTime > 1.0f) {
			float FPS = AccumulatedFrameNum / (AccumulatedTime);
			AccumulatedFrameNum = 0;
			AccumulatedTime = 0;
		}
		//~End Caculate FPS
	}

	std::cout << "Engine main loop exit." << std::endl;
}

void Engine::Shutdown()
{
	//InternalNetUnit.Shutdown();
	InternalPhysicsUnit->Shutdown();
	InternalRenderingUnit->Shutdown();
}

Engine* Engine::Instance = nullptr;
