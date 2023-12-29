#include "PreCompile.h"
#include "TestLevel_Boss.h"
#include "Boss_Vordt.h"

TestLevel_Boss::TestLevel_Boss()
{

}

TestLevel_Boss::~TestLevel_Boss()
{

}

void TestLevel_Boss::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestLevel_Boss::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_Boss::Start()
{
	Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
}

void TestLevel_Boss::Update(float _Delta)
{

}

void TestLevel_Boss::Release()
{

}