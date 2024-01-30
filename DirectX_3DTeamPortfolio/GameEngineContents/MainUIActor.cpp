#include "PreCompile.h"
#include "MainUIActor.h"

#include "PlayerValue.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

void MainUIActor::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainHpBar->SetImageScale({ (CurHpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxHp())) * 400.0f, 80.0f });
}
void MainUIActor::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void MainUIActor::Start()
{
	if (nullptr == GameEngineSprite::Find("HpBar.png"))
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

	MainHpBar = CreateComponent<GameEngineUIRenderer>();
	MainHpBar->SetSprite("HpBar.png");
	MainHpBar->Transform.SetLocalPosition(0.0f);

	GameEngineInput::AddInputObject(this);
}

void MainUIActor::Update(float _Delta)
{
	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddHp(10);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->SubHp(10);
	}

	HpUpdate(_Delta);
}

void MainUIActor::HpUpdate(float _Delta)
{
	float PlayerHp = static_cast<float>(PlayerValue::GetValue()->GetHp());
	if (PlayerHp == CurHpScale)
	{
		return;
	}

	if(PlayerHp < CurHpScale)
	{
		CurHpScale -= ScaleSpeed * _Delta;
		if (PlayerHp > CurHpScale)
		{
			CurHpScale = PlayerHp;
		}
	}
	else if (PlayerHp > CurHpScale)
	{
		CurHpScale += ScaleSpeed * _Delta;

		if (PlayerHp < CurHpScale)
		{
			CurHpScale = PlayerHp;
		}
	}

	MainHpBar->SetImageScale({ (CurHpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxHp())) * 400.0f, 80.0f });

}