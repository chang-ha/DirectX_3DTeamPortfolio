#include "PreCompile.h"
#include "AppearTextures.h"
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "Player.h"
#include "Boss_Vordt.h"

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
	Lit->SetAutoScaleRatio(2.0f);
	Lit->Off();

	LitBack = CreateComponent<GameEngineUIRenderer>();
	LitBack->SetSprite("LitBack.Png");
	ImageScale = LitBack->GetSprite()->GetSpriteData(0).GetScale();
	LitBack->AutoSpriteSizeOff();
	LitBack->SetImageScale(ImageScale * 2.1f);
	LitBack->GetColorData().MulColor.A = 0.8f;
	LitBack->Off();

	SoulImage = CreateComponent<GameEngineUIRenderer>();
	SoulImage->SetSprite("BoldSoul.Png");
	SoulImage->Transform.SetLocalPosition({ 0.0f, -250.0f });
	SoulImage->AutoSpriteSizeOn();
	SoulImage->Off();

	GameEngineInput::AddInputObject(this);
}

void AppearTextures::ReceivePointer(Player* _pPlayer, Boss_Vordt* _pBoss)
{
	// 플레이어
	PlayerObject = _pPlayer;

	// 보스
	BossObject = _pBoss;
}

void AppearTextures::Update(float _Delta)
{
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

	SoulImage->Off();
}

void AppearTextures::OffUpdate(float _Delta)
{
	if (BossObject->IsFlag(Enum_ActorFlag::Death))
	{
		Lit->SetSprite("Lit.Png");
		LitBack->SetSprite("LitBack.Png");

		GameEngineSound::SoundPlay("Bonfire_Sound_Effect_.wav");
		ChangeState(TextureActor::Appear);
	}

	if (GameEngineInput::IsDown('2', this))
	{
		Lit->SetSprite("Lit.Png");
		LitBack->SetSprite("LitBack.Png");
		
		GameEngineSound::SoundPlay("Bonfire_Sound_Effect_.wav");
		ChangeState(TextureActor::Appear);
		return;
	}
	if (GameEngineInput::IsDown('3', this))
	{
		Lit->SetSprite("TargetDestroyed.Png");
		LitBack->SetSprite("TargetDestroyedBack.Png");
		GameEngineSound::SoundPlay("Destroyed_Sound_Effect.wav");
		ChangeState(TextureActor::Appear);
		return;
	}

	if (GameEngineInput::IsDown('4', this))
	{
		Lit->SetSprite("YouDied.Png");
		LitBack->SetSprite("YouDied.Png");
		ChangeState(TextureActor::Appear);
		return;
	}
}

void AppearTextures::AppearStart()
{
	//if () 이미지 정하기?
	Lit->SetAutoScaleRatio(2.0f);

	LitBack->SetImageScale(ImageScale * 2.1f);
	LitBack->GetColorData().MulColor.A = 0.8f;

	Lit->On();
	LitBack->On();

	SoulImage->On();
	GameEngineSound::SoundPlay("Getting_an_Item_Sound_Effect.wav");
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