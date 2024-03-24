#include "PreCompile.h"
#include "UIAlert_YouDie.h"

UIAlert_YouDie::UIAlert_YouDie() 
{
}

UIAlert_YouDie::~UIAlert_YouDie() 
{
}


void UIAlert_YouDie::Start()
{
	UIAlert::Start();

	const float4 WinScale = GlobalValue::GetWinScale();
	float4 TexScale = float4::ZERO;

	BackTexture->SetSprite("YouDied.Png");
	FontTexture->Off();

	TexScale = BackTexture->GetCurSprite().Texture->GetScale();

	FullRatio = WinScale.X / TexScale.X;
	const float FrontRatio = FullRatio * 0.9f;
	BackTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	FontTexture->SetAutoScaleRatio(float4(FullRatio, FrontRatio));


	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&UIAlert_YouDie::Start_Appear, this, std::placeholders::_1);

	CreateStateParameter StayState;
	StayState.Stay = std::bind(&UIAlert_YouDie::Update_Stay, this, std::placeholders::_1, std::placeholders::_2);

	mState.CreateState(eState::Appear, AppearState);
	mState.CreateState(eState::Stay, StayState);

	mState.ChangeState(eState::Appear);
}

void UIAlert_YouDie::Update(float _Delta)
{
	UIAlert::Update(_Delta);

	mState.Update(_Delta);
}

void UIAlert_YouDie::Release()
{
	UIAlert::Release();
}



// State
static constexpr float FadeTime = 1.0f;
static constexpr float StartGamma = 0.3f;
void UIAlert_YouDie::Start_Appear(GameEngineState* _Parent)
{
	SetBackScale({ FullRatio, FullRatio });
	SetGamma(BackTexture.get(), StartGamma);
	ScaleRatio = FullRatio;

	GameEngineSoundPlayer Died = GameEngineSound::SoundPlay("YOU_DIED_Sound_Effect.wav");
	Died.SetVolume(0.7f);

	GameEngineSoundPlayer MDied = GameEngineSound::SoundPlay("Voice_M_Dead.wav");
	MDied.SetVolume(0.7f);

	mState.ChangeState(eState::Stay);
}

void UIAlert_YouDie::Update_Stay(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = _Parent->GetStateTime();
	ScaleRatio += _Delta / FadeTime;
	if (StateTime >= FadeTime)
	{
		return;
	}

	SetBackScale(float4(ScaleRatio, ScaleRatio));
	SetGamma(BackTexture.get(), StartGamma + StateTime);
}