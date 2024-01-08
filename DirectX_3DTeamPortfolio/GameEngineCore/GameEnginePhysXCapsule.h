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

	inline float GetMass()
	{
		return ComponentActor->getMass();
	}

	void SetMass(float _MassValue)
	{
		return ComponentActor->setMass(_MassValue);
	}

	void SetMaxSpeed(float _MaxSpeed);

	inline void SetPositioningComponent()
	{
		IsPositioningComponent = true;
	}

	void SetWorldPosition();

	bool RayCastUpdate(const float4& _DirVector, float _MaxDisTance);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	bool IsPositioningComponent = false;
	GameEngineActor* ParentActor = nullptr;
	physx::PxRigidDynamic* ComponentActor = nullptr;

	void Positioning(float _Delta);
};

