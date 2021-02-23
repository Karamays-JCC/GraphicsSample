#pragma once
#include <Global/Global.h>

class USpotLight
{
public:
	USpotLight();
	USpotLight(glm::vec3 _Position, glm::vec3 _Rangle, glm::vec3 _Color);
	~USpotLight();

public:
	void Tick(float DeltaTime);
	
	glm::vec3 Position;

	glm::vec3 Angle;

	glm::vec3 Direction;

	glm::vec3 Color;

	float CosPhy;

private:
	void UpdateDirection();
	
};

