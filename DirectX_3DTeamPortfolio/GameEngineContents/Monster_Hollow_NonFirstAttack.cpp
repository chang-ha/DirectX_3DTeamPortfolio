#include "PreCompile.h"
#include "Monster_Hollow_NonFirstAttack.h"
#include "BoneSocketCollision.h"

Monster_Hollow_NonFirstAttack::Monster_Hollow_NonFirstAttack()
{
}

Monster_Hollow_NonFirstAttack::~Monster_Hollow_NonFirstAttack()
{
}

void Monster_Hollow_NonFirstAttack::Start()
{
	Monster_Hollow::Start();
	//PrevState = Enum_Hollow_State::Pray3;
	//ChangeState(Enum_Hollow_State::PrayToIdle);
	//MainRenderer->ChangeAnimation("c1100_PrayToIdle3");

	// Status
	Stat.SetHp(68);
	//Stat.SetHp(500);
	Stat.SetAtt(10);
	Stat.SetSouls(ContentsRandom::RandomInt(30, 50));

	CheckLanternCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster_FindLantern);
	CheckLanternCollision->SetCollisionType(ColType::SPHERE3D);
	CheckLanternCollision->SetCollisionColor(float4::BLACK);
	CheckLanternCollision->Transform.SetLocalPosition(float4(0, 100, 0));
	CheckLanternCollision->Transform.SetWorldScale(float4(300, 300, 300));

	//AttackRangeCollision->Off();

	//RecognizeCollision->Transform.SetWorldScale(float4(3000.0f, 3000.0f, 3000.0f));
	RecognizeCollision->Transform.SetWorldScale(float4(5000.0f, 5000.0f, 5000.0f));
	
	SwordCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_Hollow_BoneType::Sword, { float4(62.0f, 4.0f, 7.0f), float4::ZERONULL, float4(0.16f, 0.0f, 0.015f) });
	SwordCollision->SetCollisionType(ColType::OBBBOX3D);

	Sword.Init(this, SwordCollision.get());
	//Sword.On();
	
	ChangeState(Enum_Hollow_State::Pray1);

	CreateMonsterUI(73);
}

void Monster_Hollow_NonFirstAttack::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_Hollow_NonFirstAttack::Release()
{
	Monster_Hollow::Release();
}

void Monster_Hollow_NonFirstAttack::LevelStart(class GameEngineLevel* _NextLevel)
{
	Monster_Hollow::LevelStart(_NextLevel);
}

void Monster_Hollow_NonFirstAttack::Reset()
{
	DeathValue = false;

	Sword.ResetRecord();

	Stat.SetHp(68);

	Hit.SetHit(false);

	//MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	SetFlagNull();
	SetTargeting(nullptr);

	RecognizeCollision->On();
	BodyCollision->On();
	MonsterCollision->On();

	ChangeState(Enum_Hollow_State::Pray1);
}

