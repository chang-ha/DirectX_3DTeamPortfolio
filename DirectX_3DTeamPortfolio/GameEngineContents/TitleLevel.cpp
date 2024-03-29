#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleLogo.h"

#include "AllFadeEffect.h"

#include "LoadingLevel.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	ContentLevel::Start();
	
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLACK);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	Title_Logo = CreateActor<TitleLogo>();
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::LevelEnding()
{
	Title_Logo->Ending();
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Effect
	FadeObject->FadeIn();
	FadeObject->On();

	// Sound
	BGMPlayer = GameEngineSound::SoundPlay("DarkSoulsIII_Main_Menu_Theme.wav", 2);
	BGMPlayer.SetVolume(0.7f);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevle)
{
	BGMPlayer.Stop();
}
