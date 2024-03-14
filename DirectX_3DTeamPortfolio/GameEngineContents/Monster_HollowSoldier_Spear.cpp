#include "PreCompile.h"
#include "Monster_HollowSoldier_Spear.h"
#include "BoneSocketCollision.h"

Monster_HollowSoldier_Spear::Monster_HollowSoldier_Spear()
{
}

Monster_HollowSoldier_Spear::~Monster_HollowSoldier_Spear()
{
}

void Monster_HollowSoldier_Spear::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Spear);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::WoodShield);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ChainMail);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ShoulderRobe);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Helmat);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::TopRobe);

	// Status
	Stat.SetHp(190);
	Stat.SetAtt(1);
	
	

	ShieldCollision = CreateSocketCollision(Enum_CollisionOrder::Monster_Shield, Enum_Hollow_BoneType::WoodShield, { float4(14.0f, 56.0f ,126.0f), float4::ZERONULL, float4(0.12f,0.02f, -0.08f)}, "WoodShield");
	ShieldCollision->SetCollisionType(ColType::OBBBOX3D);
	ShieldCollision->On();

	SpearCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_Hollow_BoneType::Sword, { float4(313.0f, 12.0f, 12.0f), float4::ZERONULL, float4(0.38f, -0.002f, 0.008f) }, "Spear");
	SpearCollision->SetCollisionType(ColType::OBBBOX3D);

	Spear.Init(this, SpearCollision.get());
	Spear.On();
}
void Monster_HollowSoldier_Spear::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_Spear::ChangeState(Enum_HollowSoldier_Spear_State _State)
{
	if (_State != SpearState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Spear_State::Idle1:
			State_Idle1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle3:
			State_Idle3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle2ToIdle1:
			State_Idle2ToIdle1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle1ToIdle2:
			State_Idle1ToIdle2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle2ToIdle3:
			State_Idle2ToIdle3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle3ToIdle2:
			State_Idle3ToIdle2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Front2:
			State_Walk_Front2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Back2:
			State_Walk_Back2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Left2:
			State_Walk_Left2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Right2:
			State_Walk_Right2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Front3:
			State_Walk_Front3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Back3:
			State_Walk_Back3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Left3:
			State_Walk_Left3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Walk_Right3:
			State_Walk_Right3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Run:
			State_Run_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Run3:
			State_Run3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack1:
			State_Attack1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack2:
			State_Attack2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack3:
			State_Attack3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack4:
			State_Attack4_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack5:
			State_Attack5_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack6:
			State_Attack6_Start();
			break;
		case Enum_HollowSoldier_Spear_State::RunToPike:
			State_RunToPike_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left2:
			State_Turn_Left2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right2:
			State_Turn_Right2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left_Twice2:
			State_Turn_Left_Twice2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right_Twice2:
			State_Turn_Right_Twice2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left1:
			State_Turn_Left1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right1:
			State_Turn_Right1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left_Twice1:
			State_Turn_Left_Twice1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right_Twice1:
			State_Turn_Right_Twice1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left3:
			State_Turn_Left3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right3:
			State_Turn_Right3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Left_Twice3:
			State_Turn_Left_Twice3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Turn_Right_Twice3:
			State_Turn_Right_Twice3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Guard:
			State_Guard_Start();
			break;
		case Enum_HollowSoldier_Spear_State::GuardBreak:
			State_GuardBreak_Start();
			break;
		case Enum_HollowSoldier_Spear_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Hit_Front:
			State_Hit_Front_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Hit_Back:
			State_Hit_Back_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Hit_Left:
			State_Hit_Left_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Hit_Right:
			State_Hit_Right_Start();
			break;
		case Enum_HollowSoldier_Spear_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Spear_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Spear_State::BackAttackDeath:
			State_BackAttackDeath_Start();
			break;
		case Enum_HollowSoldier_Spear_State::AfterGuardBreakHit:
			State_AfterGuardBreakHit_Start();
			break;
		case Enum_HollowSoldier_Spear_State::AfterGuardBreakDeath:
			State_AfterGuardBreakDeath_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	SpearState = _State;
}
void Monster_HollowSoldier_Spear::StateUpdate(float _Delta)
{
	switch (SpearState)
	{
	case Enum_HollowSoldier_Spear_State::Idle1:
		return State_Idle1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle3:
		return State_Idle3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle2ToIdle1:
		return State_Idle2ToIdle1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle1ToIdle2:
		return State_Idle1ToIdle2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle2ToIdle3:
		return State_Idle2ToIdle3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle3ToIdle2:
		return State_Idle3ToIdle2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Front2:
		return State_Walk_Front2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Back2:
		return State_Walk_Back2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Left2:
		return State_Walk_Left2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Right2:
		return State_Walk_Right2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Front3:
		return State_Walk_Front3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Back3:
		return State_Walk_Back3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Left3:
		return State_Walk_Left3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Walk_Right3:
		return State_Walk_Right3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Run:
		return State_Run_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Run3:
		return State_Run3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack1:
		return State_Attack1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack2:
		return State_Attack2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack3:
		return State_Attack3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack4:
		return State_Attack4_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack5:
		return State_Attack5_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack6:
		return State_Attack6_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::RunToPike:
		return State_RunToPike_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left2:
		return State_Turn_Left2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right2:
		return State_Turn_Right2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left_Twice2:
		return State_Turn_Left_Twice2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right_Twice2:
		return State_Turn_Right_Twice2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left1:
		return State_Turn_Left1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right1:
		return State_Turn_Right1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left_Twice1:
		return State_Turn_Left_Twice1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right_Twice1:
		return State_Turn_Right_Twice1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left3:
		return State_Turn_Left3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right3:
		return State_Turn_Right3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Left_Twice3:
		return State_Turn_Left_Twice3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Turn_Right_Twice3:
		return State_Turn_Right_Twice3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Guard:
		return State_Guard_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::GuardBreak:
		return State_GuardBreak_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Hit_Front:
		return State_Hit_Front_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Hit_Back:
		return State_Hit_Back_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Hit_Left:
		return State_Hit_Left_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Hit_Right:
		return State_Hit_Right_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::BackAttackDeath:
		return State_BackAttackDeath_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::AfterGuardBreakHit:
		return State_AfterGuardBreakHit_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::AfterGuardBreakDeath:
		return State_AfterGuardBreakDeath_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Spear::ChangeAttackState()
{
	if (GetTargetDistance_e() == Enum_TargetDist::Melee)
	{
		AttackPattern = ContentsRandom::RandomInt(7, 12);
	}
	else
	{
		AttackPattern = ContentsRandom::RandomInt(1, 9);
	}
	
	switch (AttackPattern)
	{
	case 1:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack1);
		break;
	case 2:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack2);
		break;
	case 3:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack3);
		break;
	case 4:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack4);
		break;
	case 5:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack5);
		break;
	case 6:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack6);
		break;
	case 7:
		ChangeState(Enum_HollowSoldier_Spear_State::Walk_Back3);
		break;
	case 8:
		ChangeState(Enum_HollowSoldier_Spear_State::Walk_Left3);
		break;
	case 9:
		ChangeState(Enum_HollowSoldier_Spear_State::Walk_Right3);
		break;
	case 10:
	case 11:
	case 12:
		ChangeState(Enum_HollowSoldier_Spear_State::Walk_Front3);
		break;
	default:
		break;
	}

	//ChangeState(Enum_HollowSoldier_Spear_State::Walk_Left3);
}

