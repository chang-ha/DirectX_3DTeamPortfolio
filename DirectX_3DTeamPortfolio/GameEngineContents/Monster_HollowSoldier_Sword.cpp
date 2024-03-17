#include "PreCompile.h"
#include "Monster_HollowSoldier_Sword.h"
#include "BoneSocketCollision.h"

Monster_HollowSoldier_Sword::Monster_HollowSoldier_Sword()
{
}

Monster_HollowSoldier_Sword::~Monster_HollowSoldier_Sword()
{
}

void Monster_HollowSoldier_Sword::Start() 
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Sword);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ChainMail);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);

	// Status
	Stat.SetHp(130);
	Stat.SetAtt(1);

	// 105 4 7 / 0.33 0.0 0.02
	SwordCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_Hollow_BoneType::Sword, { float4(106.0f, 4.0f, 7.0f), float4::ZERONULL, float4(0.33f, 0.0f, 0.015f) });
	SwordCollision->SetCollisionType(ColType::OBBBOX3D);

	Sword.Init(this, SwordCollision.get());
	Sword.On();
	
	//AttackRangeCollision->Off(); 

	

	ChangeState(Enum_HollowSoldier_Sword_State::Idle1);

	
}
void Monster_HollowSoldier_Sword::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);

	
}

void Monster_HollowSoldier_Sword::Release()
{
	Monster_Hollow::Release();
}

void Monster_HollowSoldier_Sword::LevelStart(class GameEngineLevel* _NextLevel)
{
	Monster_Hollow::LevelStart(_NextLevel);
}

void Monster_HollowSoldier_Sword::WakeUp()
{
	ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	return;
}

