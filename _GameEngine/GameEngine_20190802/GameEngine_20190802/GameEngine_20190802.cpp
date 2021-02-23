// GameEngine_20190802.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Global/Global.h>
#include <Unit/RenderingUnit/RenderingUnit.h>
#include <Callback/CallbackList/UCallbackList.h>
#include <iostream>
#include <memory>


float lastX = 0;
float lastY = 0;
bool mouse_first = true;
void mouse_callback(GLFWwindow* Window, double xPos, double yPos)
{
	if (mouse_first == true)
	{
		lastX = xPos;
		lastY = yPos;
		mouse_first = false;
	}

	float deltaX = xPos - lastX;
	float deltaY = yPos - lastY;

	lastX = xPos;
	lastY = yPos;

	GEngine->InternalRenderingUnit->GetUnitCamera().Rotate(deltaX, deltaY);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

int main()
{
	GEngine = std::shared_ptr<Engine>(Engine::GetInstance());

	GEngine->Init();
	glfwSetCursorPosCallback(GEngine->InternalRenderingUnit->GetWindowPtr(), mouse_callback);
	glfwSetScrollCallback(GEngine->InternalRenderingUnit->GetWindowPtr(), scroll_callback);
	GEngine->StartMainLoop();
	GEngine->Shutdown();
}