void Monster_Hollow_NonFirstAttack::ChangeState(Enum_Hollow_State _State)
{
	if (_State != HollowState)
	{
		switch (_State)
		{
		case Enum_Hollow_State::Pray1:
			State_Pray1_Start();
			break;
		case Enum_Hollow_State::Pray2:
			State_Pray2_Start();
			break;
		case Enum_Hollow_State::Pray3:
			State_Pray3_Start();
			break;
		case Enum_Hollow_State::PrayToBeScared1:
			State_PrayToBeScared1_Start();
			break;
		case Enum_Hollow_State::PrayToBeScared2:
			State_PrayToBeScared2_Start();
			break;
		case Enum_Hollow_State::PrayToBeScared3:
			State_PrayToBeScared3_Start();
			break;
		case Enum_Hollow_State::BeScared:
			State_BeScared_Start();
			break;
		case Enum_Hollow_State::PrayToIdle1:
			State_PrayToIdle1_Start();
			break;
		case Enum_Hollow_State::PrayToIdle2:
			State_PrayToIdle2_Start();
			break;
		case Enum_Hollow_State::PrayToIdle3:
			State_PrayToIdle3_Start();
			break;
		case Enum_Hollow_State::BeScaredToIdle:
			State_BeScaredToIdle_Start();
			break;
		case Enum_Hollow_State::Idle:
			State_Idle_Start();
			break;
		case Enum_Hollow_State::Walk_Front:
			State_Walk_Front_Start();
			break;
		case Enum_Hollow_State::Walk_Back:
			State_Walk_Back_Start();
			break;
		case Enum_Hollow_State::Walk_Left:
			State_Walk_Left_Start();
			break;
		case Enum_Hollow_State::Walk_Right:
			State_Walk_Right_Start();
			break;
		case Enum_Hollow_State::Run:
			State_Run_Start();
			break;
		case Enum_Hollow_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_Hollow_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_Hollow_State::TH_VerticalSlash:
			State_TH_VerticalSlash_Start();
			break;
		case Enum_Hollow_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_Hollow_State::RH_RunToSlash:
			State_RH_RunToSlash_Start();
			break;
		case Enum_Hollow_State::Turn_Left2:
			State_Turn_Left2_Start();
			break;
		case Enum_Hollow_State::Turn_Right2:
			State_Turn_Right2_Start();
			break;
		case Enum_Hollow_State::Turn_Left_Twice2:
			State_Turn_Left_Twice2_Start();
			break;
		case Enum_Hollow_State::Turn_Right_Twice2:
			State_Turn_Right_Twice2_Start();
			break;
		case Enum_Hollow_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_Hollow_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_Hollow_State::Hit_Front:
			State_Hit_Front_Start();
			break;
		case Enum_Hollow_State::Hit_Back:
			State_Hit_Back_Start();
			break;
		case Enum_Hollow_State::Hit_Left:
			State_Hit_Left_Start();
			break;
		case Enum_Hollow_State::Hit_Right:
			State_Hit_Right_Start();
			break;
		case Enum_Hollow_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_Hollow_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_Hollow_State::BackAttackDeath:
			State_BackAttackDeath_Start();
			break;
		case Enum_Hollow_State::AfterGuardBreakHit:
			State_AfterGuardBreakHit_Start();
			break;
		case Enum_Hollow_State::AfterGuardBreakDeath:
			State_AfterGuardBreakDeath_Start();
			break;
		case Enum_Hollow_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	HollowState = _State;
}

void Monster_Hollow_NonFirstAttack::StateUpdate(float _Delta)
{
	switch (HollowState)
	{
	case Enum_Hollow_State::Pray1:
		return State_Pray1_Update(_Delta);
	case Enum_Hollow_State::Pray2:
		return State_Pray2_Update(_Delta);
	case Enum_Hollow_State::Pray3:
		return State_Pray3_Update(_Delta);
	case Enum_Hollow_State::PrayToBeScared1:
		return State_PrayToBeScared1_Update(_Delta);
	case Enum_Hollow_State::PrayToBeScared2:
		return State_PrayToBeScared2_Update(_Delta);
	case Enum_Hollow_State::PrayToBeScared3:
		return State_PrayToBeScared3_Update(_Delta);
	case Enum_Hollow_State::BeScared:
		return State_BeScared_Update(_Delta);
	case Enum_Hollow_State::PrayToIdle1:
		return State_PrayToIdle1_Update(_Delta);
	case Enum_Hollow_State::PrayToIdle2:
		return State_PrayToIdle2_Update(_Delta);
	case Enum_Hollow_State::PrayToIdle3:
		return State_PrayToIdle3_Update(_Delta);
	case Enum_Hollow_State::BeScaredToIdle:
		return State_BeScaredToIdle_Update(_Delta);
	case Enum_Hollow_State::Idle:
		return State_Idle_Update(_Delta);
	case Enum_Hollow_State::Walk_Front:
		return State_Walk_Front_Update(_Delta);
	case Enum_Hollow_State::Walk_Back:
		return State_Walk_Back_Update(_Delta);
	case Enum_Hollow_State::Walk_Left:
		return State_Walk_Left_Update(_Delta);
	case Enum_Hollow_State::Walk_Right:
		return State_Walk_Right_Update(_Delta);
	case Enum_Hollow_State::Run:
		return State_Run_Update(_Delta);
	case Enum_Hollow_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_Hollow_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_Hollow_State::TH_VerticalSlash:
		return State_TH_VerticalSlash_Update(_Delta);
	case Enum_Hollow_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_Hollow_State::RH_RunToSlash:
		return State_RH_RunToSlash_Update(_Delta);
	case Enum_Hollow_State::Turn_Left2:
		return State_Turn_Left2_Update(_Delta);
	case Enum_Hollow_State::Turn_Right2:
		return State_Turn_Right2_Update(_Delta);
	case Enum_Hollow_State::Turn_Left_Twice2:
		return State_Turn_Left_Twice2_Update(_Delta);
	case Enum_Hollow_State::Turn_Right_Twice2:
		return State_Turn_Right_Twice2_Update(_Delta);
	case Enum_Hollow_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_Hollow_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_Hollow_State::Hit_Front:
		return State_Hit_Front_Update(_Delta);
	case Enum_Hollow_State::Hit_Back:
		return State_Hit_Back_Update(_Delta);
	case Enum_Hollow_State::Hit_Left:
		return State_Hit_Left_Update(_Delta);
	case Enum_Hollow_State::Hit_Right:
		return State_Hit_Right_Update(_Delta);
	case Enum_Hollow_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_Hollow_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_Hollow_State::BackAttackDeath:
		return State_BackAttackDeath_Update(_Delta);
	case Enum_Hollow_State::AfterGuardBreakHit:
		return State_AfterGuardBreakHit_Update(_Delta);
	case Enum_Hollow_State::AfterGuardBreakDeath:
		return State_AfterGuardBreakDeath_Update(_Delta);
	case Enum_Hollow_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_Hollow_NonFirstAttack::ChangeAttackState()
{
	if (GetTargetDistance_e() == Enum_TargetDist::Melee)
	{
		AttackPattern = ContentsRandom::RandomInt(5, 10);
	}
	else
	{
		AttackPattern = ContentsRandom::RandomInt(1, 4);
	}
	//AttackPattern = 2;
	
	switch (AttackPattern)  
	{
	case 1:
		ChangeState(Enum_Hollow_State::RH_VerticalSlash);
		break;
	case 2:
		ChangeState(Enum_Hollow_State::RH_HorizontalSlash);
		break;
	case 3:
		ChangeState(Enum_Hollow_State::TH_VerticalSlash);
		break;
	case 4:
		ChangeState(Enum_Hollow_State::RH_ComboAttack);
		break;
	case 5:
		ChangeState(Enum_Hollow_State::Walk_Back);
		break;
	case 6:
		ChangeState(Enum_Hollow_State::Walk_Left);
		break;
	case 7:
		ChangeState(Enum_Hollow_State::Walk_Right);
		break;
	case 8:
	case 9:
	case 10:
		ChangeState(Enum_Hollow_State::Walk_Front);
		break;
	default:
		break;
	}
}

void Monster_Hollow_NonFirstAttack::ChangeHitState()
{
	if (true == Hit.IsHit())
	{
		if (true == IsFlag(Enum_ActorFlag::FrontStab))
		{
			ChangeState(Enum_Hollow_State::AfterGuardBreakHit);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::BackStab))
		{
			ChangeState(Enum_Hollow_State::BackAttackHit);
			return;
		}

		if (Stat.GetHp() <= 0)
		{
			ChangeState(Enum_Hollow_State::HitToDeath);
			return;
		}

		Enum_DirectionXZ_Quat HitDir = Hit.GetHitDir();
		//BodyCollision->Off();

		switch (HitDir)
		{
		case Enum_DirectionXZ_Quat::F:
			HollowState = Enum_Hollow_State::Max;
			ChangeState(Enum_Hollow_State::Hit_Front);
			break;
		case Enum_DirectionXZ_Quat::R:
			HollowState = Enum_Hollow_State::Max;
			ChangeState(Enum_Hollow_State::Hit_Right);
			break;
		case Enum_DirectionXZ_Quat::B:
			HollowState = Enum_Hollow_State::Max;
			ChangeState(Enum_Hollow_State::Hit_Back);
			break;
		case Enum_DirectionXZ_Quat::L:
			HollowState = Enum_Hollow_State::Max;
			ChangeState(Enum_Hollow_State::Hit_Left);
			break;
		default:
			HollowState = Enum_Hollow_State::Max;
			ChangeState(Enum_Hollow_State::Hit_Front);
			break;
		}
	}
	else
	{
		return;
	}
}

void Monster_Hollow_NonFirstAttack::CheckAwake()
{
	EventParameter AwakeParameter;
	AwakeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			//_Other->Off();
			AwakeValue = true;
		};

	CheckLanternCollision->CollisionEvent(Enum_CollisionOrder::Monster_Lantern, AwakeParameter);
}

void Monster_Hollow_NonFirstAttack::NonFindTarget(float _Delta)
{
	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Player, RecognizeParameter))
	{
		FindTarget();
	}
	else
	{
		if (RecognizeCollision->IsUpdate() == true)
		{
			RecognizeCollision->Transform.AddWorldScale(float4(5000.0f * _Delta, 5000.0f * _Delta, 5000.0f * _Delta));
		}
	}
}

