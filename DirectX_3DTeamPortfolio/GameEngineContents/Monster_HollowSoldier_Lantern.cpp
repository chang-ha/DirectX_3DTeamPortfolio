#include "PreCompile.h"
#include "Monster_HollowSoldier_Lantern.h"
#include "BoneSocketCollision.h"

Monster_HollowSoldier_Lantern::Monster_HollowSoldier_Lantern()
{
}

Monster_HollowSoldier_Lantern::~Monster_HollowSoldier_Lantern()
{
}

void Monster_HollowSoldier_Lantern::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::InnerHood);	
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Lantern);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::BrokenSword);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shirt1);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Belt1);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LongSkirt1);

	// Status
	Stat.SetHp(83);
	Stat.SetAtt(1);

	AwakeCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster_Lantern);
	AwakeCollision->SetCollisionType(ColType::SPHERE3D);
	AwakeCollision->SetCollisionColor(float4::BLACK);
	AwakeCollision->Transform.SetLocalPosition(float4(0, 100, 0));
	AwakeCollision->Transform.SetWorldScale(float4(1000.0f, 1000.0f, 1000.0f));
	AwakeCollision->Off();

	//																										 62 4 7 / 0.16 0.0 0.015
	SwordCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_Hollow_BoneType::Sword, { float4(62.0f, 4.0f, 7.0f), float4::ZERONULL, float4(0.16f, 0.0f, 0.015f) });
	SwordCollision->SetCollisionType(ColType::OBBBOX3D);

	Sword.Init(this, SwordCollision.get());
	Sword.On();

	ChangeState(Enum_HollowSoldier_Lantern_State::Stay);

	CreateMonsterUI(0);
}
void Monster_HollowSoldier_Lantern::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}
void Monster_HollowSoldier_Lantern::Release()
{
	Monster_Hollow::Release();
}
void Monster_HollowSoldier_Lantern::LevelStart(class GameEngineLevel* _NextLevel)
{
	Monster_Hollow::LevelStart(_NextLevel);
}

void Monster_HollowSoldier_Lantern::WakeUp()
{
	ChangeState(Enum_HollowSoldier_Lantern_State::Scout);
}

void Monster_HollowSoldier_Lantern::ChangeState(Enum_HollowSoldier_Lantern_State _State)
{
	if (_State != LanternState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Lantern_State::Stay:
			State_Stay_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Idle:
			State_Idle_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::IdleToStay:
			State_IdleToStay_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::StayToIdle:
			State_StayToIdle_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Walk_Front:
			State_Walk_Front_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Walk_Back:
			State_Walk_Back_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Walk_Left:
			State_Walk_Left_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Walk_Right:
			State_Walk_Right_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Run:
			State_Run_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AwakeHollows:
			State_AwakeHollows_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::TH_VerticalSlash:
			State_TH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_RunToSlash:
			State_RH_RunToSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Scout_Turn_Left_Twice:
			State_Scout_Turn_Left_Twice_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Turn_Left:
			State_Turn_Left_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Turn_Right:
			State_Turn_Right_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Turn_Left_Twice:
			State_Turn_Left_Twice_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Turn_Right_Twice:
			State_Turn_Right_Twice_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Hit_Front:
			State_Hit_Front_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Hit_Back:
			State_Hit_Back_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Hit_Left:
			State_Hit_Left_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Hit_Right:
			State_Hit_Right_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::BackAttackDeath:
			State_BackAttackDeath_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AfterGuardBreakHit:
			State_AfterGuardBreakHit_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AfterGuardBreakDeath:
			State_AfterGuardBreakDeath_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	LanternState = _State;
}
void Monster_HollowSoldier_Lantern::StateUpdate(float _Delta)
{
	switch (LanternState)
	{
	case Enum_HollowSoldier_Lantern_State::Stay:
		return State_Stay_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Idle:
		return State_Idle_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::IdleToStay:
		return State_IdleToStay_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::StayToIdle:
		return State_StayToIdle_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Walk_Front:
		return State_Walk_Front_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Walk_Back:
		return State_Walk_Back_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Walk_Left:
		return State_Walk_Left_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Walk_Right:
		return State_Walk_Right_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Run:
		return State_Run_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Scout_Turn_Left_Twice:
		return State_Scout_Turn_Left_Twice_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AwakeHollows:
		return State_AwakeHollows_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::TH_VerticalSlash:
		return State_TH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_RunToSlash:
		return State_RH_RunToSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Turn_Left:
		return State_Turn_Left_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Turn_Right:
		return State_Turn_Right_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Turn_Left_Twice:
		return State_Turn_Left_Twice_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Turn_Right_Twice:
		return State_Turn_Right_Twice_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Hit_Front:
		return State_Hit_Front_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Hit_Back:
		return State_Hit_Back_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Hit_Left:
		return State_Hit_Left_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Hit_Right:
		return State_Hit_Right_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::BackAttackDeath:
		return State_BackAttackDeath_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AfterGuardBreakHit:
		return State_AfterGuardBreakHit_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AfterGuardBreakDeath:
		return State_AfterGuardBreakDeath_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Lantern::ChangeAttackState()
{
	if (GetTargetDistance_e() == Enum_TargetDist::Melee)
	{
		AttackPattern = ContentsRandom::RandomInt(5, 10);
	}
	else
	{
		AttackPattern = ContentsRandom::RandomInt(1, 7);
	}
	

	switch (AttackPattern)
	{
	case 1:
		ChangeState(Enum_HollowSoldier_Lantern_State::RH_VerticalSlash);
		break;
	case 2:
		ChangeState(Enum_HollowSoldier_Lantern_State::RH_HorizontalSlash);
		break;
	case 3:
		ChangeState(Enum_HollowSoldier_Lantern_State::TH_VerticalSlash);
		break;
	case 4:
		ChangeState(Enum_HollowSoldier_Lantern_State::RH_ComboAttack);
		break;
	case 5:
		ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Back);
		break;
	case 6:
		ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Left);
		break;
	case 7:
		ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Right);
		break;
	case 8:
	case 9:
	case 10:
		ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Front);
		break;
	default:
		break;
	}
}

