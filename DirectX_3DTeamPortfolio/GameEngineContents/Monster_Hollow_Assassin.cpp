#include "PreCompile.h"
#include "Monster_Hollow_Assassin.h"

Monster_Hollow_Assassin::Monster_Hollow_Assassin()
{
}

Monster_Hollow_Assassin::~Monster_Hollow_Assassin()
{
}

void Monster_Hollow_Assassin::Start() 
{
	Monster_Hollow::Start();

	MeshOnOffSwitch(Enum_Hollow_MeshIndex::ShoulderRobe);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::LeftKneePads);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Shoes);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Dagger);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::OuterHood);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::Pants);
	MeshOnOffSwitch(Enum_Hollow_MeshIndex::TopRobe);
	//MeshOnOffSwitch(Enum_Hollow_MeshIndex::Scarf);
}
void Monster_Hollow_Assassin::Update(float _Delta)
{
	Monster_Hollow::Update(_Delta);
	StateUpdate(_Delta);
}

void Monster_Hollow_Assassin::ChangeState(Enum_Hollow_Assassin_State _State)
{

}
void Monster_Hollow_Assassin::StateUpdate(float _Delta)
{

}