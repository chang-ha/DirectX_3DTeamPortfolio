#include "PreCompile.h"
#include "Monster_Hollow_NonFirstAttack.h"

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

	CheckLanternCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster);
	CheckLanternCollision->SetCollisionType(ColType::SPHERE3D);
	CheckLanternCollision->SetCollisionColor(float4::BLACK);
	CheckLanternCollision->Transform.SetLocalPosition(float4(0, 100, 0));
	CheckLanternCollision->Transform.SetWorldScale(float4(300, 300, 300));

	ChangeState(Enum_Hollow_State::Pray1);
}

void Monster_Hollow_NonFirstAttack::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
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
		case Enum_Hollow_State::Hit:
			State_Hit_Start();
			break;
		case Enum_Hollow_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_Hollow_State::BackAttackHit:
			State_BackAttackHit_Start();
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
	case Enum_Hollow_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_Hollow_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_Hollow_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_Hollow_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_Hollow_NonFirstAttack::ChangeAttackState()
{
	AttackPattern = ContentsRandom::RandomInt(1, 7);
	/*if (IsAttack == true)
	{
		AttackPattern = ContentsRandom::RandomInt(3, 7);
	}*/
	
	switch (AttackPattern)  
	{
	case 1:
		ChangeState(Enum_Hollow_State::Walk_Back);
		break;
	case 2:
		ChangeState(Enum_Hollow_State::Walk_Left);
		break;
	case 3:
		ChangeState(Enum_Hollow_State::Walk_Right);
		break;
	case 4:
		ChangeState(Enum_Hollow_State::RH_VerticalSlash);
		break;
	case 5:
		ChangeState(Enum_Hollow_State::RH_HorizontalSlash);
		break;
	case 6:
		ChangeState(Enum_Hollow_State::TH_VerticalSlash);
		break;
	case 7:
		ChangeState(Enum_Hollow_State::RH_ComboAttack);
		break;
	default:
		break;
	}
}

