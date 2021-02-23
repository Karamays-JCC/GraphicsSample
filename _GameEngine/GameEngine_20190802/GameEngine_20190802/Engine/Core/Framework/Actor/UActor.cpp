#include "UActor.h"
#include <Framework/RenderableObject/RenderableObject.h>
#include <Framework/Mesh/UMesh.h>
#include <Framework/Model/UModel.h>
#include <Framework/Utils/FileLoader/UFileLoader.h>
#include <Framework/Utils/UGUIDMaker.h>

UActor::UActor() :
	GUIDString(UGUIDMaker::GenerateGUID())
{
}

UActor::~UActor()
{
}

void UActor::Init()
{
}

void UActor::Tick(float Default)
{
}

void UActor::Deserialize(std::string SerializedStream)
{
}

std::string UActor::Serialize()
{
	return std::string();
}

std::string UActor::GetGUID()
{
	return GUIDString;
}

void UActor::AddNewMesh(const std::shared_ptr<UMesh>& NewMesh)
{

}
