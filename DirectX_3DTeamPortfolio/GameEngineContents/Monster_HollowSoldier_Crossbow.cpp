#include "PreCompile.h"
#include "Monster_HollowSoldier_Crossbow.h"

Monster_HollowSoldier_Crossbow::Monster_HollowSoldier_Crossbow()
{
}

Monster_HollowSoldier_Crossbow::~Monster_HollowSoldier_Crossbow()
{
}

void Monster_HollowSoldier_Crossbow::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Crossbow);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ChainMail);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Helmat);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);

	CreateMonsterUI(0);
}
void Monster_HollowSoldier_Crossbow::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_Crossbow::ChangeState(Enum_HollowSoldier_Crossbow_State _State)
{
	if (_State != CrossbowState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Crossbow_State::Idle:
			State_Idle_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Fire:
			State_Fire_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Sit_Fire:
			State_Sit_Fire_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Hit:
			State_Hit_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Crossbow_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	CrossbowState = _State;
}
void Monster_HollowSoldier_Crossbow::StateUpdate(float _Delta)
{
	switch (CrossbowState)
	{
	case Enum_HollowSoldier_Crossbow_State::Idle:
		return State_Idle_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Fire:
		return State_FIre_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Sit_Fire:
		return State_Sit_Fire_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Crossbow_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Crossbow::State_Idle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle");
}
void Monster_HollowSoldier_Crossbow::State_Idle_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_Crossbow::State_Idle2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Scout");
}
void Monster_HollowSoldier_Crossbow::State_Scout_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_Fire_Start()
{
	// MainRenderer->ChangeAnimation("c1100_Crossbow_Fire");
}
void Monster_HollowSoldier_Crossbow::State_FIre_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_Sit_Fire_Start()
{
	//MainRenderer->ChangeAnimation("c1100_Crossbow_Sit_Fire");
}
void Monster_HollowSoldier_Crossbow::State_Sit_Fire_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Crossbow::State_Hit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Crossbow::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_Crossbow::State_HitToDeath_Update(float _Delta)
{
	// 죽는 애니메이션 재생중 무기 Off
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		MeshOff(Enum_Hollow_MeshIndex::Crossbow);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Crossbow_State::Death);
	}
}

void Monster_HollowSoldier_Crossbow::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_Crossbow::State_Death_Update(float _Delta)
{

}