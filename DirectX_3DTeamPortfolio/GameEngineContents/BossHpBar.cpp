#include "PreCompile.h"
#include "BossHpBar.h"

BossHpBar::BossHpBar()
{

}

BossHpBar::~BossHpBar()
{

}

#define BossHpBarPos {200.0f, -350.0f}
#define BossHpPos {-301.5f, -350.0f}
#define DamagePos {670.0f, -330.0f}

void BossHpBar::Start()
{
	Boss_HpBar = CreateComponent<GameEngineUIRenderer>();
	Boss_HpBar->SetSprite("BossBar.Png");
	Boss_HpBar->SetImageScale({ 1000.0f, 19.0f });
	Boss_HpBar->Transform.SetLocalPosition(BossHpBarPos);

	Boss_DamageBar = CreateComponent<GameEngineUIRenderer>();
	Boss_DamageBar->SetSprite("DamageBar.Png");
	Boss_DamageBar->AutoSpriteSizeOff();
	Boss_DamageBar->SetImageScale({1000.0f, 13.0f});
	Boss_DamageBar->Transform.SetLocalPosition(BossHpPos);
	Boss_DamageBar->SetPivotType(PivotType::Left);

	Boss_Hp = CreateComponent<GameEngineUIRenderer>();
	Boss_Hp->SetSprite("BossHp.Png");
	//Boss_Hp->SetImageScale({ 960.0f, 13.0f });
	//Boss_Hp->SetImageScale({ (BossCurHp / BossHp) * 960.0f, 13.0f});
	Boss_Hp->AutoSpriteSizeOff();
	Boss_Hp->SetImageScale({ (BossCurHp / BossHp) * 1000.0f, 13.0f });
	Boss_Hp->SetPivotType(PivotType::Left);
	Boss_Hp->Transform.SetLocalPosition(BossHpPos);

	// GetBossName();
	Boss_Name = CreateComponent<GameEngineUIRenderer>();
	Boss_Name->SetText("OptimusBold", "차가운 골짜기의 볼드", 14.0f, float4{ 1,1,1,1 }, FW1_LEFT);
	Boss_Name->On();
	Boss_Name->Transform.SetLocalPosition({ Boss_Hp->Transform.GetLocalPosition().X + 5.0f,
	Boss_Hp->Transform.GetLocalPosition().Y + 40.0f });

	{
		BossDamageNumberRender1 = CreateComponent<GameEngineUIRenderer>();
		BossDamageNumberRender1->SetSprite("Number_0.Png");
		BossDamageNumberRender1->AutoSpriteSizeOn();
		BossDamageNumberRender1->Transform.SetLocalPosition(DamagePos);

		BossDamageNumberRender2 = CreateComponent<GameEngineUIRenderer>();
		BossDamageNumberRender2->SetSprite("Number_0.Png");
		BossDamageNumberRender2->AutoSpriteSizeOn();
		BossDamageNumberRender2->Transform.SetLocalPosition({ 670.0f - 20.0f, -330.0f });

		BossDamageNumberRender3 = CreateComponent<GameEngineUIRenderer>();
		BossDamageNumberRender3->SetSprite("Number_0.Png");
		BossDamageNumberRender3->AutoSpriteSizeOn();
		BossDamageNumberRender3->Transform.SetLocalPosition({ 670.0f - 40.0f, -330.0f });
	}

	GameEngineInput::AddInputObject(this);
}

void BossHpBar::Update(float _Delta)
{
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
		//Boss_DamageBar->SetImageScale({ 1000.0f - ((BossCurHp / BossPrevHp) * 1000.0f), 14.0f });

		int NumArr[4] = { 0, };
		int Digit;

		for (Digit = 0; Damage > 0; Digit++)
		{
			NumArr[Digit] = Damage % 10;
			Damage /= 10;
		}

		for (int i = Digit; i > 0; i--)
		{
			std::string TextureName = "Number_" + std::to_string(NumArr[i - 1]) + ".Png";

			//BossDamageNumberRender1 = CreateComponent<GameEngineUIRenderer>();
			if (i == 3)
			{
				BossDamageNumberRender3->SetSprite(TextureName);
				BossDamageNumberRender3->On();
			}
			if (i == 2)
			{
				BossDamageNumberRender2->SetSprite(TextureName);
				BossDamageNumberRender2->On();
			}
			if (i == 1)
			{
				BossDamageNumberRender1->SetSprite(TextureName);
				BossDamageNumberRender1->On();
			}
			//BossDamageNumberRender1->Transform.SetLocalPosition({ 670.0f - i * 20.0f, -330.0f });
		}
		Dam = true;
	}
	if (GameEngineInput::IsDown('9', this))
	{
		BossCurHp -= 10;
		Boss_DamageBar->SetImageScale({ 10.0f, 14.0f });
		Damage = 10;
		BossDamageNumberRender3->Off();
		BossDamageNumberRender2->Off();
		BossDamageNumberRender1->Off();
	}
	if (GameEngineInput::IsDown('0', this))
	{
		BossCurHp -= 10;
		Damage = 10;
		Dam = true;
	}
		
	if (Dam == true)
	{
		if (CurTime += _Delta)
		{
			if (CurTime >= Time)
			{
				DamageCal();
				Dam = false;
				CurTime = 0;
			}
		}
	}

	/*Boss_DamageBar->Transform.SetLocalPosition({
	Boss_Hp->Transform.GetLocalPosition().X + (BossCurHp / BossHp) * 963.0f,
	Boss_Hp->Transform.GetLocalPosition().Y - 30.0f });*/

	//Boss_DamageBar->Transform.SetLocalPosition({
	//Boss_Hp->Transform.GetLocalPosition().X + (BossCurHp / BossHp) * 1000.0f,
	//Boss_Hp->Transform.GetLocalPosition().Y - 30.0f });

	Boss_DamageBar->Transform.SetLocalPosition({
	Boss_Hp->Transform.GetLocalPosition().X, Boss_Hp->Transform.GetLocalPosition().Y });// -30.0f});

	Boss_Hp->SetImageScale({ (BossCurHp / BossHp) * 1000.0f, 13.0f });

	float Test = (BossCurHp / BossHp) * 963.0f;
	int a = 0;
}

void BossHpBar::DamageCal()
{
	Boss_DamageBar->SetImageScale({ (BossCurHp / BossHp) * 1000.0f, 13.0f });
}

void BossHpBar::Release()
{
	Death();
}