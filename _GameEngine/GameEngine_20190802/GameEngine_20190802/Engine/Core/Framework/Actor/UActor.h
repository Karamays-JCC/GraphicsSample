#pragma once

#include <Global/Global.h>
#include <Framework/Interface/IRenderable.h>
#include <Framework/Interface/ISerializable.h>

#include <memory>

class UActor : public ISerializable
{
public:
	UActor();

	virtual ~UActor();

public:

	virtual void Init();

	virtual void Tick(float Default);

	//~begin
	virtual void Deserialize(std::string SerializedStream) override;

	virtual std::string Serialize() override;

	virtual std::string GetGUID() override;
	//~end

	void AddNewMesh(const std::shared_ptr<class UMesh>& NewMesh);

	glm::vec3 Position;

private:

	std::string GUIDString;

	std::list<std::string> InfoNeedUpdateNextFrame;

	std::vector<std::shared_ptr<class UMesh>> Meshes;

public:
	inline void SetPosition(const glm::vec3& NewPosition) { Position = NewPosition; };
	inline std::list<std::string>& GetNextUpdateInfo() { return InfoNeedUpdateNextFrame; };
	inline std::vector<std::shared_ptr<class UMesh>>& GetMeshes() { return Meshes; };
};