void Monster_HollowSoldier_Spear::ChangeHitState()
{
	if (true == Hit.IsHit())
	{
		if (true == IsFlag(Enum_ActorFlag::FrontStab))
		{
			ChangeState(Enum_HollowSoldier_Spear_State::AfterGuardBreakHit);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::BackStab))
		{
			ChangeState(Enum_HollowSoldier_Spear_State::BackAttackHit);
			return;
		}

		if (Stat.GetHp() <= 0)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::HitToDeath);
			return;
		}

		if (true == Hit.IsGuardSuccesss())
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Guard);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::Guard_Break))
		{
			ChangeState(Enum_HollowSoldier_Spear_State::GuardBreak);
			return;
		}

		Enum_DirectionXZ_Quat HitDir = Hit.GetHitDir();
		BodyCollision->Off();
		Hit.SetHit(false);

		switch (HitDir)
		{
		case Enum_DirectionXZ_Quat::F:
			ChangeState(Enum_HollowSoldier_Spear_State::Hit_Front);
			break;
		case Enum_DirectionXZ_Quat::R:
			ChangeState(Enum_HollowSoldier_Spear_State::Hit_Right);
			break;
		case Enum_DirectionXZ_Quat::B:
			ChangeState(Enum_HollowSoldier_Spear_State::Hit_Back);
			break;
		case Enum_DirectionXZ_Quat::L:
			ChangeState(Enum_HollowSoldier_Spear_State::Hit_Left);
			break;
		default:
			ChangeState(Enum_HollowSoldier_Spear_State::Hit_Front);
			break;
		}
	}
	else
	{
		return;
	}
}

