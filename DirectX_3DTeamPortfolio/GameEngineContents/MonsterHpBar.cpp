#include "PreCompile.h"
#include "MonsterHpBar.h"

#include "BaseActor.h"

MonsterHpBar::MonsterHpBar()
{
}

MonsterHpBar::~MonsterHpBar()
{
}

#define ImageXScale 100.0f
#define BackBarYScale 12.0f
#define HpBarYScale 6.0f
#define DamagePos {-100.0f, 190.0f}

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
	Monster_HpBackBar->Transform.SetLocalPosition({ -100.0f, 200.0f });
	Monster_HpBackBar->SetPivotType(PivotType::Left);
	Monster_HpBackBar->SetBillboardOn();
	Monster_HpBackBar->Off();

	Monster_DamageBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_DamageBar->SetSprite("MonsterDamageBar.Png");
	Monster_DamageBar->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	Monster_DamageBar->Transform.SetLocalPosition({ -100.0f, 200.0f });
	Monster_DamageBar->SetPivotType(PivotType::Left);
	Monster_DamageBar->SetBillboardOn();

	Monster_HpBar = CreateComponent<GameEngineSpriteRenderer>();
	Monster_HpBar->SetSprite("MonsterHp.Png");
	//Monster_HpBar->SetImageScale({ (MonsterCurHp / MosnterHp) });
	Monster_HpBar->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	Monster_HpBar->Transform.SetLocalPosition({ -100.0f, 200.0f });
	Monster_HpBar->SetPivotType(PivotType::Left);
	Monster_HpBar->SetBillboardOn();

	MonsterPrevHp = MonsterCurHp;

	{
		MonsterDamageFont = CreateComponent<GameEngineSpriteRenderer>();
		MonsterDamageFont->SetText(GlobalValue::OptimusFont, "0", 15.0f, float4{ 1,0,0,1 }, FW1_LEFT);
		MonsterDamageFont->Transform.SetLocalPosition(DamagePos);
		MonsterDamageFont->SetBillboardOn();
		MonsterDamageFont->Off();
	}

	/*BaseActor* pActor;
	pActor->GetHp();*/

	GameEngineInput::AddInputObject(this);
}

void MonsterHpBar::Update(float _Delta)
{
	if (false)
	{
		float4 RenderLPos = Monster_HpBackBar->Transform.GetLocalPosition();
		float4 RenderWPos = Monster_HpBackBar->Transform.GetWorldPosition();
		float4 LPos = Transform.GetLocalPosition();
		float4 WPos = Transform.GetWorldPosition();
		float4 ActorLPos = Parent->Transform.GetLocalPosition();
		float4 ActorWPos = Parent->Transform.GetWorldPosition();
		int a = 0;
	}

	BarUpdate();
	StateUpdate(_Delta);

	if (GameEngineInput::IsDown('5', this))
	{
		DamRan.SetSeed(time(nullptr));
		DamageRandom = (DamRan.RandomInt(20, 50));

		Damage = DamageRandom;

		MonsterPrevHp = MonsterCurHp;
		MonsterCurHp -= Damage;
	}

	if (GameEngineInput::IsDown('6', this))
	{
		ChangeState(MonsterHpActor::Appear);
	}
}

void MonsterHpBar::BarUpdate()
{
	if (MonsterCurHp <= 0.0f)
	{
		// Monster_DamageBar->Transform.SetLocalPosition({
		// Monster_HpBar->Transform.GetLocalPosition().X, Monster_HpBar->Transform.GetLocalPosition().Y });
		Monster_HpBar->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (MonsterCurHp > 0.0f)
	{
		// Monster_DamageBar->Transform.SetLocalPosition({
		// Monster_HpBar->Transform.GetLocalPosition().X, Monster_HpBar->Transform.GetLocalPosition().Y });
		Monster_HpBar->SetImageScale({ (MonsterCurHp / MonsterHp) * ImageXScale, HpBarYScale });
	}
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

	MHpActor = _State;
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
	MonsterDamageFont->Off();
}
void MonsterHpBar::OffUpdate(float _Delta)
{
	if (MonsterCurHp <= 0.0f)
	{
		return;
	}

	if (MonsterCurHp == MonsterPrevHp)
	{
		return;
	}

	ChangeState(MonsterHpActor::Appear);
}
void MonsterHpBar::AppearStart()
{
	MonsterDamageFont->On();

	DamRan.SetSeed(time(nullptr));
	DamageRandom = (DamRan.RandomInt(20, 50));
	Damage = DamageRandom;

	MonsterCurHp -= Damage;
	MonsterPrevHp = MonsterCurHp;

	SumDam = Damage;
	Dam = true;
}
void MonsterHpBar::AppearUpdate(float _Delta)
{
	MonsterDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(Damage), 15.0f, float4{1,0,0,1}, FW1_LEFT);

	if (Dam == true)
	{
		if (MonsterCurHp != MonsterPrevHp)
		{
			ChangeState(MonsterHpActor::Add);
			return;
		}

		CurTime += _Delta;
		{
			if (CurTime >= LimitTime)
			{
				DamageCal();
				Dam = false;
				CurTime = 0;
				ChangeState(MonsterHpActor::Off);
				return;
			}
		}
	}
}
void MonsterHpBar::AddStart()
{
	SumDam += Damage;

	MonsterCurHp -= Damage;
	MonsterPrevHp = MonsterCurHp;
}
void MonsterHpBar::AddUpdate(float _Delta)
{
	MonsterDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(SumDam), 15.0f, float4{ 1,0,0,1 }, FW1_LEFT);
	CurTime += _Delta;
	{
		if (CurTime >= LimitTime)
		{
			SumDam = 0;
			DamageCal();
			Dam = false;
			CurTime = 0;
			ChangeState(MonsterHpActor::Off);
			return;
		}
	}
}

void MonsterHpBar::DamageCal()
{
	if (MonsterCurHp <= 0.0f)
	{
		Monster_DamageBar->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (MonsterCurHp > 0.0f)
	{
		Monster_DamageBar->SetImageScale({ (0.0f / MonsterHp) * ImageXScale, HpBarYScale });
	}
}

void MonsterHpBar::Release()
{
	
}