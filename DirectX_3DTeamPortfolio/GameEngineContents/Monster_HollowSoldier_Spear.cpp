#include "PreCompile.h"
#include "Monster_HollowSoldier_Spear.h"

Monster_HollowSoldier_Spear::Monster_HollowSoldier_Spear()
{
}

Monster_HollowSoldier_Spear::~Monster_HollowSoldier_Spear()
{
}

void Monster_HollowSoldier_Spear::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Spear);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::WoodShield);
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
void Monster_HollowSoldier_Spear::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_Spear::ChangeState(Enum_HollowSoldier_Spear_State _State)
{
	if (_State != SpearState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Spear_State::Idle1:
			State_Idle1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle2:
			State_Idle2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Idle3:
			State_Idle3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack1:
			State_Attack1_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack2:
			State_Attack2_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack3:
			State_Attack3_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack4:
			State_Attack4_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Attack5:
			State_Attack5_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Guard:
			State_Guard_Start();
			break;
		case Enum_HollowSoldier_Spear_State::GuardBreak:
			State_GuardBreak_Start();
			break;
		case Enum_HollowSoldier_Spear_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Hit:
			State_Hit_Start();
			break;
		case Enum_HollowSoldier_Spear_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Spear_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Spear_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
	SpearState = _State;
}
void Monster_HollowSoldier_Spear::StateUpdate(float _Delta)
{
	switch (SpearState)
	{
	case Enum_HollowSoldier_Spear_State::Idle1:
		return State_Idle1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle2:
		return State_Idle2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Idle3:
		return State_Idle3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack1:
		return State_Attack1_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack2:
		return State_Attack2_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack3:
		return State_Attack3_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack4:
		return State_Attack4_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Attack5:
		return State_Attack5_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Guard:
		return State_Guard_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::GuardBreak:
		return State_GuardBreak_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Spear_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Spear::ChangeAttackState()
{
	AttackPattern = ContentsRandom::RandomInt(1, 5);
	switch (AttackPattern)
	{
	case 1:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack1);
		break;
	case 2:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack2);
		break;
	case 3:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack3);
		break;
	case 4:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack4);
		break;
	case 5:
		ChangeState(Enum_HollowSoldier_Spear_State::Attack5);
		break;
	default:
		break;
	}
}

void Monster_HollowSoldier_Spear::State_Idle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle1");
}
void Monster_HollowSoldier_Spear::State_Idle1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Idle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2");
}
void Monster_HollowSoldier_Spear::State_Idle2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Idle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle3");
}
void Monster_HollowSoldier_Spear::State_Idle3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Idle2ToIdle1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2ToIdle1");
}
void Monster_HollowSoldier_Spear::State_Idle2ToIdle1_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 39)
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}
}

void Monster_HollowSoldier_Spear::State_Idle1ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle1ToIdle2");
}
void Monster_HollowSoldier_Spear::State_Idle1ToIdle2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 29)
	ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
}

void Monster_HollowSoldier_Spear::State_Idle2ToIdle3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle2ToIdle3");
}
void Monster_HollowSoldier_Spear::State_Idle2ToIdle3_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 19)
	ChangeState(Enum_HollowSoldier_Spear_State::Idle3);
}

void Monster_HollowSoldier_Spear::State_Idle3ToIdle2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Idle3ToIdle2");
}
void Monster_HollowSoldier_Spear::State_Idle3ToIdle2_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 31)
	ChangeState(Enum_HollowSoldier_Spear_State::Idle2);
}

void Monster_HollowSoldier_Spear::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Scout");
}
void Monster_HollowSoldier_Spear::State_Scout_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk_Start() 
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Front2");
}
void Monster_HollowSoldier_Spear::State_Walk_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Walk3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Walk_Front3");
}
void Monster_HollowSoldier_Spear::State_Walk3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Run_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Run2");
}
void Monster_HollowSoldier_Spear::State_Run_Update(float _Delta)
{
	
}

void Monster_HollowSoldier_Spear::State_Run3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Run3");
}
void Monster_HollowSoldier_Spear::State_Run3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Attack1_Start()
{
	// Pike1
}
void Monster_HollowSoldier_Spear::State_Attack1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Attack2_Start()
{
	// Pike1 - Pike2
}
void Monster_HollowSoldier_Spear::State_Attack2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Attack3_Start()
{
	// Pike1 - Swing	// 어울리지 않는 콤보, 다시 확인해볼것.
}
void Monster_HollowSoldier_Spear::State_Attack3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Attack4_Start()
{
	// RunToPike
}
void Monster_HollowSoldier_Spear::State_Attack4_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Attack5_Start()
{
	// Swing
}
void Monster_HollowSoldier_Spear::State_Attack5_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left2");
}
void Monster_HollowSoldier_Spear::State_Turn_Left2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right2");
}
void Monster_HollowSoldier_Spear::State_Turn_Right2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice2");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice2_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice2");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice2_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left1");
}
void Monster_HollowSoldier_Spear::State_Turn_Left1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right1");
}
void Monster_HollowSoldier_Spear::State_Turn_Right1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice1");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice1_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice1");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice1_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left3");
}
void Monster_HollowSoldier_Spear::State_Turn_Left3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right3");
}
void Monster_HollowSoldier_Spear::State_Turn_Right3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Left_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Left_Twice3");
}
void Monster_HollowSoldier_Spear::State_Turn_Left_Twice3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Turn_Right_Twice3_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Turn_Right_Twice3");
}
void Monster_HollowSoldier_Spear::State_Turn_Right_Twice3_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Guard_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Guard");
}
void Monster_HollowSoldier_Spear::State_Guard_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_GuardBreak_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_GuardBreak");
}
void Monster_HollowSoldier_Spear::State_GuardBreak_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_AttackFail");
}
void Monster_HollowSoldier_Spear::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Parrying");
}
void Monster_HollowSoldier_Spear::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Spear_Hit_Front");
}
void Monster_HollowSoldier_Spear::State_Hit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HtiToDeath");
}
void Monster_HollowSoldier_Spear::State_HitToDeath_Update(float _Delta)
{
	
}

void Monster_HollowSoldier_Spear::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Spear::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Spear::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_Spear::State_Death_Update(float _Delta)
{

}