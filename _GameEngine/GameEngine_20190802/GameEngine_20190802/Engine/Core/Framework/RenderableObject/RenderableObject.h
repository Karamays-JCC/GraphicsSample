#pragma once
#include <Global/Global.h>
#include <Framework/Object/UObject.h>
#include <Framework/Program/Program.h>

class RenderableObject : public UObject
{
public:
	RenderableObject();
	virtual ~RenderableObject();

	RenderableObject(glm::vec3 _WorldPosition, std::shared_ptr<class ULevel> _Level);

public:
	void Draw(float DeltaTime, const glm::mat4& ProjectionMatrix, const glm::mat4& ViewMatrix, glm::vec3 CameraPosition);

	void Jump();

	void StopJumping();

public:
	virtual std::string Serialize() override;

	virtual void Deserialize(const std::string& Content) override;

	glm::vec3& GetPosition() { return WorldPosition; };

private:

	std::shared_ptr<class ULevel> Level;

	std::vector<std::shared_ptr<class UMaterial>> Materials;

	class Program _Program;

	glm::vec3 WorldPosition;

	glm::mat4 ModelMatrix;

	void _RecomputeMatrix();
};

