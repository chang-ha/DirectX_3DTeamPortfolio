#include "PreCompile.h"
#include "MainUIActor.h"

#include "PlayerValue.h"
#include "UIPlayerGaugeBar.h"
#include "UIEquipFrame.h"
#include "UIPlayerEquip.h"
#include "BossHpBar.h"

#include "AddSouls.h"
#include "AppearTextures.h"

#include "Boss_Vordt.h"

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

	if (nullptr == GameEngineSprite::Find("Number_0.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("Number");
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
		PlayerIcon->Transform.SetLocalPosition({ -WindowScale.X + 60.0f, 400.0f });
	}


	/*{
		GetLevel()->CreateActor<BossHpBar>();
	}*/

	GameEngineInput::AddInputObject(this);

	GetLevel()->CreateActor<UIPlayerGaugeBar>();
	
	//GetLevel()->CreateActor<UIPlayerEquip>();

	GetLevel()->CreateActor<AddSouls>();

	GetLevel()->CreateActor<AppearTextures>();

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

}

void MainUIActor::CreateBossUI(Boss_Vordt* _pBoss)
{
	BossHpObject = GetLevel()->CreateActor<BossHpBar>(Enum_UpdateOrder::UI);

	BossHpObject->SetParent(_pBoss);
	BossHpObject.get();

}

void MainUIActor::CheckEsteUI(Player* _pPlayer)
{
	EsteUI = GetLevel()->CreateActor<UIPlayerEquip>(Enum_UpdateOrder::UI);

	EsteUI->SetParent(_pPlayer);
}