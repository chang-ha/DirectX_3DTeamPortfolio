#include "PreCompile.h"
#include "Monster_HollowSoldier_RoundShield.h"

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
		case Enum_HollowSoldier_RoundShield_State::Scout:
			State_Scout_Start();
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
		case Enum_HollowSoldier_RoundShield_State::Hit:
			State_Hit_Start();
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
	case Enum_HollowSoldier_RoundShield_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::RH_TwinSlash:
		return State_RH_TwinSlash_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Guard:
		return State_Guard_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::GuardBreak:
		return State_GuardBreak_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_RoundShield_State::Hit:
		return State_Hit_Update(_Delta);
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

void Monster_HollowSoldier_RoundShield::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_RoundShield::State_Idle1_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle2");
}
void Monster_HollowSoldier_RoundShield::State_Idle2_Update(float _Delat)
{

}

void Monster_HollowSoldier_RoundShield::State_Idle3_Start()
{
	// GuardOn
	MainRenderer->ChangeAnimation("c1100_Idle3");
}
void Monster_HollowSoldier_RoundShield::State_Idle3_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Scout");
}
void Monster_HollowSoldier_RoundShield::State_Scout_Update(float _Delta)
{

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

void Monster_HollowSoldier_RoundShield::State_Guard_Start()
{
	MainRenderer->ChangeAnimation("c1100_Guard");
}
void Monster_HollowSoldier_RoundShield::State_Guard_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_GuardBreak_Start()
{
	MainRenderer->ChangeAnimation("c1100_GuardBreak");
}
void Monster_HollowSoldier_RoundShield::State_GuardBreak_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_HollowSoldier_RoundShield::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_RoundShield::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_RoundShield::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_RoundShield::State_Hit_Update(float _Delta)
{

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