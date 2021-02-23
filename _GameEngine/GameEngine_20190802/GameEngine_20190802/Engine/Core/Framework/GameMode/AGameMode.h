#pragma once
class AGameMode
{
public:
	AGameMode();
	virtual ~AGameMode();

public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

public:

	virtual void InitGame();

	virtual void InitGameState();

	virtual void StartPlay();

	virtual void ResetLevel();

	virtual void ReturnToMainMenuHost();


	virtual void StartToLeaveMap();

	virtual void PreLogin();

	virtual void Login();

	virtual void PostLogin();

};

