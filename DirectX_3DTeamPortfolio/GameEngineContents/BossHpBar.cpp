#include "PreCompile.h"
#include "BossHpBar.h"
#include <algorithm>

BossHpBar::BossHpBar()
{

}

BossHpBar::~BossHpBar()
{

}

#define BossHpPos {-400.0f, -230.0f}
#define DamagePos {390.0f, -200.0f}

#define ImageXScale 800.0f
#define BackBarYScale 18.0f
#define HpBarYScale 11.0f

#define DamageFontScale 18.0f

void BossHpBar::Start()
{
	Boss_HpBackBar = CreateComponent<GameEngineUIRenderer>();
	Boss_HpBackBar->SetSprite("BossBar.Png");
	Boss_HpBackBar->SetImageScale({ ImageXScale, BackBarYScale });
	Boss_HpBackBar->Transform.SetLocalPosition(BossHpPos);
	Boss_HpBackBar->SetPivotType(PivotType::Left);

	Boss_DamageBar = CreateComponent<GameEngineUIRenderer>();
	Boss_DamageBar->SetSprite("DamageBar.Png");
	Boss_DamageBar->AutoSpriteSizeOff();
	Boss_DamageBar->SetImageScale({ ImageXScale, HpBarYScale });
	Boss_DamageBar->Transform.SetLocalPosition(BossHpPos);
	Boss_DamageBar->SetPivotType(PivotType::Left);

	Boss_HpBar = CreateComponent<GameEngineUIRenderer>();
	Boss_HpBar->SetSprite("BossHp.Png");
	Boss_HpBar->AutoSpriteSizeOff();
	Boss_HpBar->SetImageScale({ (BossCurHp / BossHp) * ImageXScale, HpBarYScale });
	Boss_HpBar->SetPivotType(PivotType::Left);
	Boss_HpBar->Transform.SetLocalPosition(BossHpPos);

	// GetBossName();
	Boss_Name = CreateComponent<GameEngineUIRenderer>();
	Boss_Name->SetText(GlobalValue::OptimusFont, "차가운 골짜기의 볼드", 20.0f, float4{ 1,1,1,1 }, FW1_LEFT);
	//Boss_Name->Off();
	Boss_Name->Transform.SetLocalPosition({ Boss_HpBar->Transform.GetLocalPosition().X + 5.0f,
	Boss_HpBar->Transform.GetLocalPosition().Y + 40.0f });
	
	BossPrevHp = BossCurHp;
	{
		BossDamageFont = CreateComponent<GameEngineUIRenderer>();
		BossDamageFont->SetText(GlobalValue::OptimusFont, "0", DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
		BossDamageFont->Transform.SetLocalPosition(DamagePos);
		BossDamageFont->Off();
	}

	GameEngineInput::AddInputObject(this);
}

void BossHpBar::Update(float _Delta)
{
	if (GameEngineInput::IsDown('5', this))
	{
		DamRan.SetSeed(time(nullptr));
		DamageRandom = (DamRan.RandomInt(50, 100));

		Damage = DamageRandom;

		BossPrevHp = BossCurHp;
		BossCurHp -= Damage;
	}
	if (GameEngineInput::IsDown('6', this))
	{
		ChangeState(BossHpActor::Appear);
	}
	if (GameEngineInput::IsDown('7', this))
	{
		BossCurHp = 1328;
	}
	if (GameEngineInput::IsDown('8', this))
	{
		DamRan.SetSeed(time(nullptr));
		DamageRandom = (DamRan.RandomInt(50, 100));

		Damage = DamageRandom;

		BossPrevHp = BossCurHp;
		BossCurHp -= Damage;

		BossDamageFont->On();
		BossDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(Damage), DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);

		Dam = true;
	}
	BossHpBarUpdate();

	StateUpdate(_Delta);
}

void BossHpBar::BossHpBarUpdate()
{
	if (BossCurHp <= 0.0f)
	{
		Boss_DamageBar->Transform.SetLocalPosition({
		Boss_HpBar->Transform.GetLocalPosition().X, Boss_HpBar->Transform.GetLocalPosition().Y });
		Boss_HpBar->SetImageScale({ (0.0f / BossHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (BossCurHp > 0.0f)
	{
		Boss_DamageBar->Transform.SetLocalPosition({
		Boss_HpBar->Transform.GetLocalPosition().X, Boss_HpBar->Transform.GetLocalPosition().Y });
		Boss_HpBar->SetImageScale({ (BossCurHp / BossHp) * ImageXScale, HpBarYScale });
	}
}

void BossHpBar::DamageCal()
{
	if (BossCurHp <= 0.0f)
	{
		Boss_DamageBar->SetImageScale({ (0.0f / BossHp) * ImageXScale, HpBarYScale });
		return;
	}

	if (BossCurHp > 0.0f)
	{
		Boss_DamageBar->SetImageScale({ (BossCurHp / BossHp) * ImageXScale, HpBarYScale });
	}
}

void BossHpBar::Release()
{
	Death();
}

void BossHpBar::ChangeState(BossHpActor _State)
{
	if (_State != BHpActor)
	{
		switch (_State)
		{
		case BossHpActor::Off:
			OffStart();
			break;
		case BossHpActor::Appear:
			AppearStart();
			break;
		case BossHpActor::Add:
			AddStart();
			break;
		case BossHpActor::None:
		default:
			MsgBoxAssert("없는 상태로 BossHpBar의 상태를 바꾸려 했습니다.");
			break;
		}
	}

	BHpActor = _State;
}

void BossHpBar::StateUpdate(float _Delta)
{
	switch (BHpActor)
	{
	case BossHpActor::Off:
		return OffUpdate(_Delta);
	case BossHpActor::Appear:
		return AppearUpdate(_Delta);
	case BossHpActor::Add:
		return AddUpdate(_Delta);
	case BossHpActor::None:
	default:
		break;
	}
}

void BossHpBar::OffStart()
{
	BossDamageFont->Off();
}

void BossHpBar::OffUpdate(float _Delta)
{
	if (BossCurHp <= 0.0f)
	{
		return;
	}

	if (BossCurHp == BossPrevHp)
	{
		return;
	}

	ChangeState(BossHpActor::Appear);
}

void BossHpBar::AppearStart()
{
	BossDamageFont->On();

	DamRan.SetSeed(time(nullptr));
	DamageRandom = (DamRan.RandomInt(50, 100));
	Damage = DamageRandom;

	BossCurHp -= Damage;
	BossPrevHp = BossCurHp;

	SumDam = Damage;
	Dam = true;
}

void BossHpBar::AppearUpdate(float _Delta)
{
	BossDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(Damage), DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);

	if (Dam == true)
	{
		if (BossCurHp != BossPrevHp)
		{
			ChangeState(BossHpActor::Add);
			return;
		}

		CurTime += _Delta;
		{
			if (CurTime >= Time)
			{
				DamageCal();
				Dam = false;
				CurTime = 0;
				ChangeState(BossHpActor::Off);
				return;
			}
		}
	}
}

void BossHpBar::AddStart()
{
	SumDam += Damage;

	BossCurHp -= Damage;
	BossPrevHp = BossCurHp;
}

void BossHpBar::AddUpdate(float _Delta)
{
	BossDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(SumDam), DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
	CurTime += _Delta;
	{
		if (CurTime >= Time)
		{
			SumDam = 0;
			DamageCal();
			Dam = false;
			CurTime = 0;
			ChangeState(BossHpActor::Off);
			return;
		}
	}
}