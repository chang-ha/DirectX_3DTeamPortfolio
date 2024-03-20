#include "PreCompile.h"
#include "UIAlert.h"

UIAlert::UIAlert() 
{
}

UIAlert::~UIAlert() 
{
}


void UIAlert::Start()
{
	// Renderer Create

	// 
	Off();
}

void UIAlert::Update(float _Delta)
{
	MainState.Update(_Delta);
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
	_Renderer->GetColorData().MulColor.A = _Ratio;
}