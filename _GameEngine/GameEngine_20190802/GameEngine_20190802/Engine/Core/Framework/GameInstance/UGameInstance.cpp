#include "UGameInstance.h"
#include <Framework/RenderableObject/RenderableObject.h>
#include <Framework/Level/ULevel.h>
#include <Framework/Light/DirectionalLight/UDirectionalLight.h>
#include <Framework/Light/PointLight/UPointLight.h>
#include <Framework/Light/SpotLight/USpotLight.h>

UGameInstance::UGameInstance()
{
}

UGameInstance::~UGameInstance()
{
}

void UGameInstance::Init()
{
	_LoadDefaultLevels();
	_LoadDefaultWorkingLevel();
}

void UGameInstance::Tick(float DeltaTime)
{

}

void UGameInstance::StartGameInstance()
{
}

void UGameInstance::UpdateActorByNet()
{
}

void UGameInstance::AddNewLevel(const std::shared_ptr<ULevel>& NewLevel)
{
	Levels.emplace(NewLevel->LevelName, NewLevel);
}

void UGameInstance::SwitchLevel(const std::string& LevelName)
{
	auto It = Levels.find(LevelName);
	if (It != Levels.end()) {
		CurrentLevel = It->second;
	}
}

void UGameInstance::_LoadDefaultLevels()
{
	std::shared_ptr<ULevel> Level = std::make_shared<ULevel>();
	Level->LevelName = "DefaultLevel";

	glm::vec3 cubePositions[] = {
		glm::vec3(0.0f,  0.0f,  0.0f),
		glm::vec3(2.0f,  5.0f, -15.0f),
		glm::vec3(-1.5f, -2.2f, -2.5f),
		glm::vec3(-3.8f, -2.0f, -12.3f),
		glm::vec3(2.4f, -0.4f, -3.5f),
		glm::vec3(-1.7f,  3.0f, -7.5f),
		glm::vec3(1.3f, -2.0f, -2.5f),
		glm::vec3(1.5f,  2.0f, -2.5f),
		glm::vec3(1.5f,  0.2f, -1.5f),
		glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	Level->GetDirectionalLightGroup().push_back(std::shared_ptr<UDirectionalLight>(new UDirectionalLight()));
	Level->GetPointLightGroup().push_back(std::shared_ptr<UPointLight>(new UPointLight()));
	Level->GetSpotLightGroup().push_back(std::shared_ptr<USpotLight>(new USpotLight()));
	Level->GetSpotLightGroup().push_back(std::shared_ptr<USpotLight>(new USpotLight()));
	Level->GetSpotLightGroup()[1]->Position = glm::vec3(0.0f, 5.0f, 0.0f);

	for (size_t i = 0; i < 10; ++i)
	{
		Level->GetRenderableObjectGroup().push_back(std::shared_ptr<RenderableObject>(new RenderableObject(cubePositions[i], Level)));
	}

	Level->GetRenderableObjectGroup()[0]->SetGUID("1");

	Levels.emplace(Level->LevelName, Level);


	std::shared_ptr<ULevel> Level1 = std::make_shared<ULevel>();
	Level1->LevelName = "Demo01";

	Level1->GetDirectionalLightGroup().push_back(std::shared_ptr<UDirectionalLight>(new UDirectionalLight()));
	
	for (size_t i = 0; i < 8; ++i)
	{
		Level1->GetRenderableObjectGroup().push_back(std::shared_ptr<RenderableObject>(new RenderableObject(cubePositions[i], Level1)));
	}

	Levels.emplace(Level1->LevelName, Level1);
}

void UGameInstance::_LoadDefaultWorkingLevel()
{
	SwitchLevel("DefaultLevel");
}

bool UGameInstance::AddLevel(std::shared_ptr<class ULevel> InLevel)
{
	return false;
}

bool UGameInstance::RemoveLevel(std::shared_ptr<class ULevel> InLevel)
{
	return false;
}

const std::shared_ptr<class ULevel>& UGameInstance::GetCurrentLevel() const
{
	return CurrentLevel;
}

const std::unordered_map<std::string, std::shared_ptr<class ULevel>>& UGameInstance::GetLevels() const
{
	return Levels;
}

const std::shared_ptr<class ULevel>& UGameInstance::GetLevel(int Index) const
{
	return CurrentLevel;
}

const std::shared_ptr<class ULevel>& UGameInstance::GetLevel(const std::string& LevelName) const
{
	return CurrentLevel;
}
