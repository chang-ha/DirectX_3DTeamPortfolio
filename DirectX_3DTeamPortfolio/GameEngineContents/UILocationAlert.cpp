#include "PreCompile.h"
#include "UILocationAlert.h"

#include "TriggerActor.h"

UILocationAlert::UILocationAlert() 
{
}

UILocationAlert::~UILocationAlert() 
{
}

void UILocationAlert::Start() 
{
	// 언더바 : 알파값
	UnderBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	UnderBar->GetColorData().PlusColor = float4(0.9f, 0.9f, 0.9f, 0.9f);
	UnderBar->GetImageTransform().SetLocalScale(float4(800.0f, 10.0f));

	// 폰트 텍스처
	FontTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	FontTexture->SetSprite("Lothric_Wall.png");
	FontTexture->Transform.SetLocalPosition(float4(0, 50.0f));
	FontTexture->AutoSpriteSizeOn();
	FontTexture->SetAutoScaleRatio(2.0f);

	EventTrigger = GetLevel()->CreateActor<TriggerActor>(Enum_UpdateOrder::Component);
	EventTrigger->On();
	EventTrigger->SetFunction([=]() { MainState.ChangeState(eState::Appear); });

	// Bar State
	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&::UILocationAlert::Start_Appear, this, std::placeholders::_1);
	AppearState.Stay = std::bind(&::UILocationAlert::Update_Appear, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter DisAppearState;
	DisAppearState.Stay = std::bind(&UILocationAlert::Update_DisAppear, this, std::placeholders::_1, std::placeholders::_2);
	DisAppearState.End = std::bind(&UILocationAlert::End_DisAppear, this, std::placeholders::_1);

	MainState.CreateState(eState::Appear, AppearState);
	MainState.CreateState(eState::DisAppear, DisAppearState);
	MainState.CreateState(eState::Done, {});

	Off();
}

void UILocationAlert::Update(float _Delta) 
{
	MainState.Update(_Delta);
}

void UILocationAlert::Release() 
{
	FontTexture = nullptr;
	UnderBar = nullptr;
}

void UILocationAlert::Reset() 
{
	if (EventTrigger)
	{
		EventTrigger->On();
	}
}

void UILocationAlert::SetCollision(const float4& _Scale, const float4& _Pos)
{
	if (EventTrigger)
	{
		EventTrigger->SetWorldScale(_Scale);
		EventTrigger->Transform.SetWorldPosition(_Pos);
	}
}

//State
static constexpr float FadeTime = 2.0f;
static constexpr float AppearTime = 4.0f;


void UILocationAlert::Start_Appear(GameEngineState* _Parent)
{
	On();
	SetGamma(0.0f);
	GameEngineSound::SoundPlay("New_Location_Sound_Effect.wav");
}

void UILocationAlert::Update_Appear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();

	if (StateTime >= AppearTime)
	{
		_Parent->ChangeState(eState::DisAppear);
		return;
	}

	const float Ratio = StateTime / FadeTime;
	SetGamma(Ratio);
}


void UILocationAlert::Update_DisAppear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	if (StateTime > FadeTime)
	{
		_Parent->ChangeState(eState::Done);
		return;
	}

	const float Ratio = (FadeTime - StateTime) / FadeTime;
	SetGamma(Ratio);
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