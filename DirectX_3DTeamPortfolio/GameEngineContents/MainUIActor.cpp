#include "PreCompile.h"
#include "MainUIActor.h"

#include "PlayerValue.h"
#include "UIPlayerGaugeBar.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

void MainUIActor::LevelStart(GameEngineLevel* _PrevLevel)
{
	//MainHpBar->SetImageScale({ (CurHpScale / static_cast<float>(PlayerValue::GetValue()->GetMaxHp())) * 400.0f, 80.0f });
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

	
	{
		float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();

		PlayerIcon = CreateComponent<GameEngineUIRenderer>();
		PlayerIcon->SetSprite("PlayerIcon.Png");
		PlayerIcon->AutoSpriteSizeOn();
		PlayerIcon->Transform.SetLocalPosition({ -WindowScale.X + 60.0f, 300.0f });
	}

	GameEngineInput::AddInputObject(this);

	GetLevel()->CreateActor<UIPlayerGaugeBar>();
}

void MainUIActor::Update(float _Delta)
{
	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddHp(50);
		PlayerValue::GetValue()->AddMp(10);
		PlayerValue::GetValue()->AddStamina(20);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->SubHp(50);
		PlayerValue::GetValue()->SubMp(30);
		PlayerValue::GetValue()->SubStamina(40);
	}
}

