#include "PreCompile.h"
#include "MonsterHpBar.h"

#include "BaseActor.h"

MonsterHpBar::MonsterHpBar()
{
}

MonsterHpBar::~MonsterHpBar()
{
}

#define ImageXScale 300.0f
#define BackBarYScale 11.0f
#define DamagePos {-200.0f, 290.0f}

void MonsterHpBar::Start()
{
	if (nullptr == GameEngineSprite::Find("MonsterBar.png"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("UITexture");
		Dir.MoveChild("Monster");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();
		for (GameEngineFile& pFiles : Files)
		{
			GameEngineTexture::Load(pFiles.GetStringPath());
			GameEngineSprite::CreateSingle(pFiles.GetFileName());
		}
	}

	Monster_HpBackBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_HpBackBar->SetSprite("MonsterBar.Png");
	Monster_HpBackBar->SetImageScale({ ImageXScale, BackBarYScale });
	Monster_HpBackBar->Transform.SetLocalPosition({ 0.0f, 300.0f });
	Monster_HpBackBar->SetBillboardOn();

	Monster_DamageBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_DamageBar->SetSprite("MonsterDamageBar.Png");
	Monster_DamageBar->SetImageScale({ (MonsterCurHp / MosnterHp) * ImageXScale, BackBarYScale });
	Monster_DamageBar->Transform.SetLocalPosition({ 0.0f, 300.0f });
	Monster_DamageBar->SetPivotType(PivotType::Left);
	Monster_DamageBar->SetBillboardOn();

	Monster_HpBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_HpBar->SetSprite("MonsterHp.Png");
	//Monster_HpBar->SetImageScale({ (MonsterCurHp / MosnterHp) });
	Monster_HpBar->SetImageScale({ (MonsterCurHp / MosnterHp) * ImageXScale, BackBarYScale });
	Monster_HpBar->Transform.SetLocalPosition({ 0.0f, 300.0f });
	Monster_HpBar->SetBillboardOn();


	{
		MonsterDamageFont = CreateComponent<GameEngineSpriteRenderer>();
		MonsterDamageFont->SetText(GlobalValue::OptimusFont, "50", 13.0f, float4{ 1,0,0,1 }, FW1_LEFT);
		MonsterDamageFont->Transform.SetLocalPosition(DamagePos);
		MonsterDamageFont->SetBillboardOn();
	}

	/*BaseActor* pActor;
	pActor->GetHp();*/

	GameEngineInput::AddInputObject(this);
}

void MonsterHpBar::Update(float _Delta)
{
	StateUpdate(_Delta);
}

void MonsterHpBar::ChangeState(MonsterHpActor _State)
{
	if (_State != MHpActor)
	{
		switch (_State)
		{
		case MonsterHpActor::Off:
			OffStart();
			break;
		case MonsterHpActor::Appear:
			AppearStart();
			break;
		case MonsterHpActor::Add:
			AddStart();
			break;
		case MonsterHpActor::None:
		default:
			MsgBoxAssert("없는 상태로 MonsterHpBar의 상태를 바꾸려 했습니다.");
			break;
		}
	}
}

void MonsterHpBar::StateUpdate(float _Delta)
{
	switch (MHpActor)
	{
	case MonsterHpActor::Off:
		return OffUpdate(_Delta);
	case MonsterHpActor::Appear:
		return AppearUpdate(_Delta);
	case MonsterHpActor::Add:
		return AddUpdate(_Delta);
	case MonsterHpActor::None:
	default:
		break;
	}
}

void MonsterHpBar::OffStart()
{

}
void MonsterHpBar::OffUpdate(float _Delta)
{

}
void MonsterHpBar::AppearStart()
{

}
void MonsterHpBar::AppearUpdate(float _Delta)
{

}
void MonsterHpBar::AddStart()
{

}
void MonsterHpBar::AddUpdate(float _Delta)
{

}

void MonsterHpBar::Release()
{
	Death();
}