void Monster_HollowSoldier_Lantern::ChangeHitState()
{
	if (true == Hit.IsHit())
	{
		if (true == IsFlag(Enum_ActorFlag::FrontStab))
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AfterGuardBreakHit);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::BackStab))
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::BackAttackHit);
			return;
		}

		if (Stat.GetHp() <= 0)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::HitToDeath);
			return;
		}

		Enum_DirectionXZ_Quat HitDir = Hit.GetHitDir();
		//BodyCollision->Off();

		switch (HitDir)
		{
		case Enum_DirectionXZ_Quat::F:
			ChangeState(Enum_HollowSoldier_Lantern_State::Hit_Front);
			break;
		case Enum_DirectionXZ_Quat::R:
			ChangeState(Enum_HollowSoldier_Lantern_State::Hit_Right);
			break;
		case Enum_DirectionXZ_Quat::B:
			ChangeState(Enum_HollowSoldier_Lantern_State::Hit_Back);
			break;
		case Enum_DirectionXZ_Quat::L:
			ChangeState(Enum_HollowSoldier_Lantern_State::Hit_Left);
			break;
		default:
			ChangeState(Enum_HollowSoldier_Lantern_State::Hit_Front);
			break;
		}
	}
	else
	{
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Stay_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_Lantern::State_Stay_Update(float _Delta)
{
	StateTime += _Delta;

	ChangeHitState();

	// 트리거 발동시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Scout);
		return;
	}

	/*if (StateTime >= 5.0f)
	{
		StateTime = 0.0f;
		ChangeState(Enum_HollowSoldier_Lantern_State::Scout);
	}*/
}

void Monster_HollowSoldier_Lantern::State_Idle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Idle");
}
void Monster_HollowSoldier_Lantern::State_Idle_Update(float _Delta)
{
	ChangeHitState();
	// 여기서부터는 공격
	StateTime += _Delta;

	ChangeAttackState();

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
			ChangeState(Enum_HollowSoldier_Lantern_State::Turn_Left);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Turn_Right);
			return;
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Turn_Left_Twice);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Turn_Right_Twice);
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
			StateTime = 0.0;
			ChangeState(Enum_HollowSoldier_Lantern_State::Run);
			return;
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Medium)
		{
			StateTime = 0.0f;
			ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Front);
			return;
		}
		else
		{
			StateTime = 0.0f;
			ChangeAttackState();
			/*if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_HollowSoldier_Lantern_State::Walk_Front);
			}
			else
			{
				StateTime = 0.0f;
				ChangeAttackState();
			}*/
		}

	}
}

