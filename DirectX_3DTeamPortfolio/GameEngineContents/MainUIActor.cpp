#include "PreCompile.h"
#include "MainUIActor.h"

#include "PlayerValue.h"
#include "UIPlayerGaugeBar.h"
#include "UIEquipFrame.h"
#include "UIPlayerEquip.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

void MainUIActor::LevelStart(GameEngineLevel* _PrevLevel)
{

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

	
	float4 WindowScale = GameEngineCore::MainWindow.GetScale().Half();
	{

		PlayerIcon = CreateComponent<GameEngineUIRenderer>();
		PlayerIcon->SetSprite("PlayerIcon.Png");
		PlayerIcon->AutoSpriteSizeOn();
		PlayerIcon->Transform.SetLocalPosition({ -WindowScale.X + 60.0f, 300.0f });
	}

	//{
	//	Equip_Frame = CreateComponent<GameEngineUIRenderer>();
	//	Equip_Frame->SetSprite("EquipFrame.Png");
	//	Equip_Frame->AutoSpriteSizeOn();
	//	Equip_Frame->Transform.SetLocalPosition({ -WindowScale.X + 100.0f, -100.0f });

	//	Equip_Shield = CreateComponent<GameEngineUIRenderer>();
	//	Equip_Shield->SetSprite("Sword.Png");
	//	Equip_Shield->AutoSpriteSizeOn();
	//	Equip_Shield->Transform.SetLocalPosition({ -WindowScale.X + 100.0f, -100.0f });

	//	Equip_Bottle = CreateComponent<GameEngineUIRenderer>();
	//	Equip_Bottle->SetSprite("EsteBottl_S.Png");
	//	Equip_Bottle->AutoSpriteSizeOn();
	//	Equip_Bottle->Transform.SetLocalPosition({ -WindowScale.X + 100.0f, -100.0f });
	//}

	//{
	//	Boss_HpBar = CreateComponent<GameEngineUIRenderer>();
	//	Boss_HpBar->SetSprite("BossBar.Png");
	//	Boss_HpBar->AutoSpriteSizeOn();
	//	Boss_HpBar->Transform.SetLocalPosition({ 0.0f, -200.0f });

	//	Boss_Hp = CreateComponent<GameEngineUIRenderer>();
	//	Boss_Hp->SetSprite("BossHp.Png");
	//	Boss_Hp->SetImageScale({ 960.0f, 13.0f });
	//	Boss_Hp->SetPivotType(PivotType::Left);
	//	Boss_Hp->Transform.SetLocalPosition({ -481.5f, -200.0f });

	//	Boss_DamageBar = CreateComponent<GameEngineUIRenderer>();
	//	Boss_DamageBar->SetSprite("DamageBar.Png");
	//	Boss_DamageBar->AutoSpriteSizeOn();
	//	Boss_DamageBar->Transform.SetLocalPosition({ 0.0f, -200.0f });
	//}

	//{
	//	Textures = CreateComponent<GameEngineUIRenderer>();
	//	Textures->SetSprite("Textures.Png");
	//	Textures->AutoSpriteSizeOn();
	//	Textures->Transform.SetLocalPosition({ 0.0f, 0.0f });
	//}


	GameEngineInput::AddInputObject(this);

	GetLevel()->CreateActor<UIPlayerGaugeBar>();
	GetLevel()->CreateActor<UIPlayerEquip>();
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

	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();

	int a = 0;
}

