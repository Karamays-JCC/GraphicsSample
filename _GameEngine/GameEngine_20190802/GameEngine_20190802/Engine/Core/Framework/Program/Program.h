#pragma once
#include <Global/Global.h>

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

struct ShaderGroupFilePath
{
	std::string VertexShader;
	std::string TESSControlShader;
	std::string TESSEvaluationShader;
	std::string GeometryShader;
	std::string FragmentShader;
};

struct VertexGroup
{
	std::vector<std::pair<std::string, GLuint>> Index_NameAndSize;
	GLuint TotalSize;
	GLuint Stride;

	GLfloat* Vertices;

};

class Program
{
public:
	Program();
	~Program();

public:
	void Create(ShaderGroupFilePath FilePath);

	void Use();

	void PrepareData(VertexGroup _VertexGroup);

	void BindTexture(class UTexture& Texture);

	void Draw(GLenum mode, GLint first, GLsizei count);

	void Detach();

private:
	std::shared_ptr<class UVertexShader> VertexShader;

	std::shared_ptr<class UTESSControlShader> TESSControlShader;

	std::shared_ptr<class UTESSEvaluationShader> TESSEvaluationShader;

	std::shared_ptr<class UGeometryShader> GeometryShader;

	std::shared_ptr<class UFragmentShader> FragmentShader;

	GLuint ID;

	bool bDataPrepared;

private:
	bool _CheckLink();

public:
	void UpdateUniformMatrix4(const GLchar* Name, const glm::mat4 Value);
	void UpdateUniform1f(const GLchar* Name, GLfloat Value);
	void UpdateUniform3f(const GLchar* Name, GLfloat V0, GLfloat V1, GLfloat V2);
	void UpdateUniform3f(const GLchar* Name, glm::vec3 Value);
	void UpdateUniformSubroutine(const GLchar* SubroutineUniformName, const GLchar* SelectedSubroutineName, GLenum ShaderType);
	void UpdateUniform1i(const GLchar* Name, GLint Slot); //GL_TEXTURE0 + Slot

public:
	void UpdateDirectionalLights(const std::vector<std::shared_ptr<class UDirectionalLight>>& DirectionalLights);
	void UpdatePointLights(const std::vector<std::shared_ptr<class UPointLight>>& PointLights);
	void UpdateSpotLights(const std::vector<std::shared_ptr<class USpotLight>>& SpotLights);
};

