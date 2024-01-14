#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXTriMesh : public GameEnginePhysXComponent
{
public:
	// constructer destructer
	GameEnginePhysXTriMesh();
	~GameEnginePhysXTriMesh();

	// delete function
	GameEnginePhysXTriMesh(const GameEnginePhysXTriMesh& _Ohter) = delete;
	GameEnginePhysXTriMesh(GameEnginePhysXTriMesh&& _Ohter) noexcept = delete;
	GameEnginePhysXTriMesh& operator=(const GameEnginePhysXTriMesh& _Other) = delete;
	GameEnginePhysXTriMesh& operator=(GameEnginePhysXTriMesh&& _Other) noexcept = delete;

	void PhysXComponentInit(std::string_view _MeshName, const physx::PxMaterial* _Material = GameEnginePhysX::GetDefaultMaterial());

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
	void PhysXSerialization();
	void PhysXDeserialization();

	GameEnginePath MeshPath = {};
	physx::PxRigidStatic* StaticActor = nullptr;
};

