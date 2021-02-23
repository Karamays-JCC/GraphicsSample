#include "UShader.h"
#include <Framework/ShaderFilePool/UShaderFilePool.h>

UShader::UShader() :
	ShaderID(0)
{
}

UShader::~UShader()
{
	_Destroy(ShaderID);
}

void UShader::Create(const std::string& FilePath)
{
}

void UShader::AttachTo(GLuint ProgramID)
{
}

void UShader::DetachFrom(GLuint ProgramID)
{
}

bool UShader::_CheckCompilation(GLuint ShaderID)
{
	GLint iResult = GL_FALSE;
	char InfoLog[512];
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &iResult);
	if (iResult != GL_TRUE)
	{
		glGetShaderInfoLog(ShaderID, 512, NULL, InfoLog);
		std::cout << "[OpenGL] : " << InfoLog << std::endl;
		return false;
	}
	return true;
}

void UShader::_Destroy(GLuint ShaderID)
{
	// tag the shader 'can be deleted', if there is no program using it.
	glDeleteShader(ShaderID);
}

UShaderFilePool UShader::FilePool;