void Monster_HollowSoldier_Spear::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle1");
}
void Monster_HollowSoldier_Spear::State_Idle1_Update(float _Delta)
{
	// 트리거 발동시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Scout);
	}

	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	
	if (false == IsTargeting())
	{
		if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, RecognizeParameter))
		{
			FindTarget();
			ChangeState(Enum_HollowSoldier_Spear_State::Idle1ToIdle2);
		}
	}

	// test
	StateTime += _Delta;
	//if(false)
	if (StateTime >= 5.0f)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Scout);
	}
}

void Monster_HollowSoldier_Spear::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2");
}
void Monster_HollowSoldier_Spear::State_Idle2_Update(float _Delta)
{

	// 아마 상시로?
	if (true)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2ToIdle3);
	}
}

void Monster_HollowSoldier_Spear::State_Idle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle3");
}
void Monster_HollowSoldier_Spear::State_Idle3_Update(float _Delta)
{
	StateTime += _Delta;

	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle >= 90.0f && AbsTargetAngle <= 150.0f)
	{
		//Turn
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Turn_Left3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Turn_Right3);
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Turn_Left_Twice3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Turn_Right_Twice3);
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
			ChangeState(Enum_HollowSoldier_Spear_State::Run3);
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Medium)
		{
			StateTime = 0.0f;
			ChangeState(Enum_HollowSoldier_Spear_State::Walk_Front3);
		}
		else
		{
			StateTime = 0.0f;
			ChangeAttackState();
			/*if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_HollowSoldier_Spear_State::Walk_Front3);
			}
			else
			{
				StateTime = 0.0f;
				ChangeAttackState();
			}*/
		}

	}
}

void Monster_HollowSoldier_Spear::State_Idle2ToIdle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2ToIdle1");
}
void Monster_HollowSoldier_Spear::State_Idle2ToIdle1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Idle1ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle1ToIdle2");
}
void Monster_HollowSoldier_Spear::State_Idle1ToIdle2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 29)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Idle2ToIdle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2ToIdle3");
}
void Monster_HollowSoldier_Spear::State_Idle2ToIdle3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 19)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Idle3ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle3ToIdle2");
}
void Monster_HollowSoldier_Spear::State_Idle3ToIdle2_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 31)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Scout");
}
void Monster_HollowSoldier_Spear::State_Scout_Update(float _Delta)
{
	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, RecognizeParameter))
	{
		FindTarget();
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1ToIdle2);
	}
}

void Monster_HollowSoldier_Spear::State_Walk_Front2_Start() 
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Front2");
}
void Monster_HollowSoldier_Spear::State_Walk_Front2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk_Back2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Back2");
}
void Monster_HollowSoldier_Spear::State_Walk_Back2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Left2");
}
void Monster_HollowSoldier_Spear::State_Walk_Left2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Right2");
}
void Monster_HollowSoldier_Spear::State_Walk_Right2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk_Front3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Front3");
}
void Monster_HollowSoldier_Spear::State_Walk_Front3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 61)
	{
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Run3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
		}
	}
	

	/*EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/
}

void Monster_HollowSoldier_Spear::State_Walk_Back3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(1.05f, 3.15f);
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Back3");
}
void Monster_HollowSoldier_Spear::State_Walk_Back3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Walk_Left3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(1.05f, 3.15f);
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Left3");
}
void Monster_HollowSoldier_Spear::State_Walk_Left3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	// 프레임이 생각보다 짧음... 인게임과 다시 비교해야됨.
	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	/*if (MainRenderer->GetCurAnimationFrame() >= 63)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}*/

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Walk_Right3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(1.05f, 3.15f);
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Right3");
}
void Monster_HollowSoldier_Spear::State_Walk_Right3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Run_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Run2");
}
void Monster_HollowSoldier_Spear::State_Run_Update(float _Delta)
{
	
}

