#pragma once
#include <Engine/Engine.h>
#include <Framework/Camera/Camera.h>

#include <vector>
#include <memory>

class RenderingUnit final
{
public:
	RenderingUnit();
	~RenderingUnit();

public:
	void InitContext(); // Do works about glfw/glew/etc

	void InitComponents(); // Do all the members' initialization work.

	void SetUnitOption(); //  Set mode or some options about rendering. // Power can be took over.

	void Tick(float DeltaTime); // The engine main loop will call it.

	void Shutdown(); // Shutdown the RenderingUnit, dod all the members' Shutdown.

private:
	void _ProcessInput(GLFWwindow* WindowPtr, float DeltaTime); // Process input must be finished before all rendering work start.


	void _PerRender(float DeltaTime); // Before render, do some clean work.

	void _Render(float DeltaTime); // Do real-time data update and send rendering command.

	void _PostRender(float DeltaTime); // After the rendering, do some clean work.


	void _RecomputeMatrix(); // Called by _Render(), after Camera.Tick(), before Object->Draw()

public:
	std::shared_ptr<class Engine> GEngine;

private:

	struct GLFWwindow* WindowPtr; // Take over the window ptr from OpenGL center.

	class Camera UnitCamera; // Manager the camera, compute the matrix according to this.

	glm::mat4 ViewMatrix; // ViewMatrix from camera, updated by camera.

	glm::mat4 ProjectionMatrix; // updated with window size, managed by RenderingUnit.

public:
	inline Camera& GetUnitCamera() { return UnitCamera; };
	inline struct GLFWwindow* GetWindowPtr() { return WindowPtr; };

};

