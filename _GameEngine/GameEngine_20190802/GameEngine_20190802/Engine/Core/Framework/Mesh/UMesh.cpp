#include "UMesh.h"

UMesh::UMesh()
{
}

UMesh::UMesh(std::vector<Vertex> Vertices, std::vector<GLuint> Indicates, std::vector<Texture> Textures)
{
}

UMesh::~UMesh()
{
}

void UMesh::Draw()
{
	for (size_t i = 0; i < Textures.size(); ++i)
	{
		if (Textures[0].Type == "texture_diffuse")
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
		}
		else if (Textures[i].Type == "texture_specular")
		{
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
		}
	}

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void UMesh::SetMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof Vertex * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof GLuint * Indices.size(), &Indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof Vertex, (const GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof Vertex, (const GLvoid*)(3 * sizeof GLfloat));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof Vertex, (const GLvoid*)(6 * sizeof GLfloat));

}
