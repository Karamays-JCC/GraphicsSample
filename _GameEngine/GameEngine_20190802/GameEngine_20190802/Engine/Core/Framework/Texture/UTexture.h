#pragma once
#include <Global/Global.h>

#include <string>
#include <iostream>

class UTexture
{
public:
	UTexture();
	UTexture(const std::string& FilePath, GLenum Slot);
	virtual ~UTexture();

	
private:
	std::string TextureFilePath;
	
	unsigned char* Data;

private:

	void _LoadTexture(const std::string& FilePath);

public:
	const unsigned char* GetByteData() const { return Data; }

	int Width;
	int Height;
	int NRChannel;
	GLenum Slot;

	GLuint Buffer;
};

