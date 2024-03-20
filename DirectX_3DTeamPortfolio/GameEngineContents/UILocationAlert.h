#pragma once
#include "UIActor.h"

// ���� :
class UILocationAlert : public UIActor
{
	enum class eState
	{
		Idle,
		Appear,
		DisAppear,
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

	void SetCollision(const float4& _Pos, const float4& _Scale, float _Rot);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void Reset() override;

private:
	// State_Idle
	void Start_Idle(GameEngineState* _Parent); // Reset
	void Update_Idle(float _Delta, GameEngineState* _Parent);

	// State_Appear
	void Start_Appear(GameEngineState* _Parent);
	void Update_Appear(float _Delta,GameEngineState* _Parent);

	// State_DisAppear
	void Update_DisAppear(float _Delta,GameEngineState* _Parent);
	void End_DisAppear(GameEngineState* _Parent); // Off

	// Func
	void SetGamma(float _Ratio);

private:
	std::shared_ptr<GameEngineUIRenderer> FontTexture;
	std::shared_ptr<GameEngineUIRenderer> UnderBar;

	std::shared_ptr<GameEngineCollision> AlertLoCollision;

	GameEngineState MainState;

};

