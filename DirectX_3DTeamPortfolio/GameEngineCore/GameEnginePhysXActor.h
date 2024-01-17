#pragma once
#include "GameEnginePhysXComponent.h"

class GameEnginePhysXActor
{
public:
	// constructer destructer
	GameEnginePhysXActor();
	~GameEnginePhysXActor();

	// delete function
	GameEnginePhysXActor(const GameEnginePhysXActor& _Ohter) = delete;
	GameEnginePhysXActor(GameEnginePhysXActor&& _Ohter) noexcept = delete;
	GameEnginePhysXActor& operator=(const GameEnginePhysXActor& _Other) = delete;
	GameEnginePhysXActor& operator=(GameEnginePhysXActor&& _Other) noexcept = delete;

protected:

private:
};

