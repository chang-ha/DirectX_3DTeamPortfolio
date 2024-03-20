#include "PreCompile.h"
#include "UIAlert_BoneLit.h"

UIAlert_BoneLit::UIAlert_BoneLit() 
{
}

UIAlert_BoneLit::~UIAlert_BoneLit() 
{
}


void UIAlert_BoneLit::Start()
{
	UIAlert::Start();

	const float4 WinScale = GlobalValue::GetWinScale();
	float4 TexScale = float4::ZERO;

	BackTexture->SetSprite("LitBack.Png");
	FontTexture->SetSprite("Lit.Png");

	TexScale = BackTexture->GetCurSprite().Texture->GetScale();

	FullRatio = WinScale.X / TexScale.X;
	const float FrontRatio = FullRatio * 0.9f;
	BackTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	FontTexture->SetAutoScaleRatio(float4(FullRatio, FrontRatio));

	// Create State
	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&UIAlert_BoneLit::Start_Appear, this, std::placeholders::_1);
	AppearState.Stay = std::bind(&UIAlert_BoneLit::Update_Appear, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter DisAppearState;
	DisAppearState.Stay = std::bind(&UIAlert_BoneLit::Update_DisAppear, this, std::placeholders::_1, std::placeholders::_2);

	MainState.CreateState(eState::Appear, AppearState);
	MainState.CreateState(eState::Disappear, DisAppearState);
}

void UIAlert_BoneLit::Update(float _Delta)
{
	UIAlert::Update(_Delta);
}

void UIAlert_BoneLit::Release()
{
	UIAlert::Release();
}

//State
static constexpr float FadeTime = 2.f;
static constexpr float StartGamma = 0.3f;

void UIAlert_BoneLit::Start_Appear(GameEngineState* _Parent)
{
	SetGamma(BackTexture.get(), StartGamma);
	SetGamma(FontTexture.get(), StartGamma);
	BackTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	BackTexture->On();
	FontTexture->On();

	ScaleRatio = FullRatio;
}
void UIAlert_BoneLit::Update_Appear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	ScaleRatio += _Delta / FadeTime;

	SetBackScale(float4(ScaleRatio, ScaleRatio));
	SetGamma(BackTexture.get(), StartGamma + StateTime);
	SetGamma(FontTexture.get(), StartGamma + StateTime);

	if (StateTime >= FadeTime)
	{
		MainState.ChangeState(eState::Disappear);
		return;
	}
}

void UIAlert_BoneLit::Update_DisAppear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	if (FadeTime < StateTime)
	{
		return;
	}

	ScaleRatio -= _Delta / FadeTime;
	SetBackScale(float4(ScaleRatio, ScaleRatio));

	const float Ratio = (FadeTime - StateTime) / FadeTime;
	SetGamma(BackTexture.get(), Ratio);
	SetGamma(FontTexture.get(), Ratio);
}