void Monster_HollowSoldier_Spear::State_Run3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Spear_Run3");
}
void Monster_HollowSoldier_Spear::State_Run3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		if (GetTargetDistance_e() == Enum_TargetDist::Melee)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::RunToPike);
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Close)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack1_Start()
{
	// Pike1
	MainRenderer->ChangeAnimation("c1100_Spear_Pike1");
}
void Monster_HollowSoldier_Spear::State_Attack1_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_Pike1"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 25)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 53)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack2_Start()
{
	// Pike1 - Pike2
	MainRenderer->ChangeAnimation("c1100_Spear_Pike1");
}
void Monster_HollowSoldier_Spear::State_Attack2_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_Pike1"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 25)
		{
			Spear.Off();
			MainRenderer->ChangeAnimation("c1100_Spear_Pike2");
		}
	}

	if (CheckAnimationName("c1100_Spear_Pike2"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 5)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 29 && MainRenderer->GetCurAnimationFrame() <= 32)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 33)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 62)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack3_Start()
{
	// Pike1 - Swing	
	MainRenderer->ChangeAnimation("c1100_Spear_Pike1");
}
void Monster_HollowSoldier_Spear::State_Attack3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_Pike1"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 25)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 53)
		{
			MainRenderer->ChangeAnimation("c1100_Spear_Swing");
		}
	}

	if (CheckAnimationName("c1100_Spear_Swing"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 5)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22 && MainRenderer->GetCurAnimationFrame() <= 26)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 27)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 68)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack4_Start()
{
	// StepAndPike
	MainRenderer->ChangeAnimation("c1100_Spear_StepAndPike");
}
void Monster_HollowSoldier_Spear::State_Attack4_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_StepAndPike"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 28 && MainRenderer->GetCurAnimationFrame() <= 31)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 32)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 91)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack5_Start()
{
	// Swing
	MainRenderer->ChangeAnimation("c1100_Spear_Swing");
}
void Monster_HollowSoldier_Spear::State_Attack5_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_Swing"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 22 && MainRenderer->GetCurAnimationFrame() <= 26)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 27)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 68)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_Attack6_Start()
{
	// Swing - Pike1
	MainRenderer->ChangeAnimation("c1100_Spear_Swing");
}
void Monster_HollowSoldier_Spear::State_Attack6_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_Spear_Swing"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 22 && MainRenderer->GetCurAnimationFrame() <= 26)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 27)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 68)
		{
			MainRenderer->ChangeAnimation("c1100_Spear_Pike1");
		}
	}

	if (CheckAnimationName("c1100_Spear_Pike1"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 5)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 24)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 25)
		{
			Spear.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 53)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Spear::State_RunToPike_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_RunToPike");
}
void Monster_HollowSoldier_Spear::State_RunToPike_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Spear.On();

			Spear.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Spear.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Spear_State::AttackFail);
			}
			else
			{
				Spear.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Spear.Off();
		}

	if (MainRenderer->GetCurAnimationFrame() >= 74)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left2");
}
void Monster_HollowSoldier_Spear::State_Turn_Left2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right2");
}
void Monster_HollowSoldier_Spear::State_Turn_Right2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice2");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice2");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left1");
}
void Monster_HollowSoldier_Spear::State_Turn_Left1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right1");
}
void Monster_HollowSoldier_Spear::State_Turn_Right1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice1");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice1");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left3");
}
void Monster_HollowSoldier_Spear::State_Turn_Left3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right3");
}
void Monster_HollowSoldier_Spear::State_Turn_Right3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice3");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice3");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_Guard_Start()
{
	Hit.SetHit(false);
	Hit.SetGuardSuccesss(false);
	MainRenderer->ChangeAnimation("c1100_Spear_Guard");
}
void Monster_HollowSoldier_Spear::State_Guard_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 25)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
	}
}

void Monster_HollowSoldier_Spear::State_GuardBreak_Start()
{
	Hit.SetHit(false);
	Hit.SetGuardSuccesss(false);
	MainRenderer->ChangeAnimation("c1100_Spear_GuardBreak");
}
void Monster_HollowSoldier_Spear::State_GuardBreak_Update(float _Delta)
{
	if(MainRenderer->GetCurAnimationFrame() >= 92)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_AttackFail");
}
void Monster_HollowSoldier_Spear::State_AttackFail_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 40)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Parrying");
}
void Monster_HollowSoldier_Spear::State_Parrying_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Hit_Front_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Spear_Hit_Front");
}
void Monster_HollowSoldier_Spear::State_Hit_Front_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		// BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Hit_Back_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Spear_Hit_Back");
}
void Monster_HollowSoldier_Spear::State_Hit_Back_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		// BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Hit_Left_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Spear_Hit_Left");
}
void Monster_HollowSoldier_Spear::State_Hit_Left_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		// BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_Hit_Right_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Spear_Hit_Right");
}
void Monster_HollowSoldier_Spear::State_Hit_Right_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		// BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HtiToDeath");
}
void Monster_HollowSoldier_Spear::State_HitToDeath_Update(float _Delta)
{
	
}

void Monster_HollowSoldier_Spear::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Spear::State_BackAttackHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 80)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::BackAttackDeath);
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 167)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_BackAttackDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackDeath");
}
void Monster_HollowSoldier_Spear::State_BackAttackDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_AfterGuardBreakHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakHit");
}
void Monster_HollowSoldier_Spear::State_AfterGuardBreakHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 140)
		{
			ChangeState(Enum_HollowSoldier_Spear_State::AfterGuardBreakDeath);
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 194)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
	}
}

void Monster_HollowSoldier_Spear::State_AfterGuardBreakDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakDeath");
}
void Monster_HollowSoldier_Spear::State_AfterGuardBreakDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_Spear::State_Death_Update(float _Delta)
{

}