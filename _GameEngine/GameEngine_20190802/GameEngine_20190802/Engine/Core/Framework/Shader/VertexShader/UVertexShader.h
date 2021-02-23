#pragma once
#include <Framework/Shader/UShader.h>

#include <string>
#include <iostream>

class UVertexShader final : public UShader
{
public:
	UVertexShader();

	~UVertexShader();

public:
	virtual void Create(const std::string& FilePath) override;

	virtual void AttachTo(GLuint ProgramID) override;

	virtual void DetachFrom(GLuint ProgramID) override;

private:
	static std::string SourceCode; // current class

	static const EUShaderType Type; // current class

	EUShaderState State; // current class, maybe different in other subclass

public:
	inline bool IsAvaliable() const { return State == EUShaderState::Created; };
	inline bool IsWorking() const { return State == EUShaderState::Attached; };
	inline EUShaderType GetShaderType() const { return Type; };
	inline EUShaderState GetShaderState() const { return State; };

};

