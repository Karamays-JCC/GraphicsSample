#pragma once
#include <Global/Global.h>

class ULevel
{
public:
	ULevel();
	virtual ~ULevel();

public:
	std::string LevelName;

private:
	std::vector<std::shared_ptr<class UDirectionalLight>> DirectionalLightGroup;

	std::vector<std::shared_ptr<class UPointLight>> PointLightGroup;

	std::vector<std::shared_ptr<class USpotLight>> SpotLightGroup;

	std::vector<std::shared_ptr<class RenderableObject>> RenderableObjectGroup;

public:
	inline std::vector<std::shared_ptr<class UDirectionalLight>>& GetDirectionalLightGroup() { return DirectionalLightGroup; };
	inline std::vector<std::shared_ptr<class UPointLight>>& GetPointLightGroup() { return PointLightGroup; };
	inline std::vector<std::shared_ptr<class USpotLight>>& GetSpotLightGroup() { return SpotLightGroup; };
	inline std::vector<std::shared_ptr<class RenderableObject>>& GetRenderableObjectGroup() { return RenderableObjectGroup; };

};

