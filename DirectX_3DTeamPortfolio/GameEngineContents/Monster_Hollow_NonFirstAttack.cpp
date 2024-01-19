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
	ChangeState(Enum_Hollow_State::PrayToBeScared);
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
		case Enum_Hollow_State::PrayToBeScared:
			State_PrayToBeScared_Start();
			break;
		case Enum_Hollow_State::BeScared:
			State_BeScared_Start();
			break;
		case Enum_Hollow_State::PrayToIdle:
			State_PrayToIdle_Start();
			break;
		case Enum_Hollow_State::Idle:
			State_Idle_Start();
			break;
		case Enum_Hollow_State::Hit:
			State_Hit_Start();
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
	case Enum_Hollow_State::PrayToBeScared:
		return State_PrayToBeScared_Update(_Delta);
	case Enum_Hollow_State::BeScared:
		return State_BeScared_Update(_Delta);
	case Enum_Hollow_State::PrayToIdle:
		return State_PrayToIdle_Update(_Delta);
	case Enum_Hollow_State::Idle:
		return State_Idle_Update(_Delta);
	case Enum_Hollow_State::Hit:
		return;
	default:
		break;
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
	//	ChangeState(Enum_Hollow_State::PrayToIdle);
	//}


	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared);
	}

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle);
	}
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
		ChangeState(Enum_Hollow_State::PrayToBeScared);
	}

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle);
	}
}

void Monster_Hollow_NonFirstAttack::State_Pray3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray3");
}
void Monster_Hollow_NonFirstAttack::State_Pray3_Update(float _Delta)
{
	// 플레이어 충돌시
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared);
	}

	// 아마... 랜턴들고 있는 몬스터에 의해서
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle);
	}
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared_Start()
{
	if (PrevState == Enum_Hollow_State::Pray1)
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
	}
}
void Monster_Hollow_NonFirstAttack::State_PrayToBeScared_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End) - 1)
	{
		ChangeState(Enum_Hollow_State::BeScared);
	}
}

void Monster_Hollow_NonFirstAttack::State_BeScared_Start()
{
	MainRenderer->ChangeAnimation("c1100_BeScared");
}
void Monster_Hollow_NonFirstAttack::State_BeScared_Update(float _Delta)
{
	
}

void Monster_Hollow_NonFirstAttack::State_PrayToIdle_Start()
{
	if (PrevState == Enum_Hollow_State::Pray1)
	{
		MainRenderer->ChangeAnimation("c1100_PrayToIdle1");
	}
	else if (PrevState == Enum_Hollow_State::Pray2)
	{
		MainRenderer->ChangeAnimation("c1100_PrayToIdle2");
	}
	else if (PrevState == Enum_Hollow_State::Pray3)
	{
		// 이거 애니메이션 중간에 끊김. 애니메이션 자체가 그렇게 되어있음.
		// 해결방법 필요.
		MainRenderer->ChangeAnimation("c1100_PrayToIdle3");
	}
	else
	{
		MainRenderer->ChangeAnimation("c1100_PrayToIdle1");
	}
}
void Monster_Hollow_NonFirstAttack::State_PrayToIdle_Update(float _Delta)
{
	// Pray 마다 무기 꺼내는 프레임 다름 수정 필요.
	/*if (MainRenderer->GetCurAnimationFrame() >= 31)
	{
		MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	}*/

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

}

void Monster_Hollow_NonFirstAttack::State_Hit_Start()
{
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::BrokenSword);
	// MainRenderer->ChangeAnimation("");
}