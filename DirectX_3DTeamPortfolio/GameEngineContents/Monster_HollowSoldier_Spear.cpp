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
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Helmat);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::RightKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::SmallLeatherVest);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
}
void Monster_HollowSoldier_Spear::Update(float _Delta)
{

}