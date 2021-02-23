#pragma once
#include <Global/Global.h>
#include <Framework/Object/UObject.h>

class UGameInstance : public UObject
{
public:
	UGameInstance();
	virtual ~UGameInstance();

public:
	virtual void Init();

	virtual void Tick(float DeltaTime);

public:
	virtual void StartGameInstance();

	void UpdateActorByNet();
	
	void AddNewLevel(const std::shared_ptr<class ULevel>& NewLevel);

	void SwitchLevel(const std::string& LevelName);

private:
	void _LoadDefaultLevels();
	
	void _LoadDefaultWorkingLevel();

private:
	/* Current working level, this level will be rendered. */
	std::shared_ptr<class ULevel> CurrentLevel;

	/* Manage all the levels, LevelName - LevelPtr*/
	std::unordered_map<std::string, std::shared_ptr<class ULevel>> Levels;

protected:
	std::vector<std::shared_ptr<class UObject>> ReferencedObjects;

public:
	const std::shared_ptr<class ULevel>& GetLevel(int Index) const;

	const std::shared_ptr<class ULevel>& GetLevel(const std::string& LevelName) const;
	
	const std::shared_ptr<class ULevel>& GetCurrentLevel() const;
	
	const std::unordered_map<std::string, std::shared_ptr<class ULevel>>& GetLevels() const;

	bool AddLevel(std::shared_ptr<class ULevel> InLevel);

	bool RemoveLevel(std::shared_ptr<class ULevel> InLevel);

};

