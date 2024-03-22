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
	DarkRenderer = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BlackTexture);
	BackTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackTexture);
	FontTexture = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_FontTexture);
	BackTexture->AutoSpriteSizeOn();
	FontTexture->AutoSpriteSizeOn();

	DarkRenderer->Off();
}

void UIAlert::Release()
{
	BackTexture = nullptr;
	FontTexture = nullptr;
}

void UIAlert::SetBackScale(const float4& _Scale)
{
	BackTexture->SetAutoScaleRatio(_Scale);
}

void UIAlert::AddBackScale(const float4& _AddScale)
{
	const float4 BackScale = _AddScale + BackTexture->GetAutoScaleRatio();
	BackTexture->SetAutoScaleRatio(BackScale);
}

void UIAlert::SetGamma(GameEngineUIRenderer* _Renderer, float _Ratio)
{
	const float Ratio = std::clamp(_Ratio, 0.0f, 1.0f);
	_Renderer->GetColorData().MulColor.A = Ratio;
}