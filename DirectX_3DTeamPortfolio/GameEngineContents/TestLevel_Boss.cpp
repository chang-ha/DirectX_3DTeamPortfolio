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
	//Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
	Scene = GameEnginePhysX::CreateLevelScene();

	//{
	//	std::shared_ptr<GameEngineLight> Object = CreateActor<GameEngineLight>(0);
	//}

}

void TestLevel_Boss::Update(float _Delta)
{
	Scene->simulate(1.0f / 60.0f);
	Scene->fetchResults(true);
}

void TestLevel_Boss::Release()
{

}