#pragma once
#include "GameEngineTexture.h"
#include "GAMEENGINERENDERER.H"

#define MAX_RENDER_TARGET_SETTING_COUNT 8

class Effect : public GameEngineObjectBase
{
	friend class GameEngineRenderTarget;

public:
	RenderBaseInfo RenderBaseInfoValue;

	// 효과를 준것을 받을 타겟이 필요하다.
	GameEngineRenderUnit EffectUnit;

	GameEngineRenderTarget* EffectTarget = nullptr;
	std::shared_ptr<GameEngineRenderTarget> ResultTarget = nullptr;

public:
	virtual void Start() = 0;
	// 효과를 준다는것이 무슨말인지 이해를 해야한다.
	virtual void EffectProcess(float _DeltaTime) = 0;
};


// 설명 : 기본적으로 멀티랜더 타겟
class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
	static void RenderTargetReset();

public:
	friend class GameEngineCoreWindow;
	friend GameEngineDevice;
	static bool IsDepth;

	// constrcuter destructer
	GameEngineRenderTarget();
	~GameEngineRenderTarget();

	// delete Function
	GameEngineRenderTarget(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&& _Other) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget& _Other) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&& _Other) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(std::shared_ptr<GameEngineTexture> _Texture, float4 _Color = float4::BLUE) 
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();

		NewRes->AddNewTexture(_Texture, _Color);
		return NewRes;
	}

	static std::shared_ptr<GameEngineRenderTarget> Create()
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		return NewRes;
	}

	inline std::shared_ptr<GameEngineTexture> GetTexture(int _Index = 0)
	{
		return Textures[_Index];
	}

	void Clear();
	void Setting();

	void CreateDepthTexture(int _Index = 0);

	void AddNewTexture(DXGI_FORMAT _Format, float4 _Scale, float4 _ClearColor);

	void AddNewTexture(std::shared_ptr<GameEngineTexture> _Texture, float4 _ClearColor);

	void Copy(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

	void Merge(unsigned int ThisTarget, std::shared_ptr<GameEngineRenderTarget> _Target, unsigned int _CopyTarget = 0);

	void PostEffect(float _DeltaTime);

	void EffectInit(Effect* _Effect);

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}

	template<typename EffectType>
	std::shared_ptr<EffectType> CreateEffect() 
	{
		std::shared_ptr<EffectType> NewEffect = std::make_shared<EffectType>();
		EffectInit(NewEffect.get());

		Effects.push_back(NewEffect);
		return NewEffect;
	}

	std::shared_ptr<GameEngineRenderTarget> CreateChildRenderTarget(std::vector<int> _Index);

protected:

private:
	static GameEngineRenderUnit MergeUnit;
	static void MergeRenderUnitInit();

	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<ID3D11RenderTargetView*> RTV; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한
	std::vector<ID3D11ShaderResourceView*> SRV; // <= 텍스처를 리소스로 사용할수 있는 권한
	std::vector<float4> ClearColor; // <= 텍스처를 랜더타겟으로 삼을수 있게 만드는 권한
	std::vector<D3D11_VIEWPORT> ViewPorts;

	std::shared_ptr<GameEngineTexture> DepthTexture;

	std::list<std::shared_ptr<Effect>> Effects;
};

