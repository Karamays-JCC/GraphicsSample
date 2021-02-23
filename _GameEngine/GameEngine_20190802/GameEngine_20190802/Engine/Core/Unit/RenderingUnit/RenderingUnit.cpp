#include "RenderingUnit.h"
#include <Framework/GameInstance/UGameInstance.h>
#include <Framework/RenderableObject/RenderableObject.h>
#include <Framework/Level/ULevel.h>

RenderingUnit::RenderingUnit() :
	WindowPtr(NULL),
	ViewMatrix(1.0f),
	ProjectionMatrix(1.0f)
{
}

RenderingUnit::~RenderingUnit()
{
}

void RenderingUnit::InitContext()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	WindowPtr = glfwCreateWindow(800, 600, "OpenGL", NULL, NULL);
	if (WindowPtr == NULL)
	{
		std::cout << "ERROR: Creating window failed !" << std::endl;
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(WindowPtr);
	glfwSetInputMode(WindowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "ERROR: Initializing GLEW failed." << std::endl;
		glfwTerminate();
		return;
	}
}

void RenderingUnit::InitComponents()
{
	UnitCamera.SetViewMatrixWith(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f));
}

void RenderingUnit::SetUnitOption()
{
	glViewport(0, 0, 800, 600);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_FALSE);
	glDepthFunc(GL_LESS); // Default

}

void RenderingUnit::Tick(float DeltaTime)
{
	_ProcessInput(WindowPtr, DeltaTime);
	_PerRender(DeltaTime);
	_Render(DeltaTime);
	_PostRender(DeltaTime);
}

void RenderingUnit::Shutdown()
{
}

void RenderingUnit::_ProcessInput(GLFWwindow* WindowPtr, float DeltaTime)
{
	if (glfwGetKey(WindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(WindowPtr, true);
	}
	
	// move forward(W, S)
	if (glfwGetKey(WindowPtr, GLFW_KEY_W) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_W, DeltaTime);
	}
	
	if (glfwGetKey(WindowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_S, DeltaTime);
	}

	// move right (A, D)
	if (glfwGetKey(WindowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_A, DeltaTime);
	}
	
	if (glfwGetKey(WindowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_D, DeltaTime);
	}

	// move up (SPACE, X)
	if (glfwGetKey(WindowPtr, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_Space, DeltaTime);
	}
	
	if (glfwGetKey(WindowPtr, GLFW_KEY_X) == GLFW_PRESS)
	{
		GlobalCallbackList.NotifyAxisFunc(EKey::Key_X, DeltaTime);
	}
	
	// Switch
	if (glfwGetKey(WindowPtr, GLFW_KEY_0) == GLFW_PRESS)
	{
		GEngine->GameInstance->SwitchLevel("DefaultLevel");
	}

	if (glfwGetKey(WindowPtr, GLFW_KEY_1) == GLFW_PRESS)
	{
		GEngine->GameInstance->SwitchLevel("Demo01");
	}

}

void RenderingUnit::_PerRender(float DeltaTime)
{
	glClearColor(0, 0, 0, 1.0f);
	//glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer
}

void RenderingUnit::_Render(float DeltaTime)
{
	UnitCamera.Tick(DeltaTime);
	
	_RecomputeMatrix();
	
	auto Level = GEngine->GameInstance->GetCurrentLevel();

	if (Level.get() != nullptr)
	{
		for (auto& Object : Level->GetRenderableObjectGroup())
		{
			Object->Draw(DeltaTime, ProjectionMatrix, ViewMatrix, UnitCamera.GetPosition());
		}
	}
	
}

void RenderingUnit::_PostRender(float DeltaTime)
{
	glfwSwapBuffers(WindowPtr);
	glfwPollEvents();
}

void RenderingUnit::_RecomputeMatrix()
{
	// ModelMatrix = ...
	ViewMatrix = UnitCamera.GetViewMatrix();
	ProjectionMatrix = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}
