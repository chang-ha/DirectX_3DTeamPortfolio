#include "PreCompile.h"
#include "Monster_HollowSoldier_RoundShield.h"
#include "BoneSocketCollision.h"
#include "Monster_HitInteraction.h"

Monster_HollowSoldier_RoundShield::Monster_HollowSoldier_RoundShield()
{
}

Monster_HollowSoldier_RoundShield::~Monster_HollowSoldier_RoundShield()
{
}

void Monster_HollowSoldier_RoundShield::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Sword);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RoundShield);
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
	Stat.SetHp(167);
	Stat.SetAtt(1);
	//Stat.SetPoise(1000);

	ShieldCollision = CreateSocketCollision(Enum_CollisionOrder::Monster_Shield, Enum_Hollow_BoneType::RoundShield, { float4(13.0f, 55.0f, 55.0f), float4::ZERONULL, float4(0.08f, 0.0f, -0.12f)}, "RoundShield");
	ShieldCollision->SetCollisionType(ColType::OBBBOX3D);
	ShieldCollision->On();

	// 105 4 7 / 0.33 0.0 0.02
	SwordCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_Hollow_BoneType::Sword, { float4(106.0f, 4.0f, 7.0f), float4::ZERONULL, float4(0.33f, 0.0f, 0.015f) });
	SwordCollision->SetCollisionType(ColType::OBBBOX3D);

	Sword.Init(this, SwordCollision.get());
	Sword.On();

	//ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
}
void Monster_HollowSoldier_RoundShield::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_RoundShield::ChangeState(Enum_HollowSoldier_RoundShield_State _State)
{
	if (_State != ShieldState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_RoundShield_State::Idle1:
			State_Idle1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle3:
			State_Idle3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle2ToIdle1:
			State_Idle2ToIdle1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle1ToIdle2:
			State_Idle1ToIdle2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle2ToIdle3:
			State_Idle2ToIdle3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Idle3ToIdle2:
			State_Idle3ToIdle2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Front:
			State_Walk_Front_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Back:
			State_Walk_Back_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Left:
			State_Walk_Left_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Right:
			State_Walk_Right_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Front3:
			State_Walk_Front3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Back3:
			State_Walk_Back3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Left3:
			State_Walk_Left3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Walk_Right3:
			State_Walk_Right3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Run:
			State_Run_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Run3:
			State_Run3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::RH_TwinSlash:
			State_RH_TwinSlash_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack1:
			State_Attack1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack2:
			State_Attack2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack3:
			State_Attack3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack4:
			State_Attack4_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack5:
			State_Attack5_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack6:
			State_Attack6_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Attack7:
			State_Attack7_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left2:
			State_Turn_Left2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right2:
			State_Turn_Right2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice2:
			State_Turn_Left_Twice2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice2:
			State_Turn_Right_Twice2_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left1:
			State_Turn_Left1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right1:
			State_Turn_Right1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice1:
			State_Turn_Left_Twice1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice1:
			State_Turn_Right_Twice1_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left3:
			State_Turn_Left3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right3:
			State_Turn_Right3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice3:
			State_Turn_Left_Twice3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice3:
			State_Turn_Right_Twice3_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Guard:
			State_Guard_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::GuardBreak:
			State_GuardBreak_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Hit_Front:
			State_Hit_Front_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Hit_Back:
			State_Hit_Back_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Hit_Left:
			State_Hit_Left_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Hit_Right:
			State_Hit_Right_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_RoundShield_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	ShieldState = _State;
}
void Monster_HollowSoldier_RoundShield::StateUpdate(float _Delta)
{
	switch (ShieldState)
	{
	case Enum_HollowSoldier_RoundShield_State::Idle1:
		return State_Idle1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle3:
		return State_Idle3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle2ToIdle1:
		return State_Idle2ToIdle1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle1ToIdle2:
		return State_Idle1ToIdle2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle2ToIdle3:
		return State_Idle2ToIdle3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Idle3ToIdle2:
		return State_Idle3ToIdle2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Front:
		return State_Walk_Front_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Back:
		return State_Walk_Back_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Left:
		return State_Walk_Left_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Right:
		return State_Walk_Right_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Front3:
		return State_Walk_Front3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Back3:
		return State_Walk_Back3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Left3:
		return State_Walk_Left3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Walk_Right3:
		return State_Walk_Right3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Run:
		return State_Run_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Run3:
		return State_Run3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack1:
		return State_Attack1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack2:
		return State_Attack2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack3:
		return State_Attack3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack4:
		return State_Attack4_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack5:
		return State_Attack5_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack6:
		return State_Attack6_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Attack7:
		return State_Attack7_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left2:
		return State_Turn_Left2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right2:
		return State_Turn_Right2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice2:
		return State_Turn_Left_Twice2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice2:
		return State_Turn_Right_Twice2_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left1:
		return State_Turn_Left1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right1:
		return State_Turn_Right1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice1:
		return State_Turn_Left_Twice1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice1:
		return State_Turn_Right_Twice1_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left3:
		return State_Turn_Left3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right3:
		return State_Turn_Right3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice3:
		return State_Turn_Left_Twice3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice3:
		return State_Turn_Right_Twice3_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Guard:
		return State_Guard_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::GuardBreak:
		return State_GuardBreak_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Hit_Front:
		return State_Hit_Front_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Hit_Back:
		return State_Hit_Back_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Hit_Left:
		return State_Hit_Left_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Hit_Right:
		return State_Hit_Right_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_RoundShield::ChangeAttackState()
{
	if (GetTargetDistance_e() == Enum_TargetDist::Melee)
	{
		AttackPattern = ContentsRandom::RandomInt(8, 13);
	}
	else
	{
		AttackPattern = ContentsRandom::RandomInt(1, 10);
	}
	
	switch (AttackPattern)
	{
	case 1:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack1);
		break;
	case 2:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack2);
		break;
	case 3:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack3);
		break;
	case 4:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack4);
		break;
	case 5:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack5);
		break;
	case 6:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack6);
		break;
	case 7:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Attack7);
		break;
	case 8:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Back3);
		break;
	case 9:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Left3);
		break;
	case 10:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Right3);
		break;
	case 11:
	case 12:
	case 13:
		ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Front3);
		break;
	default:
		break;
	}
}

