#include "PreCompile.h"
#include "TestLevel_Monster.h"

#include "Monster_LothricKn.h"

TestLevel_Monster::TestLevel_Monster() 
{
}

TestLevel_Monster::~TestLevel_Monster() 
{
}

void TestLevel_Monster::Start()
{

}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
}