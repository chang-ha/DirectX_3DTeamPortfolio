#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXSphere : public GameEnginePhysXComponent
{
public:
	// constructer destructer
	GameEnginePhysXSphere();
	~GameEnginePhysXSphere();

	// delete function
	GameEnginePhysXSphere(const GameEnginePhysXSphere& _Ohter) = delete;
	GameEnginePhysXSphere(GameEnginePhysXSphere&& _Ohter) noexcept = delete;
	GameEnginePhysXSphere& operator=(const GameEnginePhysXSphere& _Other) = delete;
	GameEnginePhysXSphere& operator=(GameEnginePhysXSphere&& _Other) noexcept = delete;

	void PhysXComponentInit(float _Radius, const physx::PxMaterial* _Material = GameEnginePhysX::GetDefaultMaterial());

	void MoveForce(const float4 _Force)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		MoveForce(Value);
	}

	void MoveForce(const physx::PxVec3 _Force);

	void AddForce(const float4 _Force)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		AddForce(Value);
	}

	void AddForce(const physx::PxVec3 _Force);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
};

