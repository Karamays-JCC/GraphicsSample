#pragma once
#include <Global/Global.h>

#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <string>

class UFileLoader
{
public:
	static std::string LoadFile(const std::string& FilePath);
};

