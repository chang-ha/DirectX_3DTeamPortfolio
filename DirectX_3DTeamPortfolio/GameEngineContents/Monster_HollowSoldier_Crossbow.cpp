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
}
void Monster_HollowSoldier_Crossbow::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	
}