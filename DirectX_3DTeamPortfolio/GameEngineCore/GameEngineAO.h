#pragma once
#include "GameEngineObject.h"

// Ό³Έν :
class GameEngineAO : public GameEngineObjectBase
{
public:
	// constrcuter destructer
	GameEngineAO();
	~GameEngineAO();

	// delete Function
	GameEngineAO(const GameEngineAO& _Other) = delete;
	GameEngineAO(GameEngineAO&& _Other) noexcept = delete;
	GameEngineAO& operator=(const GameEngineAO& _Other) = delete;
	GameEngineAO& operator=(GameEngineAO&& _Other) noexcept = delete;

protected:
	void Init(class ID3D11Device* pDevice);

private:

};

