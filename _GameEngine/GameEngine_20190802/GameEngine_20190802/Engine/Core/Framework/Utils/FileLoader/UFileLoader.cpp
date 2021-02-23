#include "UFileLoader.h"

std::string UFileLoader::LoadFile(const std::string& FilePath)
{
	std::ifstream File;
	std::string Content;
	File.exceptions(std::fstream::failbit | std::fstream::badbit);
	try
	{
		File.open(FilePath);
		std::stringstream SStream;
		SStream << File.rdbuf();
		Content = SStream.str();
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: [ " << e.what() << " ]" << std::endl;
		return "";
	}
	
	return  Content;
}
