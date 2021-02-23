#include "UVertexShader.h"
#include <Framework/ShaderFilePool/UShaderFilePool.h>

UVertexShader::UVertexShader() :
	State(EUShaderState::Null)
{
}

UVertexShader::~UVertexShader()
{
}

void UVertexShader::Create(const std::string& FilePath)
{
	if (State != EUShaderState::Null) return;

	// Get the OpenGL shader id.
	ShaderID = glCreateShader(static_cast<GLenum>(Type));

	// If the object created (id is valid), load it's source code.
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

	// If source code loaded, try to compile the shader.
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

void UVertexShader::AttachTo(GLuint ProgramID)
{
	if (State != EUShaderState::Created) return;

	glAttachShader(ProgramID, ShaderID);

	State = EUShaderState::Attached;
}

void UVertexShader::DetachFrom(GLuint ProgramID)
{
	if (State != EUShaderState::Attached) return;

	// Detach this shader from the program, if the shader has been taged with 'can be deleted', it will be deleted immediately.
	glDetachShader(ProgramID, ShaderID);

	State = EUShaderState::Created;
}

std::string UVertexShader::SourceCode = "";
const EUShaderType UVertexShader::Type = EUShaderType::Vertex;