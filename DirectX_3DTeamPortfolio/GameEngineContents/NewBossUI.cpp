#include "PreCompile.h"
//#include "NewBossUI.h"
//#include <algorithm>
//
//#include "Boss_Vordt.h"
//
//NewBossUI::NewBossUI()
//{
//	GameEngineInput::AddInputObject(this);
//}
//
//NewBossUI::~NewBossUI()
//{
//
//}
//
//#define BossHpPos {-400.0f, -230.0f}
//#define DamagePos {390.0f, -200.0f}
//
//#define ImageXScale 800.0f
//#define BackBarYScale 18.0f
//#define HpBarYScale 11.0f
//
//#define DamageFontScale 18.0f
//
//void NewBossUI::Start()
//{
//	Boss_HpBackBar = CreateComponent<GameEngineUIRenderer>();
//	Boss_HpBackBar->SetSprite("BossBar.Png");
//	Boss_HpBackBar->SetImageScale({ ImageXScale, BackBarYScale });
//	Boss_HpBackBar->Transform.SetLocalPosition(BossHpPos);
//	Boss_HpBackBar->SetPivotType(PivotType::Left);
//
//	Boss_DamageBar = CreateComponent<GameEngineUIRenderer>();
//	Boss_DamageBar->SetSprite("DamageBar.Png");
//	Boss_DamageBar->AutoSpriteSizeOff();
//	Boss_DamageBar->SetImageScale({ ImageXScale, HpBarYScale });
//	Boss_DamageBar->Transform.SetLocalPosition(BossHpPos);
//	Boss_DamageBar->SetPivotType(PivotType::Left);
//
//	Boss_HpBar = CreateComponent<GameEngineUIRenderer>();
//	Boss_HpBar->SetSprite("BossHp.Png");
//	Boss_HpBar->AutoSpriteSizeOff();
//	Boss_HpBar->SetPivotType(PivotType::Left);
//	Boss_HpBar->Transform.SetLocalPosition(BossHpPos);
//
//	Boss_Name = CreateComponent<GameEngineUIRenderer>();
//	Boss_Name->SetText(GlobalValue::OptimusFont, "차가운 골짜기의 볼드", 20.0f, float4{ 1,1,1,1 }, FW1_LEFT);
//	Boss_Name->Transform.SetLocalPosition({ Boss_HpBar->Transform.GetLocalPosition().X + 5.0f,
//	Boss_HpBar->Transform.GetLocalPosition().Y + 40.0f });
//
//	BossDamageFont = CreateComponent<GameEngineUIRenderer>();
//	BossDamageFont->SetText(GlobalValue::OptimusFont, "0", DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
//	BossDamageFont->Transform.SetLocalPosition(DamagePos);
//	BossDamageFont->Off();
//
//	InitState();
//}
//
//void NewBossUI::Update(float _Delta)
//{
//	ValidityCheck();
//
//	BarState.Update(_Delta);
//}
//
//void NewBossUI::ValidityCheck()
//{
//	if (nullptr == Boss_Object)
//	{
//		MsgBoxAssert("보스 포인터가 존재하지 않습니다");
//		return;
//	}
//}
//
//void NewBossUI::SetParent(class Boss_Vordt* _Object)
//{
//	Boss_Object = _Object;
//	BossMaxHp = static_cast<float>(Boss_Object->GetHp());
//}
//
//void NewBossUI::AwakeState()
//{
//	On();
//	BarState.ChangeState(eBarState::Idle);
//}
//
//void NewBossUI::DeathProcess()
//{
//	Off();
//	BarState.ChangeState(eBarState::End);
//}
//
//void NewBossUI::InitState()
//{
//	CreateStateParameter BarWakeState;
//	BarWakeState.Start = std::bind(&NewBossUI::Start_Bar_Awake, this, std::placeholders::_1);
//
//	CreateStateParameter BarIdleState;
//	BarWakeState.Start = std::bind(&NewBossUI::Start_Bar_Awake, this, std::placeholders::_1);
//
//	CreateStateParameter BarHitState;
//	BarWakeState.Start = std::bind(&NewBossUI::Start_Bar_Awake, this, std::placeholders::_1);
//	BarWakeState.Stay = std::bind(&NewBossUI::Update_Bar_Hit, this, std::placeholders::_1, std::placeholders::_2);
//
//	CreateStateParameter BarEndState;
//	BarWakeState.Start = std::bind(&NewBossUI::Start_Bar_Awake, this, std::placeholders::_1);
//
//	BarState.CreateState(eBarState::Awake, BarWakeState);
//	BarState.CreateState(eBarState::Idle, BarIdleState);
//	BarState.CreateState(eBarState::Hit, BarHitState);
//	BarState.CreateState(eBarState::End, BarEndState);
//}
//
//// BarState_Start
//void NewBossUI::Start_Bar_Idle(GameEngineState* _Parent)
//{
//	ValidityCheck();
//
//	BossHp = Boss_Object->GetHp();
//	SetDamageGauge(BossHp);
//}
//
//void NewBossUI::Start_Bar_Hit(GameEngineState* _Parent)
//{
//
//}
//
//void NewBossUI::Start_Bar_End(GameEngineState* _Parent)
//{
//
//}
//
//// BarState_Update
//void NewBossUI::Update_Bar_Idle(float _Delta, GameEngineState* _Parent)
//{
//	ValidityCheck();
//
//	int CurHp = Boss_Object->GetHp();
//	if (CurHp != BossHp)
//	{
//		BarState.ChangeState(eBarState::Hit);
//	}
//}
//
//void NewBossUI::Update_Bar_Hit(float _Delta, GameEngineState* _Parent)
//{
//	 float CurStaeTime = _Parent->GetStateTime();
//	 if (CurStaeTime > 1.0f)
//	 {
//		 SetDamageGauge(BossHp);
//		 BarState.ChangeState(eBarState::Idle);
//	 }
//}
//
//// BarState_Func
//void NewBossUI::SetDamageGauge(int _BossHp)
//{
//	if (Boss_DamageBar)
//	{
//		const float HpRatio = static_cast<float>(_BossHp) / static_cast<float>(BossMaxHp);
//		const float RenderScale = HpRatio * ImageXScale;
//		Boss_DamageBar->SetImageScale({ RenderScale , HpBarYScale });
//	}
//}
//
//void NewBossUI::BossBarUpdate()
//{
//	if (BossCurHp <= 0.0f)
//	{
//		Boss_DamageBar->Transform.SetLocalPosition({
//		Boss_HpBar->Transform.GetLocalPosition().X, Boss_HpBar->Transform.GetLocalPosition().Y });
//		Boss_HpBar->SetImageScale({ (0.0f / BossHp) * ImageXScale, HpBarYScale });
//		return;
//	}
//
//	if (BossCurHp > 0.0f)
//	{
//		Boss_DamageBar->Transform.SetLocalPosition({
//		Boss_HpBar->Transform.GetLocalPosition().X, Boss_HpBar->Transform.GetLocalPosition().Y });
//		Boss_HpBar->SetImageScale({ (BossCurHp / BossHp) * ImageXScale, HpBarYScale });
//	}
//}
//
//void NewBossUI::DamageCal()
//{
//	if (BossCurHp <= 0.0f)
//	{
//		Boss_DamageBar->SetImageScale({ (0.0f / BossHp) * ImageXScale, HpBarYScale });
//		return;
//	}
//
//	if (BossCurHp > 0.0f)
//	{
//		Boss_DamageBar->SetImageScale({ (BossCurHp / BossHp) * ImageXScale, HpBarYScale });
//	}
//}
//
//void NewBossUI::Release()
//{
//	Boss_HpBackBar = nullptr;
//	Boss_DamageBar = nullptr;
//	Boss_HpBar = nullptr;
//	Boss_Name = nullptr;
//	BossDamageFont = nullptr;
//}
//
//void NewBossUI::ChangeState(eHpState _State)
//{
//	if (_State != BHpActor)
//	{
//		switch (_State)
//		{
//		case eHpState::Off:
//			OffStart();
//			break;
//		case eHpState::Appear:
//			AppearStart();
//			break;
//		case eHpState::Add:
//			AddStart();
//			break;
//		case eHpState::None:
//		default:
//			MsgBoxAssert("없는 상태로 NewBossUI의 상태를 바꾸려 했습니다.");
//			break;
//		}
//	}
//
//	BHpActor = _State;
//}
//
//void NewBossUI::StateUpdate(float _Delta)
//{
//	switch (BHpActor)
//	{
//	case eHpState::Off:
//		return OffUpdate(_Delta);
//	case eHpState::Appear:
//		return AppearUpdate(_Delta);
//	case eHpState::Add:
//		return AddUpdate(_Delta);
//	case eHpState::None:
//	default:
//		break;
//	}
//}
//
//void NewBossUI::OffStart()
//{
//	BossDamageFont->Off();
//}
//
//void NewBossUI::OffUpdate(float _Delta)
//{
//	if (BossCurHp <= 0.0f)
//	{
//		return;
//	}
//
//	if (BossCurHp == BossPrevHp)
//	{
//		return;
//	}
//
//	ChangeState(eHpState::Appear);
//}
//
//void NewBossUI::AppearStart()
//{
//	BossDamageFont->On();
//
//	DamRan.SetSeed(time(nullptr));
//	DamageRandom = (DamRan.RandomInt(50, 100));
//	Damage = DamageRandom;
//
//	BossCurHp -= Damage;
//	BossPrevHp = BossCurHp;
//
//	SumDam = Damage;
//	Dam = true;
//}
//
//void NewBossUI::AppearUpdate(float _Delta)
//{
//	BossDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(Damage), DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
//
//	if (Dam == true)
//	{
//		if (BossCurHp != BossPrevHp)
//		{
//			ChangeState(eHpState::Add);
//			return;
//		}
//
//		CurTime += _Delta;
//		{
//			if (CurTime >= Time)
//			{
//				DamageCal();
//				Dam = false;
//				CurTime = 0;
//				ChangeState(eHpState::Off);
//				return;
//			}
//		}
//	}
//}
//
//void NewBossUI::AddStart()
//{
//	SumDam += Damage;
//
//	BossCurHp -= Damage;
//	BossPrevHp = BossCurHp;
//}
//
//void NewBossUI::AddUpdate(float _Delta)
//{
//	BossDamageFont->SetText(GlobalValue::OptimusFont, std::to_string(SumDam), DamageFontScale, float4{ 1,1,1,1 }, FW1_RIGHT);
//	CurTime += _Delta;
//	{
//		if (CurTime >= Time)
//		{
//			SumDam = 0;
//			DamageCal();
//			Dam = false;
//			CurTime = 0;
//			ChangeState(eHpState::Off);
//			return;
//		}
//	}
//}