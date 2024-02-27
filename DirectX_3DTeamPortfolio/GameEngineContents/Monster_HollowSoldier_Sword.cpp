#include "PreCompile.h"
#include "Monster_HollowSoldier_Sword.h"

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

	AddBoneIndex(Enum_BoneType::B_01_RightHand, 44);
	CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_BoneType::B_01_RightHand, "B_01_RightHand");
	
	

	ChangeState(Enum_HollowSoldier_Sword_State::Idle1);

	
}
void Monster_HollowSoldier_Sword::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);

	
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
		case Enum_HollowSoldier_Sword_State::Hit:
			State_Hit_Start();
			break;
		case Enum_HollowSoldier_Sword_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Sword_State::BackAttackHit:
			State_BackAttackHit_Start();
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
	case Enum_HollowSoldier_Sword_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Sword::ChangeAttackState()
{
	AttackPattern = ContentsRandom::RandomInt(1, 16);
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
	default:
		break;
	}

}

void Monster_HollowSoldier_Sword::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_Sword::State_Idle1_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}*/

	StateTime += _Delta;

	// 트리거 발동시
	if (StateTime >= 10.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}

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
	

	if (false)
	{
		StateTime = 0.0f;
		//ChangeState(Enum_HollowSoldier_Sword_State::Attack12);
	}

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle >= 90.0f && AbsTargetAngle <= 150.0f)
	{
		//Turn
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Left2);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Right2);
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Left_Twice2);
		}
		else
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Turn_Right_Twice2);
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

	EventParameter AttackParameter;
	AttackParameter.Stay = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			IsAttack = true;
		};
	AttackParameter.Exit = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			IsAttack = false;
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);

	if (StateTime >= 2.0f)
	{
		// 거리 구하기
		if(false)
		{
			//RunToSting
			StateTime = 0.0;
			ChangeState(Enum_HollowSoldier_Sword_State::RH_RunToSting);
		}
		else
		{
			if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_HollowSoldier_Sword_State::Walk_Front);
			}
			else
			{
				StateTime = 0.0f;
				ChangeAttackState();
			}
		}
		
	}

}

void Monster_HollowSoldier_Sword::State_Idle2ToIdle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2ToIdle1");
}
void Monster_HollowSoldier_Sword::State_Idle2ToIdle1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
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

	if (MainRenderer->GetCurAnimationFrame() >= 29)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Scout");
	StateTime = 0.0f;
}
void Monster_HollowSoldier_Sword::State_Scout_Update(float _Delta)
{
	/*StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}*/




	// 플레이어 인식시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}


	EventParameter RecognizeParameter;
	RecognizeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			
		};
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, RecognizeParameter))
	{
		//ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		FindTarget();
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1ToIdle2);
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front");
}
void Monster_HollowSoldier_Sword::State_Walk_Front_Update(float _Delta)
{
	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);
}

void Monster_HollowSoldier_Sword::State_Walk_Back_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Back");
}
void Monster_HollowSoldier_Sword::State_Walk_Back_Update(float _Delta)
{
	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 43)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Left_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Left");
}
void Monster_HollowSoldier_Sword::State_Walk_Left_Update(float _Delta)
{
	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Walk_Right_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Right");
}
void Monster_HollowSoldier_Sword::State_Walk_Right_Update(float _Delta)
{
	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Run_Start()
{
	MainRenderer->ChangeAnimation("c1100_Run");
}
void Monster_HollowSoldier_Sword::State_Run_Update(float _Delta)
{

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
	if (MainRenderer->GetCurAnimationFrame() >= 159)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
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
	
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 100)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack2_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack2_Update(float _Delta)
{
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
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack3_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack3_Update(float _Delta)
{
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

		if (MainRenderer->GetCurAnimationFrame() >= 107)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
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

		if (MainRenderer->GetCurAnimationFrame() >= 144)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack6_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack6_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
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

		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack7_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_HollowSoldier_Sword::State_Attack7_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
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

		if (MainRenderer->GetCurAnimationFrame() >= 47)
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
			MainRenderer->GetCurAnimation()->SetBlendTime(0.5f);
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
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
	if (CheckAnimationName("c1100_RH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 35)
		{
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

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack9_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack9_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 113)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack10_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_HollowSoldier_Sword::State_Attack10_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_TwinSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 45)
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
			MainRenderer->GetCurAnimation()->SetBlendTime(0.5f);
			//MainRenderer->ChangeCurFrame(5);
		}

		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Attack11_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_Sting");
}
void Monster_HollowSoldier_Sword::State_Attack11_Update(float _Delta)
{
	if (CheckAnimationName("c1100_RH_Sting"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 119)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
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
	if (CheckAnimationName("c1100_TH_VerticalSlash"))
	{
		if (MainRenderer->GetCurAnimationFrame() >= 125)
		{
			ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
		}
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left2");
}
void Monster_HollowSoldier_Sword::State_Turn_Left2_Update(float _Delta)
{
	
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right2");
}
void Monster_HollowSoldier_Sword::State_Turn_Right2_Update(float _Delta)
{
	
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice2");
}
void Monster_HollowSoldier_Sword::State_Turn_Left_Twice2_Update(float _Delta)
{
	
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice2");
}
void Monster_HollowSoldier_Sword::State_Turn_Right_Twice2_Update(float _Delta)
{
	
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left");
}
void Monster_HollowSoldier_Sword::State_Turn_Left1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right");
}
void Monster_HollowSoldier_Sword::State_Turn_Right1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Left_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice");
}
void Monster_HollowSoldier_Sword::State_Turn_Left_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
	}
}

void Monster_HollowSoldier_Sword::State_Turn_Right_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice");
}
void Monster_HollowSoldier_Sword::State_Turn_Right_Twice1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
	}
}

void Monster_HollowSoldier_Sword::State_AttackFail_Start() 
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");

}
void Monster_HollowSoldier_Sword::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_Sword::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Sword::State_Hit_Update(float _Delta)
{

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
	}
}

void Monster_HollowSoldier_Sword::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Sword::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");

}
void Monster_HollowSoldier_Sword::State_Death_Update(float _Delta) 
{

}