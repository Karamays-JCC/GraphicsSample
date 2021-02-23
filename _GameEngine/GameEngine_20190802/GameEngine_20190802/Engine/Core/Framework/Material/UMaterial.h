#pragma once
#include <Global/Global.h>

class UMaterial
{
public:
	UMaterial();
	virtual ~UMaterial();

public:
	void LoadToGPU();

	void Tick(float DeltaTime);

public:

	glm::vec3 AmbientScale;

	glm::vec3 DiffuseScale;

	glm::vec3 SpecularScale;

	float Shininess;

	bool bUseTexture;

	std::shared_ptr<class UTexture> AmbientScaleOverridden;

	std::shared_ptr<class UTexture> DiffuseScaleOverridden;

	std::shared_ptr<class UTexture> SpecularScaleOverridden;

private:
	std::string MaterialFilePath;

};

