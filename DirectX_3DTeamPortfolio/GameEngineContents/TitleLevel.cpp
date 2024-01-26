#include "PreCompile.h"
#include "TitleLevel.h"

#include "TitleLogo.h"

TitleLevel::TitleLevel()
{
	GameEngineInput::AddInputObject(this);
}

TitleLevel::~TitleLevel()
{

}

void TitleLevel::Start()
{
	ContentLevel::Start();
	
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsDown('H', this))
	{
		TestClear();
	}
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
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}

	Title_Logo = CreateActor<TitleLogo>();
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

	if (nullptr != Title_Logo)
	{
		Title_Logo->Death();
		Title_Logo = nullptr;
	}
}
