#include "UModel.h"
#include <Framework/Mesh/UMesh.h>

UModel::UModel(const std::string& FilePath)
{
}

UModel::~UModel()
{
}

void UModel::_LoadModel(const std::string& FilePath)
{
	Assimp::Importer importer;
	const aiScene* Scene = importer.ReadFile(FilePath, 
		aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		std::cout << "Assimp error" << std::endl;
		return;
	}

	Directory = FilePath.substr(0, FilePath.find_last_of("\\"));
	std::cout << Directory << std::endl;

}

void UModel::_ProcessNode(aiNode* Node, const aiScene* Scene)
{
	std::cout << Node->mName.data << std::endl;

	for (size_t i = 0; i < Scene->mNumMeshes; ++i)
	{
		aiMesh* curMesh = Scene->mMeshes[Node->mMeshes[i]];
		Meshes.push_back(_ProcessMesh(curMesh, Scene));
	}


	for (size_t i = 0; i < Node->mNumChildren; ++i)
	{
		_ProcessNode(Node->mChildren[i], Scene);
	}
}

UMesh UModel::_ProcessMesh(aiMesh* Mesh, const aiScene* Scene)
{
	std::vector<Vertex> TempVertices;
	std::vector<GLuint> TempIndices;
	std::vector<Texture> TempTextures;

	glm::vec3 TempVec;

	for (size_t i = 0; i < Mesh->mNumVertices; ++i)
	{
		Vertex TempVertex;

		TempVertex.Position.x = Mesh->mVertices[i].x;
		TempVertex.Position.y = Mesh->mVertices[i].y;
		TempVertex.Position.z = Mesh->mVertices[i].z;

		TempVertex.Normal.x = Mesh->mNormals[i].x;
		TempVertex.Normal.y = Mesh->mNormals[i].y;
		TempVertex.Normal.z = Mesh->mNormals[i].z;

		if (Mesh->mTextureCoords[0])
		{
			TempVertex.TextureCoordinate.x = Mesh->mTextureCoords[0][i].x;
			TempVertex.TextureCoordinate.y = Mesh->mTextureCoords[0][i].y;
		}
		else
		{
			TempVertex.TextureCoordinate = glm::vec2(0.0f, 0.0f);
		}

		TempVertices.push_back(TempVertex);
	}

	for (size_t i = 0; i < Mesh->mNumFaces; ++i)
	{
		for (size_t j = 0; j < Mesh->mFaces[i].mNumIndices; ++j)
		{
			TempIndices.push_back(Mesh->mFaces[i].mIndices[j]);
		}
		
	}

	return UMesh(TempVertices, TempIndices, {});
}