void Monster_HollowSoldier_RoundShield::ChangeHitState()
{
	if (true == Hit.IsHit())
	{
		if (true == Hit.IsGuardSuccesss())
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Guard);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::Guard_Break))
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::GuardBreak);
			return;
		}


		Enum_DirectionXZ_Quat HitDir = Hit.GetHitDir();
		BodyCollision->Off();

		switch (HitDir)
		{
		case Enum_DirectionXZ_Quat::F:
			ChangeState(Enum_HollowSoldier_RoundShield_State::Hit_Front);
			break;
		case Enum_DirectionXZ_Quat::R:
			ChangeState(Enum_HollowSoldier_RoundShield_State::Hit_Right);
			break;
		case Enum_DirectionXZ_Quat::B:
			ChangeState(Enum_HollowSoldier_RoundShield_State::Hit_Back);
			break;
		case Enum_DirectionXZ_Quat::L:
			ChangeState(Enum_HollowSoldier_RoundShield_State::Hit_Left);
			break;
		default:
			ChangeState(Enum_HollowSoldier_RoundShield_State::Hit_Front);
			break;
		}
	}
	else
	{
		return;
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_RoundShield::State_Idle1_Update(float _Delta)
{
	StateTime += _Delta;

	// 트리거 발동시
	if (StateTime >= 5.0f)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Scout);
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_RoundShield::State_Idle2_Update(float _Delat)
{
	// 

	// 거의 상시로? 아니면 일정 거리 안에 있으면?
	if (true)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2ToIdle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle3_Start()
{
	//Debug
	{
		AttackPattern++;
	}

	// GuardOn
	MainRenderer->ChangeAnimation("c1100_Idle3");
}
void Monster_HollowSoldier_RoundShield::State_Idle3_Update(float _Delta)
{
	StateTime += _Delta;
	SetFlag(Enum_ActorFlag::Guarding, true);

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
			ChangeState(Enum_HollowSoldier_RoundShield_State::Turn_Left3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Turn_Right3);
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Turn_Left_Twice3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Turn_Right_Twice3);
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
			ChangeState(Enum_HollowSoldier_RoundShield_State::Run3);
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Medium)
		{
			StateTime = 0.0f;
			ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Front3);
		}
		else
		{
			StateTime = 0.0f;
			ChangeAttackState();
			/*if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_HollowSoldier_RoundShield_State::Walk_Front3);
			}
			else
			{
				StateTime = 0.0f;
				ChangeAttackState();
			}*/
		}

	}
}

void Monster_HollowSoldier_RoundShield::State_Idle2ToIdle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2ToIdle1");
}
void Monster_HollowSoldier_RoundShield::State_Idle2ToIdle1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle1ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1ToIdle2");
}
void Monster_HollowSoldier_RoundShield::State_Idle1ToIdle2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 29)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle2ToIdle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2ToIdle3");
}
void Monster_HollowSoldier_RoundShield::State_Idle2ToIdle3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 19)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Idle3ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle3ToIdle2");
}
void Monster_HollowSoldier_RoundShield::State_Idle3ToIdle2_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 31)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Scout");
}
void Monster_HollowSoldier_RoundShield::State_Scout_Update(float _Delta)
{
	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{

		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, RecognizeParameter))
	{
		FindTarget();
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1ToIdle2);

	}
}

