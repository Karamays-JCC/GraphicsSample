#include "UDirectionalLight.h"

UDirectionalLight::UDirectionalLight() :
	Angle(glm::vec3(glm::radians(45.0f), 0, 0)),
	Color(glm::vec3(1.0f, 1.0f, 1.0f))
{
	_UpdateDirection();
}

UDirectionalLight::UDirectionalLight(glm::vec3 _Angle, glm::vec3 _Color) : 
	Direction(),
	Angle(_Angle),
	Color(_Color)
{
	_UpdateDirection();
}

UDirectionalLight::~UDirectionalLight()
{
}

void UDirectionalLight::Tick(float DeltaTime)
{
	_UpdateDirection();
}

void UDirectionalLight::_UpdateDirection()
{
	Direction = glm::vec3(0, 0, 1.0f);
	Direction = glm::rotateZ(Direction, Angle.z);
	Direction = glm::rotateX(Direction, Angle.x);
	Direction = glm::rotateY(Direction, Angle.y);
	Direction *= -1.0f;
}
