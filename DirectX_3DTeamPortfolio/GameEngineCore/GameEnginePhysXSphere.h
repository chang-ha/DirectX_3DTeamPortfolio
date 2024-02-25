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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:
};

