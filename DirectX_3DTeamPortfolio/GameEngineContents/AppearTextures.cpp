#include "PreCompile.h"
#include "AppearTextures.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

AppearTextures::AppearTextures()
{

}

AppearTextures::~AppearTextures()
{

}

void AppearTextures::Start()
{
	Lit = CreateComponent<GameEngineUIRenderer>();
	Lit->SetSprite("Lit.Png");
	Lit->AutoSpriteSizeOn();

	LitBack = CreateComponent<GameEngineUIRenderer>();
	LitBack->SetSprite("LitBack.Png");
	ImageScale = LitBack->GetSprite()->GetSpriteData(0).GetScale();
	LitBack->AutoSpriteSizeOff();
	LitBack->SetImageScale(ImageScale);
	LitBack->GetColorData().MulColor.A = 0.7f;

	GameEngineInput::AddInputObject(this);

}

void AppearTextures::Update(float _Delta)
{
	LitBack->AddImageScale(70.0f * _Delta);
	LitBack->GetColorData().MulColor.A += 0.01f * _Delta;
	TextureTime += _Delta;
	
	if (TextureTime >= TextureLimitTime)
	{
		Lit->Off();
		LitBack->Off();
		TextureTime = 0.0f;
	}

	if (GameEngineInput::IsDown('1', this))
	{
		Lit->On();
		LitBack->On();
		LitBack->GetColorData().MulColor.A = 0.7f;
		LitBack->SetImageScale(ImageScale);
	}
}