void Monster_HollowSoldier_Sword::ChangeState(Enum_HollowSoldier_Sword_State _State)
{
	if (_State != SoldierState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Sword_State::Idle1:
			State_Idle1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Idle2ToIdle1:
			State_Idle2ToIdle1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Idle1ToIdle2:
			State_Idle1ToIdle2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Walk_Front:
			State_Walk_Front_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Walk_Back:
			State_Walk_Back_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Walk_Left:
			State_Walk_Left_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Walk_Right:
			State_Walk_Right_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Run:
			State_Run_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_TwinSlash:
			State_RH_TwinSlash_Start();
			break;
		case Enum_HollowSoldier_Sword_State::RH_RunToSting:
			State_RH_RunToSting_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack1:
			State_Attack1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack2:
			State_Attack2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack3:
			State_Attack3_Start();
			break;
		/*case Enum_HollowSoldier_Sword_State::Attack4:
			State_Attack4_Start();
			break;*/
		case Enum_HollowSoldier_Sword_State::Attack5:
			State_Attack5_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack6:
			State_Attack6_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack7:
			State_Attack7_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack8:
			State_Attack8_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack9:
			State_Attack9_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack10:
			State_Attack10_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Attack11:
			State_Attack11_Start();
			break;
		/*case Enum_HollowSoldier_Sword_State::Attack12:
			State_Attack12_Start();
			break;*/
		case Enum_HollowSoldier_Sword_State::Attack13:
			State_Attack13_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Left2:
			State_Turn_Left2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Right2:
			State_Turn_Right2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Left_Twice2:
			State_Turn_Left_Twice2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Right_Twice2:
			State_Turn_Right_Twice2_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Left1:
			State_Turn_Left1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Right1:
			State_Turn_Right1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Left_Twice1:
			State_Turn_Left_Twice1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Turn_Right_Twice1:
			State_Turn_Right_Twice1_Start();
			break;
		case Enum_HollowSoldier_Sword_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Hit_Front:
			State_Hit_Front_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Hit_Back:
			State_Hit_Back_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Hit_Left:
			State_Hit_Left_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Hit_Right:
			State_Hit_Right_Start();
			break;
		case Enum_HollowSoldier_Sword_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Sword_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Sword_State::BackAttackDeath:
			State_BackAttackDeath_Start();
			break;
		case Enum_HollowSoldier_Sword_State::AfterGuardBreakHit:
			State_AfterGuardBreakHit_Start();
			break;
		case Enum_HollowSoldier_Sword_State::AfterGuardBreakDeath:
			State_AfterGuardBreakDeath_Start();
			break;
		case Enum_HollowSoldier_Sword_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	SoldierState = _State;
}
void Monster_HollowSoldier_Sword::StateUpdate(float _Delta)
{
	switch (SoldierState)
	{
	case Enum_HollowSoldier_Sword_State::Idle1:
		return State_Idle1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Idle2ToIdle1:
		return State_Idle2ToIdle1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Idle1ToIdle2:
		return State_Idle1ToIdle2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Walk_Front:
		return State_Walk_Front_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Walk_Back:
		return State_Walk_Back_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Walk_Left:
		return State_Walk_Left_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Walk_Right:
		return State_Walk_Right_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Run:
		return State_Run_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_RunToSting:
		return State_RH_RunToSting_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack1:
		return State_Attack1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack2:
		return State_Attack2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack3:
		return State_Attack3_Update(_Delta);
	/*case Enum_HollowSoldier_Sword_State::Attack4:
		return State_Attack4_Update(_Delta);*/
	case Enum_HollowSoldier_Sword_State::Attack5:
		return State_Attack5_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack6:
		return State_Attack6_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack7:
		return State_Attack7_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack8:
		return State_Attack8_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack9:
		return State_Attack9_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack10:
		return State_Attack10_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Attack11:
		return State_Attack11_Update(_Delta);
	/*case Enum_HollowSoldier_Sword_State::Attack12:
		return State_Attack12_Update(_Delta);*/
	case Enum_HollowSoldier_Sword_State::Attack13:
		return State_Attack13_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Left2:
		return State_Turn_Left2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Right2:
		return State_Turn_Right2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Left_Twice2:
		return State_Turn_Left_Twice2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Right_Twice2:
		return State_Turn_Right_Twice2_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Left1:
		return State_Turn_Left1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Right1:
		return State_Turn_Right1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Left_Twice1:
		return State_Turn_Left_Twice1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Turn_Right_Twice1:
		return State_Turn_Right_Twice1_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Hit_Front:
		return State_Hit_Front_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Hit_Back:
		return State_Hit_Back_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Hit_Left:
		return State_Hit_Left_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Hit_Right:
		return State_Hit_Right_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::BackAttackDeath:
		return State_BackAttackDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::AfterGuardBreakHit:
		return State_AfterGuardBreakHit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::AfterGuardBreakDeath:
		return State_AfterGuardBreakDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Sword::ChangeAttackState()
{
	if (GetTargetDistance_e() == Enum_TargetDist::Melee)
	{
		AttackPattern = ContentsRandom::RandomInt(14, 19);
		//AttackPattern = 1;
	}
	else
	{ 
		AttackPattern = ContentsRandom::RandomInt(1, 16);
		//AttackPattern = 1;
	}
	
	switch (AttackPattern)
	{
	case 1:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack1);
		break;
	case 2:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack2);
		break;
	case 3:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack3);
		break;
	case 4:
		/*ChangeState(Enum_HollowSoldier_Sword_State::Attack4);
		break;*/
	case 5:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack5);
		break;
	case 6:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack6);
		break;
	case 7:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack7);
		break;
	case 8:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack8);
		break;
	case 9:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack9);
		break;
	case 10:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack10);
		break;
	case 11:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack11);
		break;
	case 12:
		/*ChangeState(Enum_HollowSoldier_Sword_State::Attack12);
		break;*/
	case 13:
		ChangeState(Enum_HollowSoldier_Sword_State::Attack13);
		break;
	case 14:
		ChangeState(Enum_HollowSoldier_Sword_State::Walk_Back);
		break;
	case 15:
		ChangeState(Enum_HollowSoldier_Sword_State::Walk_Left);
		break;
	case 16:
		ChangeState(Enum_HollowSoldier_Sword_State::Walk_Right);
		break;
	case 17:
	case 18:
	case 19:
		ChangeState(Enum_HollowSoldier_Sword_State::Walk_Front);
		break;
	default:
		break;
	}

}

