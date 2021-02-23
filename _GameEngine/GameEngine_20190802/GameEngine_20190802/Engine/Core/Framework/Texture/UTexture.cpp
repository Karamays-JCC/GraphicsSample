#include "UTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "..//..//..//Dependencies/stb_image.h"

UTexture::UTexture() :
	Data(nullptr),
	Width(0),
	Height(0),
	NRChannel(0),
	Slot(GL_TEXTURE0)
{
}

UTexture::UTexture(const std::string& FilePath, GLenum Slot) :
	Data(nullptr),
	Width(0),
	Height(0),
	NRChannel(0),
	Slot(Slot)
{
	_LoadTexture(FilePath);
}

UTexture::~UTexture()
{
}

void UTexture::_LoadTexture(const std::string& FilePath)
{
	stbi_set_flip_vertically_on_load(true);
	Data = stbi_load(FilePath.c_str(), &Width, &Height, &NRChannel, 0);

	if (Data == nullptr)
	{
		std::cout << "load fail" << std::endl;
	}
}
