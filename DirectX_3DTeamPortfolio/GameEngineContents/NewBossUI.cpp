#include "PreCompile.h"
#include "NewBossUI.h"

#include "Boss_Vordt.h"

NewBossUI::NewBossUI()
{
}

NewBossUI::~NewBossUI()
{

}

#define BossHpPos {-400.0f, -230.0f}
#define DamagePos {390.0f, -200.0f}

#define ImageXScale 800.0f
#define BackBarYScale 18.0f
#define HpBarYScale 11.0f

#define DamageFontScale 18.0f

void NewBossUI::Start()
{
	Boss_HpBackBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackBar);
	Boss_HpBackBar->SetSprite("BossBar.Png");
	Boss_HpBackBar->SetImageScale({ ImageXScale, BackBarYScale });
	Boss_HpBackBar->Transform.SetLocalPosition(BossHpPos);
	Boss_HpBackBar->SetPivotType(PivotType::Left);

	Boss_DamageBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_BackGauge);
	Boss_DamageBar->SetSprite("DamageBar.Png");
	Boss_DamageBar->AutoSpriteSizeOff();
	Boss_DamageBar->SetImageScale({ ImageXScale, HpBarYScale });
	Boss_DamageBar->Transform.SetLocalPosition(BossHpPos);
	Boss_DamageBar->SetPivotType(PivotType::Left);

	Boss_HpBar = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_StatGauge);
	Boss_HpBar->SetSprite("BossHp.Png");
	Boss_HpBar->AutoSpriteSizeOff();
	Boss_HpBar->SetPivotType(PivotType::Left);
	Boss_HpBar->Transform.SetLocalPosition(BossHpPos);

	Boss_Name = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	Boss_Name->SetText(GlobalValue::OptimusFont, "차가운 골짜기의 볼드", 20.0f, float4{ 1,1,1,1 }, FW1_LEFT);
	Boss_Name->Transform.SetLocalPosition({ Boss_HpBar->Transform.GetLocalPosition().X + 5.0f,
	Boss_HpBar->Transform.GetLocalPosition().Y + 40.0f });

	BossDamageFont = CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Font);
	BossDamageFont->SetText(GlobalValue::OptimusFont, "0", DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
	BossDamageFont->Transform.SetLocalPosition(DamagePos);
	BossDamageFont->Off();

	InitState();
}

void NewBossUI::Update(float _Delta)
{
	ValidityCheck();

	BarState.Update(_Delta);
	FontState.Update(_Delta);
}

void NewBossUI::Release() 
{
	pBoss = nullptr;

	Boss_HpBackBar = nullptr;
	Boss_DamageBar = nullptr;
	Boss_HpBar = nullptr;
	Boss_Name = nullptr;
	BossDamageFont = nullptr;
}

void NewBossUI::ValidityCheck()
{
	if (nullptr == pBoss)
	{
		MsgBoxAssert("보스 포인터가 존재하지 않습니다");
		return;
	}
}

void NewBossUI::SetParent(class Boss_Vordt* _Object)
{
	pBoss = _Object;
	BossMaxHp = pBoss->GetHp();
}

void NewBossUI::Awake()
{
	On();

	if (pBoss)
	{
		const int CurHp = pBoss->GetHp();
		BossHp = CurHp;
		FontBossHp = CurHp;
		SetHPGauge(CurHp);
	}

	BarState.ChangeState(eBarState::Active_Idle);
	FontState.ChangeState(eFontState::Idle);
}

void NewBossUI::BossDamage(int _Damgae)
{
	if (pBoss)
	{
		pBoss->Damage(_Damgae);
	}
}

