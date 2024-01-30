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

}
void Monster_HollowSoldier_Lantern::StateUpdate(float _Delta)
{

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

}
void Monster_HollowSoldier_Lantern::State_AttackFail_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Parrying_Start()
{

}
void Monster_HollowSoldier_Lantern::State_Parrying_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Hit_Start()
{

}
void Monster_HollowSoldier_Lantern::State_Hit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_HitToDeath_Start()
{

}
void Monster_HollowSoldier_Lantern::State_HitToDeath_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_BackAttackHit_Start()
{

}
void Monster_HollowSoldier_Lantern::State_BackAttackHit_Update(float _Delta)
{

}

void Monster_HollowSoldier_Lantern::State_Death_Start()
{

}
void Monster_HollowSoldier_Lantern::State_Death_Update(float _Delta)
{

}