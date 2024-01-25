#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleLogo.h"

TitleLevel::TitleLevel()
{

}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
}

void TitleLevel::Update(float _Delta)
{

}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == GameEngineSprite::Find("Dark.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFile& File = Files[i];
			GameEngineTexture::Load(File.GetStringPath());
		}
		GameEngineSprite::CreateSingle("Dark.png");
		GameEngineSprite::CreateSingle("Textures.png");

		GameEngineSprite::CreateSingle("BanDaiNaco_Logo.png");
		GameEngineSprite::CreateSingle("FromSoftLogo.png");
		GameEngineSprite::CreateSingle("DarkSoulsLogo.png");
		GameEngineSprite::CreateSingle("Title_IncLogo.png");
		GameEngineSprite::CreateSingle("AnyButtonBack.png");
	}

	Title_Logo = CreateActor<TitleLogo>();
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevle)
{
	if (nullptr != GameEngineSprite::Find("Dark.Png"))
	{
		GameEngineSprite::Release("Dark.Png");
		GameEngineSprite::Release("Textures.Png");

		GameEngineSprite::Release("BanDaiNaco_Logo.png");
		GameEngineSprite::Release("FromSoftLogo.png");
		GameEngineSprite::Release("DarkSoulsLogo.png");
		GameEngineSprite::Release("Title_IncLogo.png");
		GameEngineSprite::Release("AnyButtonBack.png");
	}

	if (nullptr != Title_Logo)
	{
		Title_Logo->Death();
		Title_Logo = nullptr;
	}
}