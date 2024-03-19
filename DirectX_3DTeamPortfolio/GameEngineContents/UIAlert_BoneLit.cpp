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
	const float4 TexScale = float4::ZERO;
	FullRatio = WinScale.X / TexScale.X;
	const float FrontRatio = FullRatio * 0.9f;
	BackTexture->GetCurSprite().Texture->GetScale();
	BackTexture->AutoSpriteSizeOn();
	BackTexture->SetAutoScaleRatio(float4(FullRatio, FullRatio));
	FontTexture->SetAutoScaleRatio(float4(FrontRatio, FrontRatio));

	// Create State
}

void UIAlert_BoneLit::Update(float _Delta)
{
	UIAlert::Update(_Delta);
}

void UIAlert_BoneLit::Release()
{
	UIAlert::Release();
}