#include "Sphere.h"
#include "Core/SpicesRendererGlobal.h"

Sphere::Sphere()
{
	Radius = 64;

	Mesh = MeshCreator->Create();

	std::vector<glm::vec3> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	std::vector<float> Positions;
	std::vector<float> Normals;
	std::vector<float> UVs;
	std::vector<unsigned int> Indices;

	// construct positions, normals, uvs
	const float PI = 3.14159265359;
	const unsigned int X_SEGMENTS = Radius;
	const unsigned int Y_SEGMENTS = Radius;
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
			uvs.push_back(glm::vec2(xSegment, ySegment));
		}
	}

	// construct indices
	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				Indices.push_back(y * (X_SEGMENTS + 1) + x);
				Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				Indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				Indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}

	// transform
	for (size_t i = 0; i < positions.size(); ++i)
	{
		Positions.push_back(positions[i].x);
		Positions.push_back(positions[i].y);
		Positions.push_back(positions[i].z);
	}

	for (size_t i = 0; i < normals.size(); ++i)
	{
		Normals.push_back(normals[i].x);
		Normals.push_back(normals[i].y);
		Normals.push_back(normals[i].z);
	}

	for (size_t i = 0; i < uvs.size(); ++i)
	{
		UVs.push_back(uvs[i].x);
		UVs.push_back(uvs[i].y);
	}

	Mesh->SetIndices(Indices);
	Mesh->SetPositions(Positions);
	Mesh->SetUVs(UVs);
	Mesh->SetNormals(Normals);
}

Sphere::~Sphere()
{
}
