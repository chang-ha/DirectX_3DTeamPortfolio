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

}