void Monster_HollowSoldier_Sword::ChangeHitState()
{
	if (true == Hit.IsHit())
	{
		if (true == IsFlag(Enum_ActorFlag::FrontStab))
		{
			ChangeState(Enum_HollowSoldier_Sword_State::AfterGuardBreakHit);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::BackStab))
		{
			ChangeState(Enum_HollowSoldier_Sword_State::BackAttackHit);
			return;
		}

		if (Stat.GetHp() <= 0)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::HitToDeath);
			return;
		}

		if (true == IsFlag(Enum_ActorFlag::Break_Posture))
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Parrying);
			return;
		}
		
		Enum_DirectionXZ_Quat HitDir = Hit.GetHitDir();
		//BodyCollision->Off();

		switch (HitDir)
		{
		case Enum_DirectionXZ_Quat::F:
			ChangeState(Enum_HollowSoldier_Sword_State::Hit_Front);
			break;
		case Enum_DirectionXZ_Quat::R:
			ChangeState(Enum_HollowSoldier_Sword_State::Hit_Right);
			break;
		case Enum_DirectionXZ_Quat::B:
			ChangeState(Enum_HollowSoldier_Sword_State::Hit_Back);
			break;
		case Enum_DirectionXZ_Quat::L:
			ChangeState(Enum_HollowSoldier_Sword_State::Hit_Left);
			break;
		default:
			ChangeState(Enum_HollowSoldier_Sword_State::Hit_Front);
			break;
		}
	}
	else
	{
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_Sword::State_Idle1_Update(float _Delta)
{
	ChangeHitState();

	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}*/

	//StateTime += _Delta;

	// 트리거 발동시
	/*if (StateTime >= 10.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}*/

}

void Monster_HollowSoldier_Sword::State_Idle2_Start()
{
	//Debug
	{
		AttackPattern++;
	}
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_Sword::State_Idle2_Update(float _Delta)
{
	// 여기서 공격 등등 이루어짐.
	StateTime += _Delta;

	ChangeHitState();

	if (BodyCollision->IsUpdate() == false)
	{
		BodyCollision->On();
	}
	

	if (false)
	{
		StateTime = 0.0f;
		//ChangeState(Enum_HollowSoldier_Sword_State::Attack12);
	}

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle >= 80.0f && AbsTargetAngle <= 150.0f)
	{
		//Turn
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Left2);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Right2);
			return;
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Left_Twice2);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Right_Twice2);
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

	/*if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}*/

	/*if (IsRecognize == true)
	{
		const float fRotDir = BaseActor::GetRotDir_f();
		const float RotAngle = fRotDir * _Delta;
		Capsule->AddWorldRotation(float4(0.0f, RotAngle, 0.0f));
	}*/

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

	if (StateTime >= 0.0f)
	{
		// 거리 구하기
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			//RunToSting
			StateTime = 0.0;
			ChangeState(Enum_HollowSoldier_Sword_State::Run);
			return;
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Medium)
		{
			StateTime = 0.0f;
			ChangeState(Enum_HollowSoldier_Sword_State::Walk_Front);
			return;
		}
		else
		{
			StateTime = 0.0f;
			ChangeAttackState();
			/*if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_HollowSoldier_Sword_State::Walk_Front);
			}
			else
			{
				
			}*/
		}
		
	}

}

void Monster_HollowSoldier_Sword::State_Idle2ToIdle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2ToIdle1");
}
void Monster_HollowSoldier_Sword::State_Idle2ToIdle1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Idle1ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1ToIdle2");
}
void Monster_HollowSoldier_Sword::State_Idle1ToIdle2_Update(float _Delta)
{
	/*if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}*/

	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 29)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Scout_Start()
{
	ScoutTime = 0.0f;
	StateTime = 0.0f;
	MainRenderer->ChangeAnimation("c1100_Scout");
}
void Monster_HollowSoldier_Sword::State_Scout_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}*/


	ChangeHitState();

	ScoutTime += _Delta;

	// 플레이어 인식시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}

	if (ScoutTime >= 15.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Turn_Left_Twice1);
		return;
	}


	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			
		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Player, RecognizeParameter))
	{
		//ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		FindTarget();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1ToIdle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front");
}
void Monster_HollowSoldier_Sword::State_Walk_Front_Update(float _Delta)
{
	ChangeHitState();

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if(MainRenderer->GetCurAnimationFrame() >= 41)
	{
		if (GetTargetDistance_e() == Enum_TargetDist::Long)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Run);
			return;
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
		
	}

	/*EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);*/

	
}

