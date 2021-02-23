#pragma once
#include <Global/Global.h>

class UPointLight
{
public:
	UPointLight();
	~UPointLight();

	glm::vec3 Position;

	glm::vec3 Angle;

	glm::vec3 Direction;

	glm::vec3 Color;

	float Constant;

	float Linear;

	float Quadratic;

};

