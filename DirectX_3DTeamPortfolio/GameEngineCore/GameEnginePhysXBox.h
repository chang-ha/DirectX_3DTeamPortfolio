#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXBox : public GameEnginePhysXComponent
{
public:
	// constructer destructer
	GameEnginePhysXBox();
	~GameEnginePhysXBox();

	// delete function
	GameEnginePhysXBox(const GameEnginePhysXBox& _Ohter) = delete;
	GameEnginePhysXBox(GameEnginePhysXBox&& _Ohter) noexcept = delete;
	GameEnginePhysXBox& operator=(const GameEnginePhysXBox& _Other) = delete;
	GameEnginePhysXBox& operator=(GameEnginePhysXBox&& _Other) noexcept = delete;

	void PhysXComponentInit(float _hX, float _hY, float _hZ, const physx::PxMaterial* _Material = GameEnginePhysX::GetDefaultMaterial());

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
};

