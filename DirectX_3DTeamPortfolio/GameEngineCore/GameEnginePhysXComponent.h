#pragma once
#include "GameEngineComponent.h"

enum Enum_Axies
{
	X = 1 << 0,
	Y = 1 << 1,
	Z = 1 << 2,
	All = X | Y | Z
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

	void MoveForce(const float4 _Force, bool _IgnoreGravity = false)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		MoveForce(Value, _IgnoreGravity);
	}

	void MoveForce(const physx::PxVec3 _Force, bool _IgnoreGravity = false);

	void SetWorldPosition(const float4& _Pos);
	void SetWorldRotation(const float4& _Degree);

	void AddWorldRotation(const float4& _Degree);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	physx::PxScene* Scene = nullptr;
	class GameEnginePhysXLevel* CurPhysXLevel = nullptr;
	GameEngineActor* ParentActor = nullptr;
	physx::PxRigidDynamic* ComponentActor = nullptr;
private:

};

