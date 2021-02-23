#include "Program.h"
#include <Framework/Shader/VertexShader/UVertexShader.h>
#include <Framework/Shader/TESSControlShader/UTESSControlShader.h>
#include <Framework/Shader/TESSEvaluationShader/UTESSEvaluationShader.h>
#include <Framework/Shader/GeometryShader/UGeometryShader.h>
#include <Framework/Shader/FragmentShader/UFragmentShader.h>
#include <Framework/Texture/UTexture.h>
#include <Framework/Light/DirectionalLight/UDirectionalLight.h>
#include <Framework/Light/PointLight/UPointLight.h>
#include <Framework/Light/SpotLight/USpotLight.h>

Program::Program() :
	VertexShader(nullptr),
	TESSControlShader(nullptr),
	TESSEvaluationShader(nullptr),
	GeometryShader(nullptr),
	FragmentShader(nullptr),
	bDataPrepared(false)
{
}

Program::~Program()
{
	glDeleteProgram(ID);
}

void Program::Create(ShaderGroupFilePath FilePath)
{
	ID = glCreateProgram();
	if (ID <= 0) return;

	if (FilePath.VertexShader != "")
	{
		VertexShader = std::shared_ptr<UVertexShader>(new UVertexShader());
		VertexShader->Create(FilePath.VertexShader);
		VertexShader->AttachTo(ID);
	}
	if (FilePath.TESSControlShader != "")
	{
		TESSControlShader = std::shared_ptr<UTESSControlShader>(new UTESSControlShader());
		TESSControlShader->Create(FilePath.TESSControlShader);
		TESSControlShader->AttachTo(ID);
	}
	if (FilePath.TESSEvaluationShader != "")
	{
		TESSEvaluationShader = std::shared_ptr<UTESSEvaluationShader>(new UTESSEvaluationShader());
		TESSEvaluationShader->Create(FilePath.TESSEvaluationShader);
		TESSEvaluationShader->AttachTo(ID);
	}
	if (FilePath.GeometryShader != "")
	{
		GeometryShader = std::shared_ptr<UGeometryShader>(new UGeometryShader());
		GeometryShader->Create(FilePath.GeometryShader);
		GeometryShader->AttachTo(ID);
	}
	
	if (FilePath.FragmentShader != "")
	{
		FragmentShader = std::shared_ptr<UFragmentShader>(new UFragmentShader());
		FragmentShader->Create(FilePath.FragmentShader);
		FragmentShader->AttachTo(ID);
	}
	
	glLinkProgram(ID);

	_CheckLink();
}

void Program::Use()
{
	glUseProgram(ID);
}

void Program::PrepareData(VertexGroup _VertexGroup)
{
	if (bDataPrepared) 
		return;
	
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
	};

	GLuint VBO, VAO, EBO;

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const void*)(6 * sizeof(GLfloat)));

	bDataPrepared = true;
}

void Program::BindTexture(UTexture& Texture)
{
	glGenTextures(1, &Texture.Buffer);
	glActiveTexture(Texture.Slot);
	glBindTexture(GL_TEXTURE_2D, Texture.Buffer);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Texture.Width, Texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Texture.GetByteData());
	glGenerateMipmap(GL_TEXTURE_2D);
	
}

void Program::Draw(GLenum mode, GLint first, GLsizei count)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glDrawArrays(mode, first, count);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void Program::Detach()
{
	glUseProgram(0);
}

bool Program::_CheckLink()
{
	GLint bLinkSuccess = GL_FALSE;
	glGetProgramiv(ID, GL_LINK_STATUS, &bLinkSuccess);
	if (bLinkSuccess == GL_FALSE)
	{
		char LinkInfoLog[512];
		glGetProgramInfoLog(ID, sizeof LinkInfoLog, NULL, LinkInfoLog);
		std::cout << "ERROR: Link program failed [ " << LinkInfoLog << " ]" << std::endl;
		return false;
	}
	return true;
}

void Program::UpdateUniformMatrix4(const GLchar* Name, const glm::mat4 Value)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, Name), 1, GL_FALSE, glm::value_ptr(Value));
}

void Program::UpdateUniform1f(const GLchar* Name, GLfloat Value)
{
	glUniform1f(glGetUniformLocation(ID, Name), Value);
}

void Program::UpdateUniform3f(const GLchar* Name, GLfloat V0, GLfloat V1, GLfloat V2)
{
	glUniform3f(glGetUniformLocation(ID, Name), V0, V1, V2);
}

