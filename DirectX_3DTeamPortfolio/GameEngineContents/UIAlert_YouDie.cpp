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
}

void UIAlert_YouDie::Update(float _Delta)
{
	// UIAlert::Update(_Delta);
	const float StateTime = 2.0f;
	if (GetLiveTime() > StateTime)
	{
		Off();
	}
}

void UIAlert_YouDie::Release()
{
	UIAlert::Release();
}