#include "UPointLight.h"

UPointLight::UPointLight() :
	Position(glm::vec3(10.0f, 10.0f, -5.0f)),
	Color(glm::vec3(10.0f, 10.0f, 10.0f))
{
	Constant = 1.0f;
	Linear = 0.09f;
	Quadratic = 0.032f;
}

UPointLight::~UPointLight()
{
}
