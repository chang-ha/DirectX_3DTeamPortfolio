#include "PreCompile.h"
#include "UIAlert_Destroy.h"

#include "UI_Utils.h"

UIAlert_Destroy::UIAlert_Destroy() 
{
	GameEngineInput::AddInputObject(this);
}

UIAlert_Destroy::~UIAlert_Destroy() 
{
}


void UIAlert_Destroy::Start()
{
	UIAlert::Start();

	const float4 WinScale = GlobalValue::GetWinScale();
	float4 TexScale = float4::ZERO;

	BossSoulImg = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI);
	BossSoulImg->SetSprite("BoldSoul.png");
	BossSoulImg->Transform.SetLocalPosition(float4(0.0f, -235.0f));

	DarkRenderer->SetSprite("Dark.Png");

	BackTexture->SetSprite("TargetDestroyedBack.Png");
	FontTexture->SetSprite("TargetDestroyed.Png");

	TexScale = BackTexture->GetCurSprite().Texture->GetScale();

	FullRatio = WinScale.X / TexScale.X;
	const float FrontRatio = FullRatio * 0.9f;
	BackTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	FontTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	DarkRenderer->SetAutoScaleRatio(float4(FullRatio, FullRatio));

	DarkRenderer->SetImageScale(TexScale * FullRatio);

	CreateStateParameter AppearState;
	AppearState.Start = std::bind(&UIAlert_Destroy::Start_Appear, this, std::placeholders::_1);
	AppearState.Stay = std::bind(&UIAlert_Destroy::Update_Appear, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter StayState;
	StayState.Start = std::bind(&UIAlert_Destroy::Start_Stay, this, std::placeholders::_1);
	StayState.Stay = std::bind(&UIAlert_Destroy::Update_Stay, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter DisAppearState;
	DisAppearState.Start = std::bind(&UIAlert_Destroy::Start_Disappear, this, std::placeholders::_1);
	DisAppearState.Stay = std::bind(&UIAlert_Destroy::Update_Disappear, this, std::placeholders::_1, std::placeholders::_2);

	mState.CreateState(eState::Appear, AppearState);
	mState.CreateState(eState::Stay, StayState);
	mState.CreateState(eState::Disappear, DisAppearState);

	mState.ChangeState(eState::Appear);
}

void UIAlert_Destroy::Update(float _Delta)
{
	UIAlert::Update(_Delta);

	mState.Update(_Delta);

	if (GameEngineInput::IsDown('E', this))
	{
		BossSoulImg->Off();
	}
}

void UIAlert_Destroy::Release()
{
	UIAlert::Release();
}

//Tex Scale : X: 2.110750 Y : 1.875000 Z : 0.000000
//Tex Scale : X: 1.916263 Y : 1.875000 Z : 0.000000
//Tex Scale : X: 2.248928 Y : 1.055634 Z : 0.000000

void UIAlert_Destroy::Start_Appear(GameEngineState* _Parent)
{
	SetBackScale({ FullRatio ,FullRatio });
	ChangeScale = float4(2.11f, FullRatio) - BackTexture->GetAutoScaleRatio();
}

void UIAlert_Destroy::Start_Stay(GameEngineState* _Parent)
{
	SetBackScale(float4(2.11f, FullRatio));
	ChangeScale = float4(1.91f, FullRatio) - BackTexture->GetAutoScaleRatio();
}

void UIAlert_Destroy::Start_Disappear(GameEngineState* _Parent)
{
	SetBackScale(float4(1.91f, FullRatio));
	ChangeScale = float4(2.54f, 0.6f) - BackTexture->GetAutoScaleRatio();

	DarkRenderer->Off();
}


void UIAlert_Destroy::Update_Appear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = 0.3f;
	if (_Parent->GetStateTime() > StateTime)
	{
		_Parent->ChangeState(eState::Stay);
		return;
	}

	const float GammaValue = _Parent->GetStateTime() / StateTime;
	SetGamma(DarkRenderer.get(), GammaValue);
	SetGamma(BackTexture.get(), GammaValue);
	SetGamma(FontTexture.get(), GammaValue);
	SetGamma(BossSoulImg.get(), GammaValue);

	const float MulDelta = _Delta / StateTime;
	const float4 AddScale = ChangeScale * MulDelta;
	AddBackScale(AddScale);
}

void UIAlert_Destroy::Update_Stay(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = 2.0f;
	if (_Parent->GetStateTime() > StateTime)
	{
		_Parent->ChangeState(eState::Disappear);
		return;
	}

	const float MulDelta = _Delta / StateTime;
	const float4 AddScale = ChangeScale * MulDelta;
	AddBackScale(AddScale);
}

void UIAlert_Destroy::Update_Disappear(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = 0.6f;
	if (_Parent->GetStateTime() > StateTime)
	{
		Done();
		return;
	}

	const float GammaValue = (1.0f - _Parent->GetStateTime() / StateTime);
	SetGamma(BackTexture.get(), GammaValue);
	SetGamma(FontTexture.get(), GammaValue);
	SetGamma(BossSoulImg.get(), GammaValue);

	const float MulDelta = _Delta / StateTime;
	const float4 AddScale = ChangeScale * MulDelta;
	AddBackScale(AddScale);
}