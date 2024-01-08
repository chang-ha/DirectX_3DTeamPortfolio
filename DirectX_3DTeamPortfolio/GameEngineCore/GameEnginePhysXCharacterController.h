#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXCharacterController : public GameEnginePhysXComponent
{
public:
	// constructer destructer
	GameEnginePhysXCharacterController();
	~GameEnginePhysXCharacterController();

	// delete function
	GameEnginePhysXCharacterController(const GameEnginePhysXCharacterController& _Ohter) = delete;
	GameEnginePhysXCharacterController(GameEnginePhysXCharacterController&& _Ohter) noexcept = delete;
	GameEnginePhysXCharacterController& operator=(const GameEnginePhysXCharacterController& _Other) = delete;
	GameEnginePhysXCharacterController& operator=(GameEnginePhysXCharacterController&& _Other) noexcept = delete;

	void PhysXComponentInit(float _Radius, float _HalfHeight, physx::PxMaterial* _Material = GameEnginePhysX::GetDefaultMaterial());
	void Move(const float4 _Force)
	{
		physx::PxVec3 Value = physx::PxVec3(_Force.X, _Force.Y, _Force.Z);
		Move(Value);
	}

	void Move(const physx::PxVec3 _Force);

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	physx::PxController* Controller = nullptr;
	float MoveCallTime = 0.0f;
};

