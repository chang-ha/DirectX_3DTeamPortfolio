#include "PreCompile.h"
#include "Monster_HollowSoldier_Lantern.h"

Monster_HollowSoldier_Lantern::Monster_HollowSoldier_Lantern()
{
}

Monster_HollowSoldier_Lantern::~Monster_HollowSoldier_Lantern()
{
}

void Monster_HollowSoldier_Lantern::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::InnerHood);	
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Lantern);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::BrokenSword);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shirt1);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Belt1);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LongSkirt1);

	ChangeState(Enum_HollowSoldier_Lantern_State::Idle);
}
void Monster_HollowSoldier_Lantern::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_Lantern::ChangeState(Enum_HollowSoldier_Lantern_State _State)
{
	if (_State != LanternState)
	{
		switch (_State)
		{
		case Enum_HollowSoldier_Lantern_State::Idle:
			State_Idle_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::LanternIdle:
			State_LanternIdle_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Scout:
			State_Scout_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AwakeHollows:
			State_AwakeHollows_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_VerticalSlash:
			State_RH_VerticalSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_HorizontalSlash:
			State_RH_HorizontalSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_ComboAttack:
			State_RH_ComboAttack_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::RH_RunToSlash:
			State_RH_RunToSlash_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::AttackFail:
			State_AttackFail_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Parrying:
			State_Parrying_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Hit:
			State_Hit_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::HitToDeath:
			State_HitToDeath_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::BackAttackHit:
			State_BackAttackHit_Start();
			break;
		case Enum_HollowSoldier_Lantern_State::Death:
			State_Death_Start();
			break;
		default:
			break;
		}
	}
}
void Monster_HollowSoldier_Lantern::StateUpdate(float _Delta)
{
	switch (LanternState)
	{
	case Enum_HollowSoldier_Lantern_State::Idle:
		return State_Idle_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::LanternIdle:
		return State_LanternIdle_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Scout:
		return State_Scout_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AwakeHollows:
		return State_AwakeHollows_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_VerticalSlash:
		return State_RH_VerticalSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_HorizontalSlash:
		return State_RH_HorizontalSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_ComboAttack:
		return State_RH_ComboAttack_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::RH_RunToSlash:
		return State_RH_RunToSlash_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::AttackFail:
		return State_AttackFail_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Parrying:
		return State_Parrying_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Hit:
		return State_Hit_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::HitToDeath:
		return State_HitToDeath_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::BackAttackHit:
		return State_BackAttackHit_Update(_Delta);
	case Enum_HollowSoldier_Lantern_State::Death:
		return State_Death_Update(_Delta);
	default:
		break;
	}
}

void Monster_HollowSoldier_Lantern::State_Idle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Idle1");
}
void Monster_HollowSoldier_Lantern::State_Idle_Update(float _Delta)
{
	// 트리거 발동시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Scout);
	}
}

void Monster_HollowSoldier_Lantern::State_LanternIdle_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Idle");
}
void Monster_HollowSoldier_Lantern::State_LanternIdle_Update(float _Delta)
{
	// 여기서부터는 공격
}

void Monster_HollowSoldier_Lantern::State_Scout_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_Scout");
}
void Monster_HollowSoldier_Lantern::State_Scout_Update(float _Delta)
{
	// 플레이어 인식시
	if (false)
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::AwakeHollows);
	}
}

void Monster_HollowSoldier_Lantern::State_AwakeHollows_Start()
{
	MainRenderer->ChangeAnimation("c1100_Lantern_AwakeHollows");
}
void Monster_HollowSoldier_Lantern::State_AwakeHollows_Update(float _Delta)
{
	// 어떤 프레임에서 비선공 몬스터들 Idle로 변경

	// 프레임 조금 더 연구할것.
	// 어디서 무기를 뽑는지
	// 이 애니메이션이 끝나면 확실하게 Idle 상태로 가는지.

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::LanternIdle);
	}
}

void Monster_HollowSoldier_Lantern::State_RH_VerticalSlash_Start()
{

}
void Monster_HollowSoldier_Lantern::State_RH_VerticalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_RH_HorizontalSlash_Start()
{

}
void Monster_HollowSoldier_Lantern::State_RH_HorizontalSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_RH_ComboAttack_Start()
{

}
void Monster_HollowSoldier_Lantern::State_RH_ComboAttack_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_RH_RunToSlash_Start()
{

}
void Monster_HollowSoldier_Lantern::State_RH_RunToSlash_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_AttackFail_Start()
{
	MainRenderer->ChangeAnimation("c1100_AttackFail");
}
void Monster_HollowSoldier_Lantern::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Parrying_Start()
{
	MainRenderer->ChangeAnimation("c1100_Parrying");
}
void Monster_HollowSoldier_Lantern::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Hit_Start()
{
	MainRenderer->ChangeAnimation("c1100_Hit_Front");
}
void Monster_HollowSoldier_Lantern::State_Hit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_HitToDeath_Start()
{
	MainRenderer->ChangeAnimation("c1100_HitToDeath");
}
void Monster_HollowSoldier_Lantern::State_HitToDeath_Update(float _Delta)
{
	if (MainRenderer->GetCurAnimationFrame() >= 58)
	{
		//MeshOff(Enum_Hollow_MeshIndex::Sword);
	}

	if (MainRenderer->GetCurAnimationFrame() >= static_cast<int>(MainRenderer->GetCurAnimation()->End))
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Death);
	}
}

void Monster_HollowSoldier_Lantern::State_BackAttackHit_Start()
{
	MainRenderer->ChangeAnimation("c1100_BackAttackHit");
}
void Monster_HollowSoldier_Lantern::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Death_Start()
{
	MainRenderer->ChangeAnimation("c1100_Death");
}
void Monster_HollowSoldier_Lantern::State_Death_Update(float _Delta)
{

}