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

	void AddForce(const float4 _Force)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		AddForce(Value);
	}

	void AddForce(const physx::PxVec3 _Force);

	void ResetMove(Enum_Axies _Axies)
	{
		ResetMove(static_cast<int>(_Axies));
	}

	void ResetMove(int _Axies);

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
		// F = M * A
		return ComponentActor->setMass(_MassValue);
	}

	void SetMaxSpeed(float _MaxSpeed);

	inline void SetPositioningComponent()
	{
		IsPositioningComponent = true;
	}

	physx::PxVec3 GetWorldPosition()
	{
		return ComponentActor->getGlobalPose().p;
	}

	bool IsGravity()
	{
		physx::PxActorFlags Flags = ComponentActor->getActorFlags();
		bool Result = Flags & physx::PxActorFlag::eDISABLE_GRAVITY;
		return !Result;
	}

	void GravityOn();
	void GravityOff();

	void RayCastTargetOn();
	void RayCastTargetOff();

	void CollisionOn(bool _GravityOn = true);
	void CollisionOff(bool _GravityOff = true);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	bool IsPositioningComponent = false;
	physx::PxShape* CapsuleShape = nullptr;

	void Positioning(float _Delta);
};

