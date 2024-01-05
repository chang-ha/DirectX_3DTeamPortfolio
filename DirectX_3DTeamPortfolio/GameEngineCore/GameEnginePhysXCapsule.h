#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXCapsule : public GameEnginePhysXComponent
{
public:
	// constructer destructer
	GameEnginePhysXCapsule();
	~GameEnginePhysXCapsule();

	// delete function
	GameEnginePhysXCapsule(const GameEnginePhysXCapsule& _Ohter) = delete;
	GameEnginePhysXCapsule(GameEnginePhysXCapsule&& _Ohter) noexcept = delete;
	GameEnginePhysXCapsule& operator=(const GameEnginePhysXCapsule& _Other) = delete;
	GameEnginePhysXCapsule& operator=(GameEnginePhysXCapsule&& _Other) noexcept = delete;

	void PhysXComponentInit(float _Radius, float _HalfHeight, const physx::PxMaterial* _Material = GameEnginePhysX::GetDefaultMaterial());

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

	void ResetForce();

	physx::PxVec3 GetLinearVelocity()
	{
		return ComponentActor->getLinearVelocity();
	}

	float GetMass()
	{
		return ComponentActor->getMass();
	}

	void SetMass(float _MassValue)
	{
		return ComponentActor->setMass(_MassValue);
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	GameEngineActor* ParentActor = nullptr;
	physx::PxRigidDynamic* ComponentActor = nullptr;
};