void NewBossUI::InitState()
{
	// Bar State
	CreateStateParameter BarIdleState;
	BarIdleState.Start = std::bind(&NewBossUI::Start_Bar_Idle, this, std::placeholders::_1);
	BarIdleState.Stay = std::bind(&NewBossUI::Update_Bar_Idle, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter BarHitState;
	BarHitState.Stay = std::bind(&NewBossUI::Update_Bar_Hit, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter BarEndState;
	BarEndState.Start = std::bind(&NewBossUI::Start_Bar_End, this, std::placeholders::_1);
	BarEndState.Stay = std::bind(&NewBossUI::Update_Bar_End, this, std::placeholders::_1, std::placeholders::_2);

	BarState.CreateState(eBarState::Active_Idle, BarIdleState);
	BarState.CreateState(eBarState::Active_Hit, BarHitState);
	BarState.CreateState(eBarState::ZERO_HP, BarEndState);

	// Font State
	CreateStateParameter FontDelayState;
	FontDelayState.Stay = std::bind(&NewBossUI::Update_Font_Delay, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter FontIdleState;
	FontIdleState.Start = std::bind(&NewBossUI::Start_Font_Idle, this, std::placeholders::_1);
	FontIdleState.Stay = std::bind(&NewBossUI::Update_Font_Idle, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter FontShowMsgState;
	FontShowMsgState.Start = std::bind(&NewBossUI::Start_Font_ShowMsg, this, std::placeholders::_1);
	FontShowMsgState.Stay = std::bind(&NewBossUI::Update_Font_ShowMsg, this, std::placeholders::_1, std::placeholders::_2);
	FontShowMsgState.End = std::bind(&NewBossUI::End_Font_ShowMsg, this, std::placeholders::_1);

	FontState.CreateState(eFontState::Delay, FontDelayState);
	FontState.CreateState(eFontState::Idle, FontIdleState);
	FontState.CreateState(eFontState::ShowMsg, FontShowMsgState);
}

// BarState_Start
void NewBossUI::Start_Bar_Idle(GameEngineState* _Parent)
{
	ValidityCheck();

	BossHp = pBoss->GetHp();
	SetDamageGauge(BossHp);
}

void NewBossUI::Start_Bar_End(GameEngineState* _Parent)
{
	BossHp = 0;
	SetHPGauge(0);
	SetDamageGauge(0);
}

// BarState_Update
void NewBossUI::Update_Bar_Idle(float _Delta, GameEngineState* _Parent)
{
	ValidityCheck();

	int CurHp = pBoss->GetHp();
	if (CurHp <= 0)
	{
		BarState.ChangeState(eBarState::ZERO_HP);
		return;
	}

	if (CurHp != BossHp)
	{
		BossHp = CurHp;
		SetHPGauge(CurHp);
		BarState.ChangeState(eBarState::Active_Hit);
	}
}

void NewBossUI::Update_Bar_Hit(float _Delta, GameEngineState* _Parent)
{
	int CurHp = pBoss->GetHp();
	if (CurHp <= 0)
	{
		BarState.ChangeState(eBarState::ZERO_HP);
		return;
	}

	if (CurHp != BossHp)
	{

		BossHp = CurHp;
		SetHPGauge(CurHp);
	}

	 float CurStaeTime = _Parent->GetStateTime();
	 if (CurStaeTime > 1.0f)
	 {
		 SetDamageGauge(BossHp);
		 BarState.ChangeState(eBarState::Active_Idle);
	 }
}

void NewBossUI::Update_Bar_End(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 3.0F)
	{
		Off();
	}
}

// BarState_Func
void NewBossUI::SetDamageGauge(int _BossHp)
{
	if (Boss_DamageBar)
	{
		const float HpRatio = static_cast<float>(_BossHp) / static_cast<float>(BossMaxHp);
		const float RenderScale = HpRatio * ImageXScale;
		Boss_DamageBar->SetImageScale({ RenderScale , HpBarYScale });
	}
}

void NewBossUI::SetHPGauge(int _BossHp)
{
	if (Boss_HpBar)
	{
		const float HpRatio = static_cast<float>(_BossHp) / static_cast<float>(BossMaxHp);
		const float RenderScale = HpRatio * ImageXScale;
		Boss_HpBar->SetImageScale({ RenderScale , HpBarYScale });
	}
}


// Font_Start
void NewBossUI::Start_Font_Idle(GameEngineState* _Parent)
{
	if (nullptr != BossDamageFont)
	{
		BossDamageFont->Off();
	}

	const int CurHp = pBoss->GetHp();
	FontBossHp = CurHp;
}

void NewBossUI::Start_Font_ShowMsg(GameEngineState* _Parent)
{
	if (nullptr != BossDamageFont)
	{
		BossDamageFont->On();
	}

	KeepStateTime = 1.0f;
}

// Font_Update
void NewBossUI::Update_Font_Delay(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 0.5f)
	{
		FontState.ChangeState(eFontState::Idle);
		return;
	}
}

void NewBossUI::Update_Font_Idle(float _Delta, GameEngineState* _Parent)
{
	int CurHp = pBoss->GetHp();
	if (CurHp != FontBossHp)
	{
		AddAndPrintDamageMsg(CurHp);
		FontState.ChangeState(eFontState::ShowMsg);
		return;
	}
}

void NewBossUI::Update_Font_ShowMsg(float _Delta, GameEngineState* _Parent)
{
	int CurHp = pBoss->GetHp();
	if (CurHp != FontBossHp)
	{
		AddAndPrintDamageMsg(CurHp);
		KeepStateTime = 1.0f;
	}
	else
	{
		KeepStateTime -= _Delta;
	}

	if (KeepStateTime <= 0.0f)
	{
		FontState.ChangeState(eFontState::Delay);
	}
}

// Font_End
void NewBossUI::End_Font_ShowMsg(GameEngineState* _Parent)
{
	if (BossDamageFont)
	{
		BossDamageFont->Off();
	}

	FontRenderDamage = 0;
}

void NewBossUI::AddAndPrintDamageMsg(int _CurBossHp)
{
	if (nullptr == BossDamageFont)
	{

	}

	const int DamageInt = FontBossHp - _CurBossHp;
	FontRenderDamage += DamageInt;
	BossDamageFont->ChangeText(std::to_string(FontRenderDamage));

	FontBossHp = _CurBossHp;
}