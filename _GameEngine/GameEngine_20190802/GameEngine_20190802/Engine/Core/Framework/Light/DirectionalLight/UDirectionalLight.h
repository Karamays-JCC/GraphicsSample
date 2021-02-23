#pragma once
#include <Global/Global.h>

class UDirectionalLight
{
public:
	UDirectionalLight();
	UDirectionalLight(glm::vec3 _Angle, glm::vec3 _Color);
	~UDirectionalLight();

public:
	void Tick(float DeltaTime);

	glm::vec3 Direction;

	glm::vec3 Color;

private:
	glm::vec3 Angle;
	
	void _UpdateDirection();

};

