#pragma once
#include <Framework/Shader/UShader.h>

class UFragmentShader final : public UShader
{
public:
	UFragmentShader();

	~UFragmentShader();

public:
	virtual void Create(const std::string& FilePath) override;

	virtual void AttachTo(GLuint ProgramID) override;

	virtual void DetachFrom(GLuint ProgramID) override;

private:
	static std::string SourceCode;

	static const EUShaderType Type;

	EUShaderState State;

public:

};