void Monster_HollowSoldier_RoundShield::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Front_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Walk_Back_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Back");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Back_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Walk_Left_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Left");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Left_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Walk_Right_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Right");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Right_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Walk_Front3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front3");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Front3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 41)
	{
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Run3);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
		}
	}
	

	/*EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/
}

void Monster_HollowSoldier_RoundShield::State_Walk_Back3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.7f, 2.8f);
	MainRenderer->ChangeAnimation("c1100_Walk_Back3");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Back3_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Walk_Left3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Left3");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Left3_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Walk_Right3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Right3");
}
void Monster_HollowSoldier_RoundShield::State_Walk_Right3_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Run_Start()
{
	MainRenderer->ChangeAnimation("c1100_Run");
}
void Monster_HollowSoldier_RoundShield::State_Run_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Run3_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Run3");
}
void Monster_HollowSoldier_RoundShield::State_Run3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	WalkTime += _Delta;

	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if(WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		if (GetTargetDistance_e() == Enum_TargetDist::Melee)
		{
			// RunToSting 없나? 조사해야함.
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_RoundShield::State_RH_VerticalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
}
void Monster_HollowSoldier_RoundShield::State_RH_HorizontalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_ComboAttack");
}
void Monster_HollowSoldier_RoundShield::State_RH_ComboAttack_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_RH_TwinSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_RoundShield::State_RH_TwinSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Attack1_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_RoundShield::State_Attack1_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 57)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack2_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_RoundShield::State_Attack2_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 45)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack3_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_RoundShield::State_Attack3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
	{

		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 2)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{

		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.6f);
			MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 85)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack4_Start()
{
	MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
}
void Monster_HollowSoldier_RoundShield::State_Attack4_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 85)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack5_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_RoundShield::State_Attack5_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 85)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack6_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_Sting");
}
void Monster_HollowSoldier_RoundShield::State_Attack6_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_RH_Sting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 66)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Attack7_Start()
{
	MainRenderer->ChangeAnimation("c1100_LH_Fist");
}
void Monster_HollowSoldier_RoundShield::State_Attack7_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, false);

	ChangeHitState();

	if (CheckAnimationName("c1100_LH_Fist"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 43)
		{
			MainRenderer->ChangeAnimation("c1100_RH_ChargingSting");
		}
	}

	if (CheckAnimationName("c1100_RH_ChargingSting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 98)
		{
			ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left2");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right2");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice2");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice2");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left1");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right1");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice1");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice1");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle1);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left3");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right3");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice3");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Left_Twice3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice3");
}
void Monster_HollowSoldier_RoundShield::State_Turn_Right_Twice3_Update(float _Delta)
{
	SetFlag(Enum_ActorFlag::Guarding, true);

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_Guard_Start()
{
	Hit.SetHit(false);
	Hit.SetGuardSuccesss(false);
	MainRenderer->ChangeAnimation("c1100_Guard");
}
void Monster_HollowSoldier_RoundShield::State_Guard_Update(float _Delta)
{
	
	if (MainRenderer->GetCurAnimationFrame() >= 25)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}
}

void Monster_HollowSoldier_RoundShield::State_GuardBreak_Start()
{
	Hit.SetHit(false);
	Hit.SetGuardSuccesss(false);
	MainRenderer->ChangeAnimation("c1100_GuardBreak");
}
void Monster_HollowSoldier_RoundShield::State_GuardBreak_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_HollowSoldier_RoundShield::State_AttackFail_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 40)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_RoundShield::State_Parrying_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Hit_Front_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_RoundShield::State_Hit_Front_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		BodyCollision->On();
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Hit_Back_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Back");
}
void Monster_HollowSoldier_RoundShield::State_Hit_Back_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		BodyCollision->On();
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Hit_Left_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Left");
}
void Monster_HollowSoldier_RoundShield::State_Hit_Left_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		BodyCollision->On();
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_Hit_Right_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Right");
}
void Monster_HollowSoldier_RoundShield::State_Hit_Right_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		BodyCollision->On();
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle2);
	}
}

void Monster_HollowSoldier_RoundShield::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_RoundShield::State_HitToDeath_Update(float _Delta)
{
	// 죽는 애니메이션 재생중 무기 Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::Sword);
		MeshOff(Enum_Hollow_MeshIndex::RoundShield);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Death);
	}
}

void Monster_HollowSoldier_RoundShield::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_RoundShield::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_RoundShield::State_Death_Update(float _Delta)
{

}