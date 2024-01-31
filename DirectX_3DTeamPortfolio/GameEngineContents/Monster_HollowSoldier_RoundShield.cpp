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
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Helmat);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
}
void Monster_HollowSoldier_RoundShield::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_HollowSoldier_RoundShield::ChangeState(Enum_HollowSoldier_RoundShield_State _State)
{

}
void Monster_HollowSoldier_RoundShield::StateUpdate(float _Delta)
{

}