#include "PreCompile.h"
#include "MainUIActor.h"

#include "UIActor.h"
#include "UIPlayerGaugeBar.h"
#include "UIEquipFrame.h"
#include "UIPlayerEquip.h"
#include "BossHpUI.h"

#include "PlayerValue.h"
#include "AddSouls.h"
#include "AppearTextures.h"

#include "Boss_Vordt.h"


MainUIActor::MainUIActor()
{
	GameEngineInput::AddInputObject(this);
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

	const float4 HScale = GameEngineCore::MainWindow.GetScale().Half();
	PlayerIcon = CreateComponent<GameEngineUIRenderer>();
	PlayerIcon->SetSprite("PlayerIcon.Png");
	PlayerIcon->AutoSpriteSizeOn();
	PlayerIcon->Transform.SetLocalPosition({ -HScale.X + 60.0f, 400.0f });

	GetLevel()->CreateActor<AddSouls>();
	GetLevel()->CreateActor<AppearTextures>();
}

void MainUIActor::Update(float _Delta)
{

}

void MainUIActor::CreateBossUI(Boss_Vordt* _pBoss)
{
	if (nullptr == _pBoss)
	{
		MsgBoxAssert("플레이어 포인터를 사용하고 있습니다.");
		return;
	}

	BossHpObject = GetLevel()->CreateActor<BossHpUI>(Enum_UpdateOrder::UI);
	BossHpObject->SetParent(_pBoss);
	BossHpObject->Off();
}

void MainUIActor::CreateAndCheckEsteUI(Player* _pPlayer)
{
	if (nullptr == _pPlayer)
	{
		MsgBoxAssert("플레이어 포인터를 사용하고 있습니다.");
		return;
	}

	EsteUI = GetLevel()->CreateActor<UIPlayerEquip>(Enum_UpdateOrder::UI);
	EsteUI->SetParent(_pPlayer);
}

void MainUIActor::CreateAndCheckPlayerGaugeBar(Player* _pPlayer)
{
	if (nullptr == _pPlayer)
	{
		MsgBoxAssert("플레이어 포인터를 사용하고 있습니다.");
		return;
	}

	PlayerGaugeBar = GetLevel()->CreateActor<UIPlayerGaugeBar>(Enum_UpdateOrder::UI);
	PlayerGaugeBar->Init(_pPlayer);
}

void MainUIActor::AllUIActorReset()
{
	std::vector<std::shared_ptr<UIActor>> Actors = GetLevel()->GetObjectGroupConvert<UIActor>(Enum_UpdateOrder::UI);
	for (const std::shared_ptr<UIActor>& UI : Actors)
	{
		UI->Reset();
	}
}

void MainUIActor::BossUIOn()
{
	if (BossHpObject)
	{
		BossHpObject->Awake();
	}
}