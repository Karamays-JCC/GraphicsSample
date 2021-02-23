#include "UShaderFilePool.h"
#include <Framework/Utils/FileLoader/UFileLoader.h>

UShaderFilePool::UShaderFilePool()
{
}

UShaderFilePool::~UShaderFilePool()
{
}

void UShaderFilePool::Tick(float DeltaTime)
{
	_TryToReleaseFile();
}

const std::string& UShaderFilePool::FindFile(const std::string& FilePath)
{
	auto Iterator = FileMap.find(FilePath);
	if (Iterator != FileMap.cend())
	{
		return Iterator->second;
	}
	else {
		try
		{
			_LoadFileFromDisk(FilePath);
		}
		catch (const std::exception& e)
		{
			std::cout << "Exception: " << e.what() << std::endl;
		}
		return FindFile(FilePath);
	}
}

void UShaderFilePool::_LoadFileFromDisk(const std::string& FilePath)
{
	std::string Content = UFileLoader::LoadFile(FilePath);
	FileMap.emplace(std::pair<const std::string, const std::string>(FilePath, Content));
}

void UShaderFilePool::_TryToReleaseFile()
{
}
