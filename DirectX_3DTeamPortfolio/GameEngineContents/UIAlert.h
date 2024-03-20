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
	void Update(float _Delta) override;
	void Release() override;

	// State Func
	void SetBackScale(const float4& _Scale);
	void SetGamma(GameEngineUIRenderer* _Renderer, float _Ratio);

	enum class eState
	{
		Appear, // Start Update
		Disappear, // Update End 
	};

	//virtual void Start_Appear(GameEngineState* _Parent) {};
	//virtual void Update_Appear(float _Delta, GameEngineState* _Parent) {};

	//virtual void Update_DisAppear(float _Delta, GameEngineState* _Parent) {};
	//virtual void End_DisAppear(GameEngineState* _Parent) {};

protected:
	std::shared_ptr<GameEngineUIRenderer> BackTexture;
	std::shared_ptr<GameEngineUIRenderer> FontTexture;

	float FullRatio = 0.0f;

	GameEngineState MainState;


};