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
	ContentLevel::Start();
	Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
	Boss_Object->Transform.SetLocalPosition({0.0f, 3.0f, -100.0f});
}

void TestLevel_Boss::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TestLevel_Boss::Release()
{

}