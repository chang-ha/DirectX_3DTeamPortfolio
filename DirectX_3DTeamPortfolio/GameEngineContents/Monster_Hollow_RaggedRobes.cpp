#include "PreCompile.h"
#include "Monster_Hollow_RaggedRobes.h"

Monster_Hollow_RaggedRobes::Monster_Hollow_RaggedRobes()
{
}

Monster_Hollow_RaggedRobes::~Monster_Hollow_RaggedRobes()
{
}

void Monster_Hollow_RaggedRobes::Start()
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shirt2);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Belt3);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ShortSkirt);
}
void Monster_Hollow_RaggedRobes::Update(float _Delta)
{

}