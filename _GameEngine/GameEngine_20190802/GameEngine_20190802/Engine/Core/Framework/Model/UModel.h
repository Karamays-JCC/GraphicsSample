#pragma once
#include <Global/Global.h>

#include <iostream>
#include <string>
#include <vector>

class UModel
{
public:
	UModel(const std::string& FilePath);
	~UModel();

public:
	std::vector<class UMesh> Meshes;

	std::string Directory;

private:
	void _LoadModel(const std::string& FilePath);

	void _ProcessNode(aiNode* Node, const aiScene* Scene);

	class UMesh _ProcessMesh(aiMesh* Mesh, const aiScene* Scene);

};