void Monster_HollowSoldier_Lantern::State_IdleToStay_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_IdleToStay");
}
void Monster_HollowSoldier_Lantern::State_IdleToStay_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Stay);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_StayToIdle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_StayToIdle");
}
void Monster_HollowSoldier_Lantern::State_StayToIdle_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 29)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Walk_Front");
}
void Monster_HollowSoldier_Lantern::State_Walk_Front_Update(float _Delta)
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
			ChangeState(Enum_HollowSoldier_Lantern_State::Run);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
			return;
		}
	}

	


	/*EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/
}

void Monster_HollowSoldier_Lantern::State_Walk_Back_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.7f, 2.8f);
	MainRenderer->ChangeAnimation("c1100_Lantern_Walk_Back");
}
void Monster_HollowSoldier_Lantern::State_Walk_Back_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Walk_Left_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Lantern_Walk_Left");
}
void Monster_HollowSoldier_Lantern::State_Walk_Left_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Walk_Right_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Lantern_Walk_Right");
}
void Monster_HollowSoldier_Lantern::State_Walk_Right_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Run_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Lantern_Run");
}
void Monster_HollowSoldier_Lantern::State_Run_Update(float _Delta)
{
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		WalkTime = 0.0f;
		if (GetTargetDistance_e() == Enum_TargetDist::Melee)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::RH_RunToSlash);
			return;
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Close)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
			return;
		}
	}
}

void Monster_HollowSoldier_Lantern::State_Scout_Start()
{
	ScoutTime = 0.0f;
	MainRenderer->ChangeAnimation("c1100_Lantern_Scout");
}
void Monster_HollowSoldier_Lantern::State_Scout_Update(float _Delta)
{
	ChangeHitState();

	// 플레이어 인식시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::AwakeHollows);
		return;
	}

	ScoutTime += _Delta;

	if (ScoutTime >= 15.0f)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Scout_Turn_Left_Twice);
	}

	//ChangeAttackState();

	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Player, RecognizeParameter))
	{
		FindTarget();
		ChangeState(Enum_HollowSoldier_Lantern_State::AwakeHollows);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_AwakeHollows_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_AwakeHollows");
}
void Monster_HollowSoldier_Lantern::State_AwakeHollows_Update(float _Delta)
{
	// 어떤 프레임에서 비선공 몬스터들 Idle로 변경

	// 프레임 조금 더 연구할것.
	// 이 애니메이션이 끝나면 확실하게 Idle 상태로 가는지.

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 76 && MainRenderer->GetCurAnimationFrame() <= 79)
	{
		if (AwakeCollision->IsUpdate() != true && AwakeValue == false)
		{
			AwakeCollision->On();
			AwakeValue = true;
		}
	}

	if (AwakeCollision->IsUpdate() == true)
	{
		//AwakeCollision->Transform.AddWorldScale(float4(_Delta * 500.0f, _Delta * 500.0f, _Delta * 500.0f));
	}

	/*if (MainRenderer->GetCurAnimationFrame() >= 80)
	{
		if (AwakeCollision->IsUpdate() == true)
		{
			AwakeCollision->Off();
		}
	}*/

	if (MainRenderer->GetCurAnimationFrame() >= 80)
	{
		if (AwakeCollision->IsUpdate() == true)
		{
			AwakeCollision->Off();
		}
		
	}

	if (MainRenderer->GetCurAnimationFrame() >= 80)
	{
		AwakeCollision->Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{

		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_VerticalSlash");
}
void Monster_HollowSoldier_Lantern::State_RH_VerticalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 21)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_HorizontalSlash");
}
void Monster_HollowSoldier_Lantern::State_RH_HorizontalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_TH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_TH_VerticalSlash");
}
void Monster_HollowSoldier_Lantern::State_TH_VerticalSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 28 && MainRenderer->GetCurAnimationFrame() <= 31)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_ComboAttack");
}
void Monster_HollowSoldier_Lantern::State_RH_ComboAttack_Update(float _Delta)
{
	ChangeHitState();

	// 1st
	if (MainRenderer->GetCurAnimationFrame() >= 32 && MainRenderer->GetCurAnimationFrame() <= 36)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_RH_RunToSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_BrokenSword_RH_RunToSlash");
}
void Monster_HollowSoldier_Lantern::State_RH_RunToSlash_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 29 && MainRenderer->GetCurAnimationFrame() <= 32)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AttackFail);
			return;
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
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Scout_Turn_Left_Twice_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice");
}
void Monster_HollowSoldier_Lantern::State_Scout_Turn_Left_Twice_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Scout);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Turn_Left_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Turn_Left");
}
void Monster_HollowSoldier_Lantern::State_Turn_Left_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Turn_Right_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Turn_Right");
}
void Monster_HollowSoldier_Lantern::State_Turn_Right_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Turn_Left_Twice_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Turn_Left_Twice");
}
void Monster_HollowSoldier_Lantern::State_Turn_Left_Twice_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Turn_Right_Twice_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Turn_Right_Twice");
}
void Monster_HollowSoldier_Lantern::State_Turn_Right_Twice_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_AttackFail_Start()
{
	Hit.SetHit(false);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_HollowSoldier_Lantern::State_AttackFail_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 40)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Parrying_Start()
{
	Hit.SetHit(false);
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_Lantern::State_Parrying_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Hit_Front_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Lantern::State_Hit_Front_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Hit_Back_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Back");
}
void Monster_HollowSoldier_Lantern::State_Hit_Back_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Hit_Left_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Left");
}
void Monster_HollowSoldier_Lantern::State_Hit_Left_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_Hit_Right_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Right");
}
void Monster_HollowSoldier_Lantern::State_Hit_Right_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_Lantern::State_HitToDeath_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		//MeshOff(Enum_Hollow_MeshIndex::Sword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Death);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Lantern::State_BackAttackHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 80)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::BackAttackDeath);
			return;
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 167)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_BackAttackDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackDeath");
}
void Monster_HollowSoldier_Lantern::State_BackAttackDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_AfterGuardBreakHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakHit");
}
void Monster_HollowSoldier_Lantern::State_AfterGuardBreakHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 140)
		{
			ChangeState(Enum_HollowSoldier_Lantern_State::AfterGuardBreakDeath);
			return;
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 194)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
		return;
	}
}

void Monster_HollowSoldier_Lantern::State_AfterGuardBreakDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakDeath");
}
void Monster_HollowSoldier_Lantern::State_AfterGuardBreakDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_Lantern::State_Death_Update(float _Delta)
{

}