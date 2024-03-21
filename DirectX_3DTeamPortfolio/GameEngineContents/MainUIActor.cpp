#include "PreCompile.h"
#include "MainUIActor.h"

#include "UIPlayerGaugeBar.h"
#include "UIEquipFrame.h"
#include "UIPlayerEquip.h"
#include "BossHpUI.h"
#include "UILoading.h"
#include "UIAlert.h"

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

	GetLevel()->CreateActor<AddSouls>();
}

void MainUIActor::Update(float _Delta)
{

}

void MainUIActor::LevelEnd(GameEngineLevel* _NextLevel)
{
	std::vector<std::shared_ptr<UIAlert>> Alerts = GetLevel()->GetObjectGroupConvert<UIAlert>(Enum_UpdateOrder::UI);
	for (std::shared_ptr<UIAlert>& AlertUnit : Alerts)
	{
		AlertUnit->Death();
	}
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

void MainUIActor::CallAlert(Enum_AlertType _Type)
{
	switch (_Type)
	{
	case Enum_AlertType::BoneLit:
		GetLevel()->CreateActor<UIAlert>(Enum_UpdateOrder::UI);
		break;
	case Enum_AlertType::TargetDistory:
		GetLevel()->CreateActor<UIAlert>(Enum_UpdateOrder::UI);
		break;
	case Enum_AlertType::YouDie:
		GetLevel()->CreateActor<UIAlert>(Enum_UpdateOrder::UI);
		break;
	default:
		break;
	}
}