void Monster_HollowSoldier_Sword::State_Walk_Back_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.7f, 2.8f);
	MainRenderer->ChangeAnimation("c1100_Walk_Back");
}
void Monster_HollowSoldier_Sword::State_Walk_Back_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Left_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Left");
}
void Monster_HollowSoldier_Sword::State_Walk_Left_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Right_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.65f, 2.6f);
	MainRenderer->ChangeAnimation("c1100_Walk_Right");
}
void Monster_HollowSoldier_Sword::State_Walk_Right_Update(float _Delta)
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
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Run_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Run");
}
void Monster_HollowSoldier_Sword::State_Run_Update(float _Delta)
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
		if (GetTargetDistance_e() == Enum_TargetDist::Melee)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::RH_RunToSting);
			return;
		}
		else if (GetTargetDistance_e() == Enum_TargetDist::Close)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
		
	}
}

void Monster_HollowSoldier_Sword::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_RH_VerticalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
}
void Monster_HollowSoldier_Sword::State_RH_HorizontalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_ComboAttack");
}
void Monster_HollowSoldier_Sword::State_RH_ComboAttack_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_TwinSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_RH_TwinSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_RH_RunToSting_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_RunToSting");
}
void Monster_HollowSoldier_Sword::State_RH_RunToSting_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35 && MainRenderer->GetCurAnimationFrame() <= 41)
	{
		Sword.On();

		Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
		if (true == Sword.GetBlock())
		{
			ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
			return;
		}
		else
		{
			Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
		}
	}
	
	if (MainRenderer->GetCurAnimationFrame() >= 42)
	{
		Sword.Off();
	}

	if (MainRenderer->GetCurAnimationFrame() >= 159)
	{
		Sword.ResetRecord();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Attack1_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack1_Update(float _Delta)
{
	std::string_view name = MainRenderer->GetCurAnimation()->Aniamtion->GetName();
	std::string name2 = MainRenderer->GetCurAnimation()->FBXAnimationData->AniName;
	int a = 0;

	ChangeHitState();
	
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();
			
			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}
			
		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 100)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack2_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack2_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
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
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 11 && MainRenderer->GetCurAnimationFrame() <= 15)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 16)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack3_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack3_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
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

		if (MainRenderer->GetCurAnimationFrame() >= 11 && MainRenderer->GetCurAnimationFrame() <= 15)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 16)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			Sword.ResetRecord();
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

		if (MainRenderer->GetCurAnimationFrame() >= 25 && MainRenderer->GetCurAnimationFrame() <= 28)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 29)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

//void Monster_HollowSoldier_Sword::State_Attack4_Start()
//{
//	// 부자연스러운 움직임, 빼야되는 State
//	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
//}
//void Monster_HollowSoldier_Sword::State_Attack4_Update(float _Delta)
//{
//	if (CheckAnimationName("c1100_RH_VerticalSlash"))
//	{
//		if (MainRenderer->GetCurAnimationFrame() >= 35)
//		{
//			MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
//		}
//	}
//
//	if (CheckAnimationName("c1100_RH_HorizontalSlash"))
//	{
//		
//		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 2)
//		{
//			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
//			MainRenderer->ChangeCurFrame(3);
//		}
//
//		if (MainRenderer->GetCurAnimationFrame() >= 22)
//		{
//			MainRenderer->ChangeAnimation("c1100_RH_Sting");
//		}
//	}
//
//	if (CheckAnimationName("c1100_RH_Sting"))
//	{
//		
//		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
//		{
//			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
//			//MainRenderer->ChangeCurFrame(5);
//		}
//
//		if (MainRenderer->GetCurAnimationFrame() >= 119)
//		{
//			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
//		}
//	}
//}

