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
	Lit->Off();

	LitBack = CreateComponent<GameEngineUIRenderer>();
	LitBack->SetSprite("LitBack.Png");
	ImageScale = LitBack->GetSprite()->GetSpriteData(0).GetScale();
	LitBack->AutoSpriteSizeOff();
	LitBack->SetImageScale(ImageScale);
	LitBack->GetColorData().MulColor.A = 0.7f;
	LitBack->Off();

	GameEngineInput::AddInputObject(this);
}

void AppearTextures::Update(float _Delta)
{
	//LitBack->AddImageScale(70.0f * _Delta);
	//LitBack->GetColorData().MulColor.A += 0.01f * _Delta;
	//TextureTime += _Delta;
	//
	//if (TextureTime >= TextureLimitTime)
	//{
	//	Lit->Off();
	//	LitBack->Off();
	//	TextureTime = 0.0f;
	//}

	if (GameEngineInput::IsDown('1', this))
	{
		Lit->On();
		LitBack->On();
		LitBack->GetColorData().MulColor.A = 0.7f;
		LitBack->SetImageScale(ImageScale);
	}

	StateUpdate(_Delta);
}

void AppearTextures::ChangeState(TextureActor _State)
{
	if (TextActor != _State)
	{
		switch (_State)
		{
		case TextureActor::Off:
			OffStart();
			break;
		case TextureActor::Appear:
			AppearStart();
			break;
		case TextureActor::Disappear:
			DisappearStart();
			break;
		case TextureActor::None:
		default:
			MsgBoxAssert("존재하지 않는 텍스처 이미지로 시작하려했습니다.");
			break;
		}
	}

	TextActor = _State;
}

void AppearTextures::StateUpdate(float _Delta)
{
	switch (TextActor)
	{
	case TextureActor::Off:
		return OffUpdate(_Delta);
	case TextureActor::Appear:
		return AppearUpdate(_Delta);
	case TextureActor::Disappear:
		return DisappearUpdate(_Delta);
	case TextureActor::None:
	default:
		break;
	}
}

void AppearTextures::OffStart()
{
	Lit->Off();
	LitBack->Off();
}

void AppearTextures::OffUpdate(float _Delta)
{
	if (GameEngineInput::IsDown('2', this))
	{
		ChangeState(TextureActor::Appear);
		return;
	}
}

void AppearTextures::AppearStart()
{
	//if () 이미지 정하기?
	Lit->On();
	LitBack->On();
}

void AppearTextures::AppearUpdate(float _Delta)
{
	LitBack->AddImageScale(70.0f * _Delta);
	LitBack->GetColorData().MulColor.A += 0.01f * _Delta;

	TextureTime += _Delta;
	if (TextureTime >= TextureLimitTime)
	{
		TextureTime = 0.0f;
		ChangeState(TextureActor::Disappear);
		return;
	}
}

void AppearTextures::DisappearStart()
{

}

void AppearTextures::DisappearUpdate(float _Delta)
{
	LitBack->AddImageScale(-70.0f * _Delta);
	LitBack->GetColorData().MulColor.A -= 0.01f * _Delta;

	TextureTime += _Delta;
	if (TextureTime >= TextureLimitTime)
	{
		TextureTime = 0.0f;
		ChangeState(TextureActor::Off);
		return;
	}
}