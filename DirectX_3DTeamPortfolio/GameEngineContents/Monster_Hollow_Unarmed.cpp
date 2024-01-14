#include "PreCompile.h"
#include "Monster_Hollow_Unarmed.h"

Monster_Hollow_Unarmed::Monster_Hollow_Unarmed()
{
}

Monster_Hollow_Unarmed::~Monster_Hollow_Unarmed()
{
}

void Monster_Hollow_Unarmed::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
}

void Monster_Hollow_Unarmed::Update(float _Delta)
{

}