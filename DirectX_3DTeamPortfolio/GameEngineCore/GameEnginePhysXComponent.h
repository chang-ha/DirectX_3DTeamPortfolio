#pragma once
#include "GameEngineComponent.h"

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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	physx::PxScene* Scene = nullptr;
	class GameEnginePhysXLevel* CurPhysXLevel = nullptr;
private:

};

