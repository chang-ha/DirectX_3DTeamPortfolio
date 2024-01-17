#include "PreCompile.h"
#include "Monster_HollowSoldier.h"

Monster_HollowSoldier::Monster_HollowSoldier()
{
}

Monster_HollowSoldier::~Monster_HollowSoldier()
{
}

void Monster_HollowSoldier::Start()
{
	Monster_Hollow::Start();
	
	// HollowSoldier?

	// HollowCitizen?

	// Hollow
}
void Monster_HollowSoldier::Update(float _Delta)
{

}

void Monster_HollowSoldier::Release()
{
	//Monster_Hollow::Release();
}

void Monster_HollowSoldier::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}
