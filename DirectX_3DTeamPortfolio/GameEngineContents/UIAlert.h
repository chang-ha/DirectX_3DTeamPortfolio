#pragma once
#include "UIActor.h"


// Ό³Έν :
class UIAlert : public UIActor
{
public:
	// constrcuter destructer
	UIAlert();
	~UIAlert();

	// delete Function
	UIAlert(const UIAlert& _Other) = delete;
	UIAlert(UIAlert&& _Other) noexcept = delete;
	UIAlert& operator=(const UIAlert& _Other) = delete;
	UIAlert& operator=(UIAlert&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;

	void Done() { Off(); }

	// State Func
	void SetBackScale(const float4& _Scale);
	void AddBackScale(const float4& _AddScale);
	void SetGamma(GameEngineUIRenderer* _Renderer, float _Ratio);

protected:
	std::shared_ptr<GameEngineUIRenderer> DarkRenderer;
	std::shared_ptr<GameEngineUIRenderer> BackTexture;
	std::shared_ptr<GameEngineUIRenderer> FontTexture;

	float FullRatio = 0.0f;

};