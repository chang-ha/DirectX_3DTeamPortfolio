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

	physx::PxVec3 GetLinearVelocity()
	{
		Scene->lockRead();
		physx::PxVec3 Result = CapsuleActor->getLinearVelocity();
		Scene->unlockRead();
		return Result;
	}

	float4 GetLinearVelocity_f();

	inline float GetMass()
	{
		return CapsuleActor->getMass();
	}

	void SetMass(float _MassValue)
	{
		// F = M * A
		return CapsuleActor->setMass(_MassValue);
	}

	physx::PxVec3 GetWorldPosition()
	{
		Scene->lockRead();
		physx::PxVec3 Result = CapsuleActor->getGlobalPose().p;
		Scene->unlockRead();
		return Result;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	physx::PxRigidDynamic* CapsuleActor = nullptr;
};

