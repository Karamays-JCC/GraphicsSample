#include "RenderableObject.h"
#include <Framework/Texture/UTexture.h>
#include <Framework/Material/UMaterial.h>
#include <Framework/Light/DirectionalLight/UDirectionalLight.h>
#include <Framework/Light/PointLight/UPointLight.h>
#include <Framework/Light/SpotLight/USpotLight.h>
#include <Framework/Level/ULevel.h>

RenderableObject::RenderableObject()
{
}

RenderableObject::~RenderableObject()
{
}

RenderableObject::RenderableObject(glm::vec3 _WorldPosition, std::shared_ptr<ULevel> _Level) :
	ModelMatrix(1.0f),
	WorldPosition(_WorldPosition),
	Level(_Level)
{
	_RecomputeMatrix();
	
	ShaderGroupFilePath FilePath;
	FilePath.VertexShader = "Engine\\Shader\\Boxes\\Box_001.vert";
	FilePath.FragmentShader = "Engine\\Shader\\Boxes\\Box_001.frag";
	_Program.Create(FilePath);

	UTexture Texture0("Assets\\Textures\\container2.png", GL_TEXTURE0);
	_Program.BindTexture(Texture0);
	UTexture Texture1("Assets\\Textures\\container2_specular.png", GL_TEXTURE1);
	_Program.BindTexture(Texture1);

	GlobalCallbackList.BindAction("Jump", EInputEvent::IE_Pressed, this, &RenderableObject::Jump);
	GlobalCallbackList.BindAction("Jump", EInputEvent::IE_Released, this, &RenderableObject::StopJumping);
}

void RenderableObject::Draw(float DeltaTime, const glm::mat4& ProjectionMatrix, const glm::mat4& ViewMatrix, glm::vec3 CameraPosition)
{
	_Program.Use();
	_Program.PrepareData(VertexGroup());

	_RecomputeMatrix();

	glm::mat4 TransformMatrix(1.0f);
	TransformMatrix = glm::rotate(TransformMatrix, (float)glfwGetTime(), glm::vec3(1.0, 1.0, 1.0));
	_Program.UpdateUniformMatrix4("TransformMatrix", TransformMatrix);
	_Program.UpdateUniformMatrix4("ModelMatrix", ModelMatrix);
	_Program.UpdateUniformMatrix4("ViewMatrix", ViewMatrix);
	_Program.UpdateUniformMatrix4("ProjectionMatrix", ProjectionMatrix);

	_Program.UpdateUniform3f("oAmbientLight.Color", glm::vec3(0.1f, 0.1f, 0.1f));
	_Program.UpdateDirectionalLights(Level->GetDirectionalLightGroup());
	_Program.UpdatePointLights(Level->GetPointLightGroup());
	_Program.UpdateSpotLights(Level->GetSpotLightGroup());

	_Program.UpdateUniform1i("oMaterial.AmbientTextureFactor", 0);
	_Program.UpdateUniform1i("oMaterial.DiffuseTextureFactor", 0);
	_Program.UpdateUniform1i("oMaterial.SpecularTextureFactor", 1);
	_Program.UpdateUniform1f("oMaterial.Shininess", 64.0f);

	_Program.UpdateUniform3f("oCameraPosition", CameraPosition);

	_Program.Draw(GL_TRIANGLES, 0, 36);
	_Program.Detach();
}

void RenderableObject::Jump()
{
	std::cout << "Jump" << std::endl;
}

void RenderableObject::StopJumping()
{
	std::cout << "StopJumping" << std::endl;
}

std::string RenderableObject::Serialize()
{
	nlohmann::json NetJson;

	NetJson["x"] = WorldPosition.x;
	NetJson["y"] = WorldPosition.y;
	NetJson["z"] = WorldPosition.z;

	std::string RenderableObjectContent(NetJson.dump());
	return RenderableObjectContent;
}

void RenderableObject::Deserialize(const std::string& Content)
{
	nlohmann::json tempJson(Content);
	WorldPosition.x = tempJson["x"].get<int>();
	WorldPosition.y = tempJson["y"].get<int>();
	WorldPosition.z = tempJson["z"].get<int>();
}

void RenderableObject::_RecomputeMatrix()
{
	ModelMatrix = glm::translate(glm::mat4(1.0f), WorldPosition);
}
