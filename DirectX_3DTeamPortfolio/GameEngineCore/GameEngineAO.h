#pragma once
#include "GameEngineObject.h"

// Ό³Έν :
class GameEngineAO : public GameEngineObjectBase
{
private:
	static GameEngineAO MainHBAO;

public:

	// constrcuter destructer
	GameEngineAO();
	~GameEngineAO();

	// delete Function
	GameEngineAO(const GameEngineAO& _Other) = delete;
	GameEngineAO(GameEngineAO&& _Other) noexcept = delete;
	GameEngineAO& operator=(const GameEngineAO& _Other) = delete;
	GameEngineAO& operator=(GameEngineAO&& _Other) noexcept = delete;

	//void DrawHBAO()

protected:
	void Init(ID3D11Device* pDevice);

private:
	class GFSDK_SSAO_Context_D3D11* AOContext = nullptr;

};

