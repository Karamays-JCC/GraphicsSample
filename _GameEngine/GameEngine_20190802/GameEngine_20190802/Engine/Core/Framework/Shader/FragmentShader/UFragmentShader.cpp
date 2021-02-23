#include "UFragmentShader.h"
#include <Framework/ShaderFilePool/UShaderFilePool.h>

UFragmentShader::UFragmentShader() :
	State(EUShaderState::Null)
{
}

UFragmentShader::~UFragmentShader()
{
}

void UFragmentShader::Create(const std::string& FilePath)
{
	if (State != EUShaderState::Null) return;

	ShaderID = glCreateShader(static_cast<GLenum>(Type));

	if (ShaderID != 0)
	{
		if (SourceCode == "")
		{
			try
			{
				SourceCode = FilePool.FindFile(FilePath);
			}
			catch (const std::exception& e)
			{
				std::cout << "Exception: " << e.what() << std::endl;
				_Destroy(ShaderID);
			}
		}
	}

	if (SourceCode != "")
	{
		const GLchar* SourceCodePtr = SourceCode.c_str();
		glShaderSource(ShaderID, 1, &SourceCodePtr, NULL);
		glCompileShader(ShaderID);

		if (!_CheckCompilation(ShaderID))
		{
			_Destroy(ShaderID);
			return;
		}

		State = EUShaderState::Created;
	}

}

void UFragmentShader::AttachTo(GLuint ProgramID)
{
	if (State != EUShaderState::Created) return;

	glAttachShader(ProgramID, ShaderID);

	State = EUShaderState::Attached;
}

void UFragmentShader::DetachFrom(GLuint ProgramID)
{
	if (State != EUShaderState::Attached) return;

	// Detach this shader from the program, if the shader has been taged with 'can be deleted', it will be deleted immediately.
	glDetachShader(ProgramID, ShaderID);

	State = EUShaderState::Created;
}

std::string UFragmentShader::SourceCode = "";
const EUShaderType UFragmentShader::Type = EUShaderType::Fragment;