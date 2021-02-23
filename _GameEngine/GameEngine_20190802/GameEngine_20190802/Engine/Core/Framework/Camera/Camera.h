#pragma once
#include <Global/Global.h>

class Camera
{
public:
	Camera();

	virtual ~Camera();

public:
	/* Reset the ViewMatrix. No guarantee of keeping constant next frame. */
	void SetViewMatrixWith(glm::vec3 CameraPosition);
	void SetViewMatrixWith(glm::vec3 CameraPosition, glm::vec3 NewTargetPosition);
	void SetViewMatrixWith(glm::vec3 CameraPosition, float NewPitch, float NewYaw);

public:
	/* Called per frame, update by input. */
	void Tick(float DeltaTime);

	/* Called per frame, update outside ViewMatrix. */
	inline const glm::mat4& GetViewMatrix() const { return ViewMatrix; };

	/* Key event called by processInput */
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveUp(float Value);

	/* Move event called by mouse_callback */
	void Rotate(float DeltaX, float DeltaY); // Called by mouse_callback()

	/* Button which controls input */
	void AcceptInput();
	void RejectInput();

protected:
	void _RecomputeCameraDirection(); //According to Pitch/Yaw/Roll
	void _RecomputeViewMatrix(); // According to CameraDirection/Target/ProstheticUp 
	
private:
	//point position
	glm::vec3 Position;
	//target point position
	glm::vec3 TargetPosition; 
	//position - target position
	glm::vec3 CameraDirection; 
	//temp up for helping computing
	glm::vec3 ProstheticUp; 
	//cross(CameraDirection, PorstheticUp)
	glm::vec3 CameraRight; 
	//cross(CameraDirection, CameraRight)
	glm::vec3 CameraUp; 

	float Pitch;
	float Yaw;
	float Roll;

	glm::vec3 AxisSpeed;
	glm::vec3 RotationSpeed; // Pitch Yaw Roll

	glm::mat4 ViewMatrix;

	bool bAcceptInput;


public:
	inline glm::vec3 GetPosition() { return Position; }
};

