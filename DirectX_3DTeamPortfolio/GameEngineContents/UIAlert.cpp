#include "PreCompile.h"
#include "UIAlert.h"
#include "UIAlert_BoneLit.h"

UIAlert::UIAlert() 
{
}

UIAlert::~UIAlert() 
{
}


void UIAlert::Start()
{
	// Renderer Create
	BackTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackTexture);
	FontTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_FontTexture);
	BackTexture->AutoSpriteSizeOn();
	FontTexture->AutoSpriteSizeOn();

	BackTexture->Off();
	FontTexture->Off();

	GameEngineInput::AddInputObject(this);
}

void UIAlert::Update(float _Delta)
{
	MainState.Update(_Delta);
	if (GameEngineInput::IsDown('I', this))
	{
		MainState.ChangeState(eState::Appear);
	}
}

void UIAlert::Release()
{
	// Renderer Release
}

void UIAlert::SetBackScale(const float4& _Scale)
{
	BackTexture->SetAutoScaleRatio(_Scale);
}

void UIAlert::SetGamma(GameEngineUIRenderer* _Renderer, float _Ratio)
{
	const float Ratio = std::clamp(_Ratio, 0.0f, 1.0f);
	_Renderer->GetColorData().MulColor.A = Ratio;
}