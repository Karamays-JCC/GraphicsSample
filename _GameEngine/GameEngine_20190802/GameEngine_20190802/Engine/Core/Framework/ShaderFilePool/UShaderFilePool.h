#pragma once

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <unordered_map>

class UShaderFilePool
{
public:
	UShaderFilePool();
	~UShaderFilePool();

public:
	void Tick(float DeltaTime);

	const std::string& FindFile(const std::string& FilePath);

private:

	std::unordered_map<std::string, const std::string> FileMap;

	void _LoadFileFromDisk(const std::string& FilePath);

	void _TryToReleaseFile();

};

