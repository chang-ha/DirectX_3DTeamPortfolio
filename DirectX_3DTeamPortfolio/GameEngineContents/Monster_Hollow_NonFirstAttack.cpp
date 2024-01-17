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
		//return State_Pray1_Update(float _Delta);
		return;
	case Enum_Hollow_State::Pray2:
		//return State_Pray2_Update(float _Delta);
		return;
	case Enum_Hollow_State::Pray3:
		//return State_Pray3_Update(float _Delta);
		return;
	case Enum_Hollow_State::PrayToBeScared:
		return State_PrayToBeScared_Update(_Delta);
	case Enum_Hollow_State::BeScared:
		return State_BeScared_Update(_Delta);
	default:
		break;
	}
}



void Monster_Hollow_NonFirstAttack::State_Pray1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray1");
}

void Monster_Hollow_NonFirstAttack::State_Pray2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray2");
}

void Monster_Hollow_NonFirstAttack::State_Pray3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray3");
}

void Monster_Hollow_NonFirstAttack::State_PrayToBeScared_Start()
{
	//MainRenderer->ChangeAnimation("c1100_Pray3");
	MainRenderer->ChangeAnimation("c1100_PrayToBeScared1");
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