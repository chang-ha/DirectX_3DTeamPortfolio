#pragma once
#include "GameEngineObject.h"
#include <GFSDK_SSAO.h>

struct HBAOInfos
{
	float AORadius = 2.f;
	float AOBias = 0.2f;
	bool BlurAO = true;
	float BlurSharpness = 32.f;
	float PowerExponent = 2.f;
	float SmallScaleAO = 1.f;
	float LargeScaleAO = 1.f;
};



// 설명 :
class GameEngineAO : public GameEngineObjectBase
{
	friend class GameEngineCamera;
	
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
	void Init(ID3D11Device* pDevice);
	void DrawHBAO( std::shared_ptr<class GameEngineRenderTarget> _RTV, const TransformData& _Transform);

protected:



private:
	class GFSDK_SSAO_Context_D3D11* AOContext = nullptr;

	std::shared_ptr<class GameEngineRenderTarget> HBAOTarget; //앰비언트 그려지는 대상

	HBAOInfos  HBAOInfosValue;

};

