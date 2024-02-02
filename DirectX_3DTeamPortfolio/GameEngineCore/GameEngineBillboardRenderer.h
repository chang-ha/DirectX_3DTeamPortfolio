#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineComputeUnit.h"

// Ό³Έν :
class GameEngineBillboardRenderer : public GameEngineRenderer
{
public:
	// constrcuter destructer
	GameEngineBillboardRenderer();
	~GameEngineBillboardRenderer();

	// delete Function
	GameEngineBillboardRenderer(const GameEngineBillboardRenderer& _Other) = delete;
	GameEngineBillboardRenderer(GameEngineBillboardRenderer&& _Other) noexcept = delete;
	GameEngineBillboardRenderer& operator=(const GameEngineBillboardRenderer& _Other) = delete;
	GameEngineBillboardRenderer& operator=(GameEngineBillboardRenderer&& _Other) noexcept = delete;

protected:

private:

};

