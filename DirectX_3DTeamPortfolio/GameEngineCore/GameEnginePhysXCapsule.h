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
		return CapsuleActor->getLinearVelocity();
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
		return CapsuleActor->getGlobalPose().p;
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	physx::PxRigidDynamic* CapsuleActor = nullptr;
};

