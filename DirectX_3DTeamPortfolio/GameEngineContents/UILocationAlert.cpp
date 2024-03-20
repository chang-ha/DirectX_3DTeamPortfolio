#include "PreCompile.h"
#include "UILocationAlert.h"

UILocationAlert::UILocationAlert() 
{
}

UILocationAlert::~UILocationAlert() 
{
}

void UILocationAlert::Start() 
{

	// 언더바 : 알파값

	// Bar State
	//CreateStateParameter AwakeState;
	//AwakeState.Start = std::bind(&MonsterHpBar::Start_Awake, this, std::placeholders::_1);

	//CreateStateParameter IdleState;
	//IdleState.Stay = std::bind(&MonsterHpBar::Update_Idle, this, std::placeholders::_1, std::placeholders::_2);

	//CreateStateParameter OffState;
	//OffState.Start = std::bind(&MonsterHpBar::Start_Off, this, std::placeholders::_1);
	//OffState.Stay = std::bind(&MonsterHpBar::Update_Off, this, std::placeholders::_1, std::placeholders::_2);

	//MainState.CreateState(eState::Awake, AwakeState);
	//MainState.CreateState(eState::Idle, IdleState);
	//MainState.CreateState(eState::Off, OffState);
}

void UILocationAlert::Update(float _Delta) 
{

}

void UILocationAlert::Release() 
{
	FontTexture = nullptr;
	UnderBar = nullptr;
	Collision = nullptr;
}

void UILocationAlert::Reset() 
{
	MainState.ChangeState(eState::Idle);
}

void UILocationAlert::SetCollision(const float4& _Scale, float _Rot)
{
	Collision->Transform.SetLocalScale(_Scale);
	Collision->Transform.SetLocalRotation(float4(0.0f, _Rot));
}

//State
static constexpr float FadeTime = 2.0f;
static constexpr float AppearStateTime = 4.0f;

// State_Idle
void UILocationAlert::Start_Idle(GameEngineState* _Parent)
{
	On();
}

void UILocationAlert::Update_Idle(float _Delta, GameEngineState* _Parent)
{

}


void UILocationAlert::Start_Appear(GameEngineState* _Parent)
{

}

void UILocationAlert::Update_Appear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	if (StateTime > FadeTime)
	{
		const float Ratio = (FadeTime - StateTime) / FadeTime;
	}

	if (StateTime >= AppearStateTime)
	{
		_Parent->ChangeState(eState::DisAppear);
		return;
	}
}


void UILocationAlert::Update_DisAppear(float _Delta, GameEngineState* _Parent)
{

}

void UILocationAlert::End_DisAppear(GameEngineState* _Parent)
{
	Off();
}

void UILocationAlert::SetGamma(float _Ratio)
{
	const float Ratio = std::clamp(_Ratio, 0.0f, 1.0f);
	FontTexture->GetColorData().MulColor.A = Ratio;
	UnderBar->GetColorData().MulColor.A = Ratio;
}