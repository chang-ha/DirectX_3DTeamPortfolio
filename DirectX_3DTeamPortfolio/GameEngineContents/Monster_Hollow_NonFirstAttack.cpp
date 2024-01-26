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
	MainRenderer->ChangeAnimation("c1100_PrayToIdle3");
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
		case Enum_Hollow_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_Hollow_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_Hollow_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_Hollow_State::RH_TwinSlash:
			State_RH_TwinSlash_Start();
			break;
		case Enum_Hollow_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_Hollow_State::Hit:
			State_Hit_Start();
			break;
		case Enum_Hollow_State::HitToDeath:
			State_HitToDeath_Start();
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
	case Enum_Hollow_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_Hollow_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_Hollow_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_Hollow_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_Hollow_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_Hollow_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_Hollow_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_Hollow_State::Death:
		return State_Death_Update(_Delta);
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
	//	ChangeState(Enum_Hollow_State::PrayToBeScared1);
	//}


	// �÷��̾� �浹��
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared1);
	}

	// �Ƹ�... ���ϵ�� �ִ� ���Ϳ� ���ؼ�
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToIdle1);
	}
}

void Monster_Hollow_NonFirstAttack::State_Pray2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Pray2");
}
void Monster_Hollow_NonFirstAttack::State_Pray2_Update(float _Delta)
{
	
	
	// �÷��̾� �浹��
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared2);
	}

	// �Ƹ�... ���ϵ�� �ִ� ���Ϳ� ���ؼ�
	if (false)
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

	// �÷��̾� �浹��
	if (false)
	{
		ChangeState(Enum_Hollow_State::PrayToBeScared3);
	}

	// �Ƹ�... ���ϵ�� �ִ� ���Ϳ� ���ؼ�
	if (false)
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

	// ���� ȿ�� �޾�����
	if (false)
	{
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
	//	// �̰� �ִϸ��̼� �߰��� ����. �ִϸ��̼� ��ü�� �׷��� �Ǿ�����.
	//	// �ذ��� �ʿ�.
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
	// Pray ���� ���� ������ ������ �ٸ� ���� �ʿ�.
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

}

void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_VerticalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_VerticalSlash_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_HorizontalSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_HorizontalSlash_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_ComboAttack");
}
void Monster_Hollow_NonFirstAttack::State_RH_ComboAttack_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_RH_TwinSlash_Start()
{
	MainRenderer->ChangeAnimation("c1100_RH_TwinSlash");
}
void Monster_Hollow_NonFirstAttack::State_RH_TwinSlash_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_AttackFail_Start()
{
	//MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_Hollow_NonFirstAttack::State_AttackFail_Update(float _Delta)
{

}

void Monster_Hollow_NonFirstAttack::State_Hit_Start()
{
	// ���Ⱑ ���� �����϶� �¾����� �����ߵ�
	MeshOn(Enum_Hollow_MeshIndex::BrokenSword);
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
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
	// �״� �ִϸ��̼� ����� ���� Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::BrokenSword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_Hollow_State::Death);
	}
}

void Monster_Hollow_NonFirstAttack::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_Hollow_NonFirstAttack::State_Death_Update(float _Delta)
{

}