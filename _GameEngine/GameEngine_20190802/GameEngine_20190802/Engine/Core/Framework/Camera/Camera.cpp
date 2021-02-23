#include "Camera.h"

Camera::Camera() :
	AxisSpeed(5.0f, 5.0f, 5.0f),
	ViewMatrix(1.0f),
	bAcceptInput(false),
	ProstheticUp(0.0f, 1.0f, 0.0f)
{
	GlobalCallbackList.BindAxis("MoveForward", this, &Camera::MoveForward);
	GlobalCallbackList.BindAxis("MoveRight", this, &Camera::MoveRight);
	GlobalCallbackList.BindAxis("MoveUp", this, &Camera::MoveUp);
}

Camera::~Camera()
{
}

void Camera::SetViewMatrixWith(glm::vec3 CameraPosition)
{
	Position = CameraPosition;
	TargetPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	CameraDirection = glm::normalize(Position - TargetPosition);
	CameraRight = glm::normalize(glm::cross(CameraDirection, ProstheticUp));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

void Camera::SetViewMatrixWith(glm::vec3 CameraPosition, glm::vec3 NewTargetPosition)
{
	Position = CameraPosition;
	TargetPosition = NewTargetPosition;
	CameraDirection = glm::normalize(CameraPosition - TargetPosition);
	CameraRight = glm::normalize(glm::cross(CameraDirection, ProstheticUp));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

void Camera::SetViewMatrixWith(glm::vec3 CameraPosition, float NewPitch, float NewYaw)
{
	Position = CameraPosition;
	
	Pitch = NewPitch;
	Yaw = NewYaw;

	CameraDirection.x = glm::cos(Pitch) * glm::sin(Yaw);
	CameraDirection.y = glm::sin(Pitch);
	CameraDirection.z = glm::cos(Pitch) * glm::cos(Yaw);

	CameraRight = glm::normalize(glm::cross(CameraDirection, ProstheticUp));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

void Camera::MoveForward(float Value)
{
	Position.z += AxisSpeed.z * Value;
}

void Camera::MoveRight(float Value)
{
	Position.x += AxisSpeed.x * Value;
}

void Camera::MoveUp(float Value)
{
	Position.y += AxisSpeed.y * Value;
}

void Camera::Tick(float DeltaTime)
{
	_RecomputeCameraDirection();
	_RecomputeViewMatrix();
}

void Camera::AcceptInput()
{
	bAcceptInput = true;
}

void Camera::RejectInput()
{
	bAcceptInput = false;
}

void Camera::Rotate(float DeltaX, float DeltaY)
{
	Pitch -= DeltaY * 0.005f;
	Yaw -= DeltaX * 0.005f;
}

void Camera::_RecomputeCameraDirection()
{
	CameraDirection.x = glm::cos(Pitch) * glm::sin(Yaw);
	CameraDirection.y = glm::sin(Pitch);
	CameraDirection.z = glm::cos(Pitch) * glm::cos(Yaw);

	CameraRight = glm::normalize(glm::cross(CameraDirection, ProstheticUp));
	CameraUp = glm::normalize(glm::cross(CameraDirection, CameraRight));
}

void Camera::_RecomputeViewMatrix()
{
	// CameraPosition, TargetPosition, ProstheticUp
	ViewMatrix = glm::lookAt(Position, Position + CameraDirection, ProstheticUp);
}
