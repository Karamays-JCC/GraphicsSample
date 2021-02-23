#pragma once
#include <Global/Global.h>

#include <string>
#include <iostream>

enum class EUShaderType : GLenum
{
	Null								= 0,
	Vertex							= GL_VERTEX_SHADER,
	Geometry						= GL_GEOMETRY_SHADER,
	TESS_Control				= GL_TESS_CONTROL_SHADER,
	TESS_Evaluation			= GL_TESS_EVALUATION_SHADER,
	Fragment						= GL_FRAGMENT_SHADER,
	Compute						= GL_COMPUTE_SHADER
};

enum class EUShaderState : GLenum
{
	Null,
	Created,
	Attached
};

class UShader
{
public:
	UShader();

	virtual ~UShader();

public:
	virtual void Create(const std::string& FilePath);

	virtual void AttachTo(GLuint ProgramID);

	virtual void DetachFrom(GLuint ProgramID);

protected:
	bool _CheckCompilation(GLuint ShaderID);

	void _Destroy(GLuint ShaderID);

	GLuint ShaderID;

	static class UShaderFilePool FilePool;

public:
	inline GLuint GetShaderID() const { return ShaderID; };

};

