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

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
}

void TitleLevel::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("BanDaiNaco_Logo.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}

	if (nullptr == GameEngineSprite::Find("DarkSoulsIII_Main_Menu_Theme.wav"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound\\UI");

		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineSound::SoundLoad(pFiles.GetStringPath());
		}
	}

	Title_Logo = CreateActor<TitleLogo>();

	// Effect
	FadeObject->FadeIn();
	FadeObject->On();

	// Sound
	BGMPlayer = GameEngineSound::SoundPlay("DarkSoulsIII_Main_Menu_Theme.wav", 2);
	BGMPlayer.SetVolume(0.7f);
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevle)
{
	TestClear();
}

void TitleLevel::TestClear()
{
	if (nullptr != GameEngineSprite::Find("Dark.Png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineSprite::Release(pFiles.GetFileName());
			GameEngineTexture::Release(pFiles.GetFileName());
		}
	}
	
	BGMPlayer.Stop();

	if (nullptr != Title_Logo)
	{
		Title_Logo->Death();
		Title_Logo = nullptr;
	}
}
