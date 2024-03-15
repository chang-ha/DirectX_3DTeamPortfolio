#pragma once
#include "GameEngineComponent.h"

enum Enum_Axies
{
	X = 1 << 0,
	Y = 1 << 1,
	Z = 1 << 2,
	All = X | Y | Z
};

struct FilterData
{
	FilterData()
	{

	}

	template <typename Enum_Type>
	FilterData(Enum_Type _Word0, Enum_Type _Word1, Enum_Type _Word2, Enum_Type _Word3)
		: Word0(static_cast<int>(_Word0)), Word1(static_cast<int>(_Word1)), Word2(static_cast<int>(_Word2)), Word3(static_cast<int>(_Word3))
	{

	}

	int Word0 = 0;
	int Word1 = 0;
	int Word2 = 0;
	int Word3 = 0;
};

class GameEnginePhysXComponent : public GameEngineComponent
{
public:
	// constructer destructer
	GameEnginePhysXComponent();
	~GameEnginePhysXComponent();

	// delete function
	GameEnginePhysXComponent(const GameEnginePhysXComponent& _Ohter) = delete;
	GameEnginePhysXComponent(GameEnginePhysXComponent&& _Ohter) noexcept = delete;
	GameEnginePhysXComponent& operator=(const GameEnginePhysXComponent& _Other) = delete;
	GameEnginePhysXComponent& operator=(GameEnginePhysXComponent&& _Other) noexcept = delete;

	void On() override
	{
		GameEngineComponent::On();

		CollisionOn();
		if (true == JudgeDynamic())
		{
			physx::PxRigidDynamic* DynamicActor = ComponentActor->is<physx::PxRigidDynamic>();
			ResetMove(Enum_Axies::All);
			DynamicActor->putToSleep();
		}
	}
	void Off() override
	{
		GameEngineComponent::Off();

		CollisionOff();
		if (true == JudgeDynamic())
		{
			physx::PxRigidDynamic* DynamicActor = ComponentActor->is<physx::PxRigidDynamic>();
			ResetMove(Enum_Axies::All);
			DynamicActor->wakeUp();
		}
	}

	void MoveForce(const float4& _Force, float _Dir, bool _IgnoreGravity = false)
	{
		float4 Force = _Force;
		Force.VectorRotationToDegY(_Dir);
		physx::PxVec3 Value = physx::PxVec3(Force.X, Force.Y, Force.Z);
		MoveForce(Value, _IgnoreGravity);
	}

	void MoveForce(const float4& _Force, bool _IgnoreGravity = false)
	{
		float4 Force = _Force;
		Force.VectorRotationToDegY(Dir);
		physx::PxVec3 Value = physx::PxVec3(Force.X, Force.Y, Force.Z);
		MoveForce(Value, _IgnoreGravity);
	}

	void MoveForce(const physx::PxVec3 _Force, bool _IgnoreGravity = false);

	void AddForce(const float4& _Force)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		AddForce(Value);
	}

	void AddForce(const physx::PxVec3 _Force);

	void SetWorldPosition(const float4& _Pos);
	void SetWorldRotation(const float4& _Degree);

	void AddWorldRotation(const float4& _Degree);

	inline float GetDir()
	{
		return Dir;
	}

	inline float* GetDirPtr()
	{
		return &Dir;
	}

	void ResetMove(Enum_Axies _Axies)
	{
		ResetMove(static_cast<int>(_Axies));
	}

	void ResetMove(int _Axies);

	bool IsInit()
	{
		if (nullptr == ComponentActor)
		{
			return false;
		}

		return true;
	}

	template <typename EnumType>
	void SetFiltering(EnumType _CollisionOrder, EnumType _TargetCollisionOrder)
	{
		SetFiltering(static_cast<int>(_CollisionOrder), static_cast<int>(_TargetCollisionOrder));
	}

	template <typename EnumType>
	void SetFiltering(EnumType _MyCollisionOrder)
	{
		SetFiltering(static_cast<int>(_MyCollisionOrder));
	}

	void SetFiltering(int _MyCollisionOrder)
	{
		SetFiltering(_MyCollisionOrder, 0);
	}

	void SetFiltering(int _MyCollisionOrder, int _TargetCollisionOrder);

	void SetFiltering(FilterData& _FilterData);

	void ChangeMaterial(physx::PxMaterial* const* _Material);

	void GravityOn();
	void GravityOff();

	void RayCastTargetOn();
	void RayCastTargetOff();

	void CollisionOn(bool _GravityOn = true);
	void CollisionOff(bool _GravityOff = true);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override; 
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	physx::PxScene* Scene = nullptr;
	class GameEnginePhysXLevel* CurPhysXLevel = nullptr;

	float Dir = 0.f;
	GameEngineActor* ParentActor = nullptr;
	physx::PxRigidActor* ComponentActor = nullptr;
	physx::PxShape* Shape = nullptr;

private:

	inline void SetDir(float _Dir)
	{
		Dir = _Dir;

		if (360.f <= Dir)
		{
			Dir -= 360.f;
		}

		if (0.f > Dir)
		{
			Dir += 360.f;
		}
	}

	void AddDir(float _Dir)
	{
		Dir += _Dir;

		if (360.f <= Dir)
		{
			Dir -= 360.f;
		}

		if (0.f > Dir)
		{
			Dir += 360.f;
		}
	}

	bool JudgeDynamic();

	void SetFiltering(int _MyCollisionOrder, int _Target1CollisionOrder, int _Target2CollisionOrder, int _Target3CollisionOrder);
};

