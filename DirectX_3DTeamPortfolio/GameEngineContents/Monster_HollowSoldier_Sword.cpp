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
		case Enum_HollowSoldier_Sword_State::Scout:
			State_Scout_Start();
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
		case Enum_HollowSoldier_Sword_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Sword_State::HitToDeath:
			State_HitToDeath_Start();
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
	case Enum_HollowSoldier_Sword_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Sword_State::Death:
		return State_Death_Update(_Delta);
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

	// 트리거 발동시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}
}

void Monster_HollowSoldier_Sword::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_Sword::State_Idle2_Update(float _Delta)
{
	// 여기서 공격 등등 이루어짐.
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

void Monster_HollowSoldier_Sword::State_AttackFail_Start() 
{
	// MainRenderer->ChangeAnimation("c1100_AttackFail");

	// 애니메이션 여러개라 보류
}
void Monster_HollowSoldier_Sword::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Sword::State_HitToDeath_Start()
{
	//MainRenderer->ChangeAnimation("c1100_HitToDeath");

	// 애니메이션 여러개라 보류
}
void Monster_HollowSoldier_Sword::State_HitToDeath_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Death);
	}
}

void Monster_HollowSoldier_Sword::State_Death_Start()
{
	//MainRenderer->ChangeAnimation("c1100_Death");

	// HitToDeath 와 연관이 있어서 보류
}
void Monster_HollowSoldier_Sword::State_Death_Update(float _Delta) 
{

}