void Monster_Hollow_NonFirstAttack::CheckAwake()
{
	EventParameter AwakeParameter;
	AwakeParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			_Other->Off();
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
	if (true == RecognizeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, RecognizeParameter))
	{
		FindTarget();
	}
	else
	{
		if (RecognizeCollision->IsUpdate() == true)
		{
			RecognizeCollision->Transform.AddWorldScale(float4(500.0f * _Delta, 500.0f * _Delta, 500.0f * _Delta));
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


	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared1);
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle1);
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
	
	
	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared2);
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle2);
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

	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared3);
	}

	CheckAwake();

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (AwakeValue == true)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle3);
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
	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared2_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared2");
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared3_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared3");
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared3_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
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

	// 랜턴 효과 받았을때
	if (false)
	{
		ChangeState(Enum_Hollow_State::BeScaredToIdle);
	}

	// Test
	StateTime += _Delta;
	if (StateTime >= 3.0f)
	{
		StateTime = 0.0f;
		ChangeState(Enum_Hollow_State::BeScaredToIdle);
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

	// Pray 마다 무기 꺼내는 프레임 다름 수정 필요.
	if (MainRenderer->GetCurAnimationFrame() >= 31)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToIdle2");
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle2_Update(float _Delta)
{
	NonFindTarget(_Delta);

	if (MainRenderer->GetCurAnimationFrame() >= 37)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_PrayToIdle3");
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle3_Update(float _Delta)
{
	NonFindTarget(_Delta);

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_BeScaredToIdle_Start()
{
	MainRenderer->ChangeAnimation("c1100_BeScaredToIdle");
}
void Monster_Hollow_NonFirstAttack::State_BeScaredToIdle_Update(float _Delta)
{
	NonFindTarget(_Delta);

	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Idle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_Hollow_NonFirstAttack::State_Idle_Update(float _Delta)
{
	StateTime += _Delta;

	const float AbsTargetAngle = std::fabs(BaseActor::GetTargetAngle());
	if (AbsTargetAngle >= 90.0f && AbsTargetAngle <= 150.0f)
	{
		//Turn
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_Hollow_State::Turn_Left2);
		}
		else
		{
			ChangeState(Enum_Hollow_State::Turn_Right2);
		}
	}
	else if (AbsTargetAngle > 150.0f)
	{
		// TurnTwice
		if (Enum_RotDir::Left == GetRotDir_e())
		{
			ChangeState(Enum_Hollow_State::Turn_Left_Twice2);
		}
		else
		{
			ChangeState(Enum_Hollow_State::Turn_Right_Twice2);
		}
	}
	else if (AbsTargetAngle < 80.0f)
	{
		if (false == IsTargetInAngle(3.0f))
		{
			RotToTarget(_Delta);
		}
	}

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

	if (StateTime >= 0.1f)
	{
		// 거리 구하기
		if (false)
		{
			//RunToSting
			StateTime = 0.0;
			//ChangeState(Enum_Hollow_State::RH_RunToSting);
		}
		else
		{
			if (IsAttack == false)
			{
				StateTime = 0.0f;
				ChangeState(Enum_Hollow_State::Walk_Front);
			}
			else
			{
				StateTime = 0.0f;
				ChangeAttackState();
				//ChangeState(Enum_Hollow_State::Walk_Front);
			}
		}

	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Front_Start()
{
	MainRenderer->ChangeAnimation("c1100_Walk_Front");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Front_Update(float _Delta)
{
	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	EventParameter AttackParameter;
	AttackParameter.Enter = [&](class GameEngineCollision* _This, class GameEngineCollision* _Other)
		{
			ChangeState(Enum_Hollow_State::Idle);
		};
	AttackRangeCollision->CollisionEvent(Enum_CollisionOrder::Dummy, AttackParameter);
}

void Monster_Hollow_NonFirstAttack::State_Walk_Back_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Walk_Back");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Back_Update(float _Delta)
{
	WalkTime += _Delta;

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Left_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Walk_Left");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Left_Update(float _Delta)
{
	WalkTime += _Delta;

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Walk_Right_Start()
{
	WalkToChangeTime = ContentsRandom::Randomfloat(0.5f, 2.5f);
	MainRenderer->ChangeAnimation("c1100_Walk_Right");
}
void Monster_Hollow_NonFirstAttack::State_Walk_Right_Update(float _Delta)
{
	WalkTime += _Delta;

	if (false == IsTargetInAngle(3.0f))
	{
		RotToTarget(_Delta);
	}

	if (WalkTime >= WalkToChangeTime)
	{
		WalkTime = 0.0f;
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Run_Start()
{
	MainRenderer->ChangeAnimation("c1100_Run");
}
void Monster_Hollow_NonFirstAttack::State_Run_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 61)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 53)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_TH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_TH_VerticalSlash");
}
void Monster_Hollow_NonFirstAttack::State_TH_VerticalSlash_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 73)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_ComboAttack");
}
void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 165)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_RH_RunToSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_RunToSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_RunToSlash_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 82)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Left2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Right2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 35)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Left_Twice2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Left_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Turn_Right_Twice2");
}
void Monster_Hollow_NonFirstAttack::State_Turn_Right_Twice2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 38)
	{
		ChangeState(Enum_Hollow_State::Idle);
	}
}

void Monster_Hollow_NonFirstAttack::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_Hollow_NonFirstAttack::State_AttackFail_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_Hollow_NonFirstAttack::State_Parrying_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_Hit_Start()
{
	// 무기가 없는 상태일때 맞았을때 꺼내야됨
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	MainRenderer->ChangeAnimation("c1100_Hit_Front");

	// 이 전에 있던 State가 Pray 또는 BeScared일때
	// 타게팅은 여기서 이루어짐.
}
void Monster_Hollow_NonFirstAttack::State_Hit_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_HitToDeath_Start()
{
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
	}
}

void Monster_Hollow_NonFirstAttack::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_Hollow_NonFirstAttack::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_Hollow_NonFirstAttack::State_Death_Update(float _Delta)
{

}