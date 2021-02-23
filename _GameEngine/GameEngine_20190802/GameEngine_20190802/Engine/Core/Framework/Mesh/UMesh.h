#pragma once

#include <Global/Global.h>
#include <string>
#include <vector>
#include <iostream>

struct Vertex 
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TextureCoordinate;
};

struct Texture
{
	GLuint ID;
	std::string Type;
	std::string Path;
};

class UMesh
{
public:
	UMesh();
	UMesh(std::vector<Vertex> Vertices, std::vector<GLuint> Indicates, std::vector<Texture> Textures);
	~UMesh();

	void Draw();

public:
	std::vector<Vertex> Vertices;
	std::vector<GLuint> Indices;
	std::vector<Texture> Textures;
	 
private:
	GLuint VAO, VBO, EBO;

	void SetMesh();

};