void Monster_HollowSoldier_Sword::State_Attack5_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack5_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
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

		if (MainRenderer->GetCurAnimationFrame() >= 11 && MainRenderer->GetCurAnimationFrame() <= 15)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 16)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 22)
		{
			Sword.ResetRecord();
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

		if (MainRenderer->GetCurAnimationFrame() >= 44 && MainRenderer->GetCurAnimationFrame() <= 48)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 49)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 144)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack6_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack6_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
			MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_TwinSlash"))
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

		if (MainRenderer->GetCurAnimationFrame() >= 13 && MainRenderer->GetCurAnimationFrame() <= 16)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 17)
		{
			Sword.Off();
		}

		// 중간에 RecordReset 호출 한번 해야할꺼같은데?
		if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 19)
		{
			Sword.ResetRecord();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 31 && MainRenderer->GetCurAnimationFrame() <= 34)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack7_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack7_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
			MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
		}
	}

	if (CheckAnimationName("c1100_RH_TwinSlash"))
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

		if (MainRenderer->GetCurAnimationFrame() >= 13 && MainRenderer->GetCurAnimationFrame() <= 16)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 17)
		{
			Sword.Off();
		}

		// 중간에 RecordReset 한번 호출 해야할꺼같은데?
		if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 19)
		{
			Sword.ResetRecord();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 31 && MainRenderer->GetCurAnimationFrame() <= 34)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 47)
		{
			Sword.ResetRecord();
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
			MainRenderer->GetCurAnimation()->SetBlendTime(0.5f);
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 25 && MainRenderer->GetCurAnimationFrame() <= 28)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 29)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack8_Start()
{
	// 이 콤보 맞는거야? 못본거같은데
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack8_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 23 && MainRenderer->GetCurAnimationFrame() <= 27)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 28)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.ResetRecord();
			MainRenderer->ChangeAnimation("c1100_Th_VerticalSlash");
		}
	}

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		
		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 9)
		{
			if (false == IsTargetInAngle(3.0f))
			{
				RotToTarget(_Delta);
			}
			MainRenderer->GetCurAnimation()->SetBlendTime(0.4f);
			//MainRenderer->ChangeCurFrame(10);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 25 && MainRenderer->GetCurAnimationFrame() <= 28)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 29)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack9_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack9_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 13 && MainRenderer->GetCurAnimationFrame() <= 16)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 17)
		{
			Sword.Off();
		}

		// 중간에 ResetRecord 해줘야함.
		if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 19)
		{
			Sword.ResetRecord();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 31 && MainRenderer->GetCurAnimationFrame() <= 34)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack10_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack10_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 13 && MainRenderer->GetCurAnimationFrame() <= 16)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 17)
		{
			Sword.Off();
		}

		// 중간에 ResetRecord 해줘야함.
		if (MainRenderer->GetCurAnimationFrame() >= 18 && MainRenderer->GetCurAnimationFrame() <= 19)
		{
			Sword.ResetRecord();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 31 && MainRenderer->GetCurAnimationFrame() <= 34)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 45)
		{
			Sword.ResetRecord();
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
			MainRenderer->GetCurAnimation()->SetBlendTime(0.5f);
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 25 && MainRenderer->GetCurAnimationFrame() <= 28)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 29)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack11_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_Sting");
}
void Monster_HollowSoldier_Sword::State_Attack11_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_RH_Sting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 21 && MainRenderer->GetCurAnimationFrame() <= 26)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 27)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 119)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

//void Monster_HollowSoldier_Sword::State_Attack12_Start()
//{
//	// 애니메이션 바뀌는게 이상함 조정 필요한데 어떻게??
//	// 아무리 해도 손이 몸을 통과함 -> 폐기 예정
//	MainRenderer->ChangeAnimation("c1100_RH_Sting");
//}
//void Monster_HollowSoldier_Sword::State_Attack12_Update(float _Delta)
//{
//	if (CheckAnimationName("c1100_RH_Sting"))
//	{
//		if (MainRenderer->GetCurAnimationFrame() >= 31)
//		{
//			//MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
//			MainRenderer->ChangeAnimation("c1100_Idle2");
//		}
//	}
//
//	if (CheckAnimationName("c1100_Idle2"))
//	{
//		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 4)
//		{
//			MainRenderer->GetCurAnimation()->SetBlendTime(0.8f);
//		}
//
//		if (MainRenderer->GetCurAnimationFrame() >= 4)
//		{
//			MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
//		}
//	}
//
//	if (CheckAnimationName("c1100_TH_VerticalSlash"))
//	{
//		if (MainRenderer->GetCurAnimationFrame() >= 0 && MainRenderer->GetCurAnimationFrame() <= 3)
//		{
//			MainRenderer->GetCurAnimation()->SetBlendTime(0.9f);
//			//MainRenderer->ChangeCurFrame(4);
//		}
//
//		if (MainRenderer->GetCurAnimationFrame() >= 125)
//		{
//			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
//		}
//	}
//}

