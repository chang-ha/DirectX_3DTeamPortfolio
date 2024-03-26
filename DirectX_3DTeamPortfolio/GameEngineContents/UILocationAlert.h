#pragma once
#include "UIActor.h"

// ¼³¸í :
class UILocationAlert : public UIActor
{
	enum class eState
	{
		Appear,
		DisAppear,
		Done,
	};

public:
	// constrcuter destructer
	UILocationAlert();
	~UILocationAlert();

	// delete Function
	UILocationAlert(const UILocationAlert& _Other) = delete;
	UILocationAlert(UILocationAlert&& _Other) noexcept = delete;
	UILocationAlert& operator=(const UILocationAlert& _Other) = delete;
	UILocationAlert& operator=(UILocationAlert&& _Other) noexcept = delete;

	void SetCollision(const float4& _Scale, const float4& _Pos);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void Reset() override;

private:
	// State_Appear
	void Start_Appear(GameEngineState* _Parent);
	void Update_Appear(float _Delta,GameEngineState* _Parent);

	// State_DisAppear
	void Update_DisAppear(float _Delta,GameEngineState* _Parent);
	void End_DisAppear(GameEngineState* _Parent); // Off

	// State_End
	void Start_Done(GameEngineState* _Parent); // Reset½Ã Off

	// Func
	void SetGamma(float _Ratio);

private:
	std::shared_ptr<GameEngineUIRenderer> FontTexture;
	std::shared_ptr<GameEngineUIRenderer> UnderBar;

	std::shared_ptr<class TriggerActor> EventTrigger;
	
	GameEngineState MainState;
	
	bool ResetAlert = false;
};