void Monster_Hollow_NonFirstAttack::State_Pray1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray1");
}
void Monster_Hollow_NonFirstAttack::State_Pray1_Update(float _Delta)
{
	//StateTime += _Delta;
	//if (StateTime > 3.0f)
	//{
	//	ChangeState(Enum_Hollow_State::PrayToBeScared1);
	//}

	ChangeHitState();


	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared1);
		return;
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle1);
		return;
	}

	// Test
	/*StateTime += _Delta;

	if (StateTime >= 3.0f)
	{
		StateTime = 0.0f;
		ChangeState(Enum_Hollow_State::PrayToBeScared1);
	}*/
}

void Monster_Hollow_NonFirstAttack::State_Pray2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray2");
}
void Monster_Hollow_NonFirstAttack::State_Pray2_Update(float _Delta)
{
	ChangeHitState();
	
	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared2);
		return;
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle2);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Pray3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray3");
}
void Monster_Hollow_NonFirstAttack::State_Pray3_Update(float _Delta)
{
	//StateTime += _Delta;
	//if (StateTime > 3.0f)
	//{
	//	ChangeState(Enum_Hollow_State::PrayToIdle3);
	//}

	ChangeHitState();

	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared3);
		return;
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle3);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared1_Start()
{
	/*if (PrevState == Enum_Hollow_State::Pray1)
	{
		MainRenderer->ChangeAnimation("c1100_PrayToBeScared1");
	}
	else if (PrevState == Enum_Hollow_State::Pray2)
	{
		MainRenderer->ChangeAnimation("c1100_PrayToBeScared2");
	}
	else if (PrevState == Enum_Hollow_State::Pray3)
	{
		MainRenderer->ChangeAnimation("c1100_PrayToBeScared3");
	}
	else
	{
		MainRenderer->ChangeAnimation("c1100_PrayToBeScared1");
	}*/
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared1");
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared2_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared2");
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared3_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared3");
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared3_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_BeScared_Start()
{
	MainRenderer->ChangeAnimation("c1100_BeScared");
	//StateTime = 0.0f;
}
void Monster_Hollow_NonFirstAttack::State_BeScared_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime > 3.0f)
	{
		ChangeState(Enum_Hollow_State::BeScaredToIdle);
	}*/

	ChangeHitState();

	// 랜턴 효과 받았을때
	if (false)
	{
		ChangeState(Enum_Hollow_State::BeScaredToIdle);
		return;
	}

	// Test
	StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		StateTime = 0.0f;
		ChangeState(Enum_Hollow_State::BeScaredToIdle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle1_Start()
{
	//if (PrevState == Enum_Hollow_State::Pray1)
	//{
	//	MainRenderer->ChangeAnimation("c1100_PrayToIdle1");
	//}
	//else if (PrevState == Enum_Hollow_State::Pray2)
	//{
	//	MainRenderer->ChangeAnimation("c1100_PrayToIdle2");
	//}
	//else if (PrevState == Enum_Hollow_State::Pray3)
	//{
	//	// 이거 애니메이션 중간에 끊김. 애니메이션 자체가 그렇게 되어있음.
	//	// 해결방법 필요.
	//	MainRenderer->ChangeAnimation("c1100_PrayToIdle3");
	//}
	//else
	//{
	//	MainRenderer->ChangeAnimation("c1100_PrayToIdle1");
	//}

	MainRenderer->ChangeAnimation("c1100_PrayToIdle1");
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle1_Update(float _Delta)
{
	NonFindTarget(_Delta);

	ChangeHitState();

	// Pray 마다 무기 꺼내는 프레임 다름 수정 필요.
	if (MainRenderer->GetCurAnimationFrame() >= 31)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToIdle2");
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle2_Update(float _Delta)
{
	NonFindTarget(_Delta);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 37)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToIdle3");
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle3_Update(float _Delta)
{
	NonFindTarget(_Delta);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_BeScaredToIdle_Start()
{
	MainRenderer->ChangeAnimation("c1100_BeScaredToIdle");
}
void Monster_Hollow_NonFirstAttack::State_BeScaredToIdle_Update(float _Delta)
{
	NonFindTarget(_Delta);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Idle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_Hollow_NonFirstAttack::State_Idle_Update(float _Delta)
{
	StateTime += _Delta;

	ChangeHitState();

	if (BodyCollision->IsUpdate() == false)
	{
		BodyCollision->On();
	}

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle >= 90.0f && AbsTargetAngle <= 150.0f)
	{
		//Turn
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_Hollow_State::Turn_Left2);
			return;
		}
		else
		{
			ChangeState(Enum_Hollow_State::Turn_Right2);
			return;
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_Hollow_State::Turn_Left_Twice2);
			return;
		}
		else
		{
			ChangeState(Enum_Hollow_State::Turn_Right_Twice2);
			return;
		}
	}
	else if (AbsTargetAngle < 80.0f)
	{
		if (false == IsTargetInAngle(3.0f))
		{
			RotToTarget(_Delta);
		}
	}

	/*EventParameter AttackParameter;
	AttackParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			IsAttack = true;
		};
	AttackParameter.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			IsAttack = false;
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/

	if (StateTime >= 0.1f)
	{
		// 거리 구하기
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			//RunToSting
			StateTime = 0.0f;
			ChangeState(Enum_Hollow_State::Run);
			return;
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Medium)
		{
			StateTime = 0.0f;
			ChangeState(Enum_Hollow_State::Walk_Front);
			return;
		}
		else
		{
			StateTime = 0.0f;
			ChangeAttackState();

			//if (IsAttack == false)
			//{
			//	StateTime = 0.0f;
			//	ChangeState(Enum_Hollow_State::Walk_Front);
			//}
			//else
			//{
			//	StateTime = 0.0f;
			//	ChangeAttackState();
			//	//ChangeState(Enum_Hollow_State::Walk_Front);
			//}
		}

	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Front_Update(float _Delta)
{
	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 41)
	{
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			// Idle로 넘어갈지 바로 Run으로 넘어갈지 조사해야할듯..
			ChangeState(Enum_Hollow_State::Run);
			return;
		}
		else
		{
			ChangeState(Enum_Hollow_State::Idle);
			return;
		}
	}

	

	/*EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_Hollow_State::Idle);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/
}

void Monster_Hollow_NonFirstAttack::State_Walk_Back_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.7f, 2.8f);
	MainRenderer->ChangeAnimation("c1100_Walk_Back");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Back_Update(float _Delta)
{
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Left_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Left");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Left_Update(float _Delta)
{
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Right_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Right");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Right_Update(float _Delta)
{
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Run_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.8f, 1.6f);
	MainRenderer->ChangeAnimation("c1100_Run");
}
void Monster_Hollow_NonFirstAttack::State_Run_Update(float _Delta)
{
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (GetTargetDistance_e() == Enum_TargetDist::Close)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		if (GetTargetDistance_e() == Enum_TargetDist::Melee)
		{
			ChangeState(Enum_Hollow_State::RH_RunToSlash);
			return;
		}
		/*else if (GetTargetDistance_e() == Enum_TargetDist::Close)
		{
			ChangeState(Enum_Hollow_State::Idle);
			return;
		}*/
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_VerticalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 21)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 22)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 61)
	{
		Sword.ResetRecord();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_HorizontalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
			
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 25)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 53)
	{
		Sword.ResetRecord();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_TH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_TH_VerticalSlash");
}
void Monster_Hollow_NonFirstAttack::State_TH_VerticalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 28 && MainRenderer->GetCurAnimationFrame() <= 31)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 32)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 73)
	{
		Sword.ResetRecord();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_ComboAttack");
}
void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Update(float _Delta)
{
	ChangeHitState();

	// 1st
	if (MainRenderer->GetCurAnimationFrame() >= 32 && MainRenderer->GetCurAnimationFrame() <= 36)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 37)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 38 && MainRenderer->GetCurAnimationFrame() <= 39)
	{
		Sword.ResetRecord();
	}

	// 2nd
	if (MainRenderer->GetCurAnimationFrame() >= 50 && MainRenderer->GetCurAnimationFrame() <= 53)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 54)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 55 && MainRenderer->GetCurAnimationFrame() <= 56)
	{
		Sword.ResetRecord();
	}

	// 3rd
	if (MainRenderer->GetCurAnimationFrame() >= 63 && MainRenderer->GetCurAnimationFrame() <= 67)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 68)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 69 && MainRenderer->GetCurAnimationFrame() <= 70)
	{
		Sword.ResetRecord();
	}

	// 4th
	if (MainRenderer->GetCurAnimationFrame() >= 71 && MainRenderer->GetCurAnimationFrame() <= 74)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 75)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 76 && MainRenderer->GetCurAnimationFrame() <= 77)
	{
		Sword.ResetRecord();
	}

	// 5th
	if (MainRenderer->GetCurAnimationFrame() >= 78 && MainRenderer->GetCurAnimationFrame() <= 82)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 83)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 84 && MainRenderer->GetCurAnimationFrame() <= 85)
	{
		Sword.ResetRecord();
	}

	// 6th
	if (MainRenderer->GetCurAnimationFrame() >= 92 && MainRenderer->GetCurAnimationFrame() <= 95)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 96)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 165)
	{
		Sword.ResetRecord();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_RunToSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_RunToSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_RunToSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 29 && MainRenderer->GetCurAnimationFrame() <= 32)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			if (true == IsFlag(Enum_ActorFlag::Break_Posture))
			{
				ChangeState(Enum_Hollow_State::Parrying);
				return;
			}
			else
			{
				ChangeState(Enum_Hollow_State::AttackFail);
				return;
			}
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}

	}

	if (MainRenderer->GetCurAnimationFrame() >= 32)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 82)
	{
		Sword.ResetRecord();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Left2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Right2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Left_Twice2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Right_Twice2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_AttackFail_Start()
{
	Hit.SetHit(false);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_Hollow_NonFirstAttack::State_AttackFail_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 40)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Parrying_Start()
{
	Hit.SetHit(false);
	Sword.Off();
	Sword.ResetRecord();
	SetFlag(Enum_ActorFlag::Break_Posture, false);
	SetFlag(Enum_ActorFlag::Groggy, true);
	MainRenderer->ChangeAnimation("c1100_Parrying");

}
void Monster_Hollow_NonFirstAttack::State_Parrying_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		SetFlag(Enum_ActorFlag::Groggy, false);
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Hit_Front_Start()
{
	Hit.SetHit(false);
	// 무기가 없는 상태일때 맞았을때 꺼내야됨
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Hit_Front");

	// 이 전에 있던 State가 Pray 또는 BeScared일때
	// 타게팅은 여기서 이루어짐.
}
void Monster_Hollow_NonFirstAttack::State_Hit_Front_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Hit_Back_Start()
{
	Hit.SetHit(false);
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Hit_Back");
}
void Monster_Hollow_NonFirstAttack::State_Hit_Back_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Hit_Left_Start()
{
	Hit.SetHit(false);
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Hit_Left");
}
void Monster_Hollow_NonFirstAttack::State_Hit_Left_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_Hit_Right_Start()
{
	Hit.SetHit(false);
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Hit_Right");
}
void Monster_Hollow_NonFirstAttack::State_Hit_Right_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_HitToDeath_Start()
{
	if (DeathValue == false)
	{
		DeathFunc();
	}

	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_Hollow_NonFirstAttack::State_HitToDeath_Update(float _Delta)
{
	// 죽는 애니메이션 재생중 무기 Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Death);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_BackAttackHit_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_Hollow_NonFirstAttack::State_BackAttackHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 80)
		{
			ChangeState(Enum_Hollow_State::BackAttackDeath);
			return;
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 167)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_BackAttackDeath_Start()
{
	if (DeathValue == false)
	{
		DeathFunc();
	}

	MainRenderer->ChangeAnimation("c1100_BackAttackDeath");
}
void Monster_Hollow_NonFirstAttack::State_BackAttackDeath_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 56)
	{
		MeshOff(Enum_Hollow_MeshIndex::BrokenSword);
	}
}

void Monster_Hollow_NonFirstAttack::State_AfterGuardBreakHit_Start()
{
	Hit.SetHit(false);
	SetFlag(Enum_ActorFlag::Groggy, false);
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakHit");
}
void Monster_Hollow_NonFirstAttack::State_AfterGuardBreakHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 140)
		{
			MeshOff(Enum_Hollow_MeshIndex::BrokenSword);

			ChangeState(Enum_Hollow_State::AfterGuardBreakDeath);
			return;
		}
	}
	if (MainRenderer->GetCurAnimationFrame() >= 194)
	{
		ChangeState(Enum_Hollow_State::Idle);
		return;
	}
}

void Monster_Hollow_NonFirstAttack::State_AfterGuardBreakDeath_Start()
{
	if (DeathValue == false)
	{
		DeathFunc();
	}

	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakDeath");
}
void Monster_Hollow_NonFirstAttack::State_AfterGuardBreakDeath_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 63)
	{
		MeshOff(Enum_Hollow_MeshIndex::BrokenSword);
	}
}

void Monster_Hollow_NonFirstAttack::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_Hollow_NonFirstAttack::State_Death_Update(float _Delta)
{

}