void Monster_HollowSoldier_Sword::State_Attack13_Start()
{
	MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack13_Update(float _Delta)
{
	ChangeHitState();

	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 25 && MainRenderer->GetCurAnimationFrame() <= 28)
		{
			Sword.On();

			Sword.CollisionToShield(Enum_CollisionOrder::Player_Shield);
			if (true == Sword.GetBlock())
			{
				ChangeState(Enum_HollowSoldier_Sword_State::AttackFail);
				return;
			}
			else
			{
				Sword.CollisionToBody(Enum_CollisionOrder::Player_Body);
			}

		}

		if (MainRenderer->GetCurAnimationFrame() >= 29)
		{
			Sword.Off();
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			Sword.ResetRecord();
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
			return;
		}
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left2");
}
void Monster_HollowSoldier_Sword::State_Turn_Left2_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right2");
}
void Monster_HollowSoldier_Sword::State_Turn_Right2_Update(float _Delta)
{
	ChangeHitState();
	
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice2");
}
void Monster_HollowSoldier_Sword::State_Turn_Left_Twice2_Update(float _Delta)
{
	ChangeHitState();
	
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice2");
}
void Monster_HollowSoldier_Sword::State_Turn_Right_Twice2_Update(float _Delta)
{
	ChangeHitState();
	
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left");
}
void Monster_HollowSoldier_Sword::State_Turn_Left1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right");
}
void Monster_HollowSoldier_Sword::State_Turn_Right1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice");
}
void Monster_HollowSoldier_Sword::State_Turn_Left_Twice1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		//ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice");
}
void Monster_HollowSoldier_Sword::State_Turn_Right_Twice1_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_AttackFail_Start() 
{
	Hit.SetHit(false);
	Sword.Off();
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_AttackFail");

}
void Monster_HollowSoldier_Sword::State_AttackFail_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 40)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Parrying_Start()
{
	Hit.SetHit(false);
	Sword.ResetRecord();
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_Sword::State_Parrying_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 64)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Hit_Front_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Sword::State_Hit_Front_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Hit_Back_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Back");
}
void Monster_HollowSoldier_Sword::State_Hit_Back_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Hit_Left_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_Hit_Left");
}
void Monster_HollowSoldier_Sword::State_Hit_Left_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_Hit_Right_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("C1100_Hit_Right");
}
void Monster_HollowSoldier_Sword::State_Hit_Right_Update(float _Delta)
{
	ChangeHitState();

	if (MainRenderer->GetCurAnimationFrame() >= 46)
	{
		//BodyCollision->On();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_Sword::State_HitToDeath_Update(float _Delta)
{
	// 죽는 애니메이션 재생중 무기 Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::Sword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Death);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_BackAttackHit_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Sword::State_BackAttackHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 80)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::BackAttackDeath);
			return;
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 167)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_BackAttackDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackDeath");
}
void Monster_HollowSoldier_Sword::State_BackAttackDeath_Update(float _Delta)
{
	
}

void Monster_HollowSoldier_Sword::State_AfterGuardBreakHit_Start()
{
	Hit.SetHit(false);
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakHit");
}
void Monster_HollowSoldier_Sword::State_AfterGuardBreakHit_Update(float _Delta)
{
	if (Stat.GetHp() <= 0)
	{
		if (MainRenderer->GetCurAnimationFrame() >= 140)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::AfterGuardBreakDeath);
			return;
		}
	}

	if (MainRenderer->GetCurAnimationFrame() >= 194)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		return;
	}
}

void Monster_HollowSoldier_Sword::State_AfterGuardBreakDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_AfterGuardBreakDeath");
}
void Monster_HollowSoldier_Sword::State_AfterGuardBreakDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");

}
void Monster_HollowSoldier_Sword::State_Death_Update(float _Delta) 
{

}