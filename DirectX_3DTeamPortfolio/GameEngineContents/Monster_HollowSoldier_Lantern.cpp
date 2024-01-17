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
}
void Monster_HollowSoldier_Lantern::Update(float _Delta)
{

}