void Program::UpdateUniform3f(const GLchar* Name, glm::vec3 Value)
{
	glUniform3f(glGetUniformLocation(ID, Name), Value.x, Value.y, Value.z);
}

void Program::UpdateUniformSubroutine(const GLchar* SubroutineUniformName, const GLchar* SelectedSubroutineName, GLenum ShaderType)
{
	/*
	* We have some subroutine functions which are logic groups.
	* And also some subroutine uniforms.
	* One uniform correspond to one logic group.
	* Subroutine uniform storage a subroutine index.\
	*/
	if (ShaderType == GL_COMPUTE_SHADER) return;

	GLint SubroutineUniformLocation;
	GLuint SelectedSubroutineIndex;

	SubroutineUniformLocation = glGetSubroutineUniformLocation(ID, ShaderType, SubroutineUniformName);
	if (SubroutineUniformLocation < 0) return; // Whether it's location exists.

	SelectedSubroutineIndex = glGetSubroutineIndex(ID, ShaderType, SelectedSubroutineName);

	if (SelectedSubroutineIndex == GL_INVALID_INDEX) return; // Whether it's a valid index.
	
	GLsizei SubroutineUniformNum;
	glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &SubroutineUniformNum);
	GLuint* Indices = new GLuint[SubroutineUniformNum];
	Indices[SubroutineUniformLocation] = SelectedSubroutineIndex; // Index(SubroutineUnifomrLocation) - Value(Subroutine Index)
	glUniformSubroutinesuiv(ShaderType, SubroutineUniformNum, Indices); // Update the index
	delete[] Indices;
}

void Program::UpdateUniform1i(const GLchar* Name, GLint Slot)
{
	glUniform1i(glGetUniformLocation(ID, Name), Slot);
}

void Program::UpdateDirectionalLights(const std::vector<std::shared_ptr<UDirectionalLight>>& DirectionalLights)
{
	UpdateUniform1i("oDirectionalLightNum", DirectionalLights.size());

	for (size_t i = 0; i < DirectionalLights.size(); ++i)
	{
		std::string Str = "oDirectionalLights[";
		std::string Str1 = Str + std::to_string(i) + std::string("].Color");
		std::string Str2 = Str + std::to_string(i) + std::string("].Direction");
		UpdateUniform3f(Str1.c_str(), DirectionalLights[i]->Color);
		UpdateUniform3f(Str2.c_str(), DirectionalLights[i]->Direction);
	}
}

void Program::UpdatePointLights(const std::vector< std::shared_ptr<UPointLight>>& PointLights)
{
	UpdateUniform1i("oPointLightNum", PointLights.size());

	for (size_t i = 0; i < PointLights.size(); ++i)
	{
		std::string Str = "oPointLights[";
		std::string Str1 = Str + std::to_string(i) + std::string("].Color");
		std::string Str2 = Str + std::to_string(i) + std::string("].Position");
		std::string Str3 = Str + std::to_string(i) + std::string("].Constant");
		std::string Str4 = Str + std::to_string(i) + std::string("].Linear");
		std::string Str5 = Str + std::to_string(i) + std::string("].Quadratic");
		UpdateUniform3f(Str1.c_str(), PointLights[i]->Color);
		UpdateUniform3f(Str2.c_str(), PointLights[i]->Position);
		UpdateUniform1f(Str3.c_str(), PointLights[i]->Constant);
		UpdateUniform1f(Str4.c_str(), PointLights[i]->Linear);
		UpdateUniform1f(Str5.c_str(), PointLights[i]->Quadratic);
	}
}

void Program::UpdateSpotLights(const std::vector< std::shared_ptr<USpotLight>>& SpotLights)
{
	UpdateUniform1i("oSpotLightNum", SpotLights.size());

	for (size_t i = 0; i < SpotLights.size(); ++i)
	{
		std::string Str = "oSpotLights[";
		std::string Str1 = Str + std::to_string(i) + std::string("].Color");
		std::string Str2 = Str + std::to_string(i) + std::string("].Position");
		std::string Str3 = Str + std::to_string(i) + std::string("].Direction");
		std::string Str4 = Str + std::to_string(i) + std::string("].CosPhy");
		UpdateUniform3f(Str1.c_str(), SpotLights[i]->Color);
		UpdateUniform3f(Str2.c_str(), SpotLights[i]->Position);
		UpdateUniform3f(Str3.c_str(), SpotLights[i]->Direction);
		UpdateUniform1f(Str4.c_str(), SpotLights[i]->CosPhy);
	}
}
