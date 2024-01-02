#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"

TestLevel_Map::TestLevel_Map()
{

}

TestLevel_Map::~TestLevel_Map()
{

}

void TestLevel_Map::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestLevel_Map::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_Map::Start()
{
	GameEngineInput::AddInputObject(this);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	//GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	{
		std::shared_ptr<TestMap> Object = CreateActor<TestMap>(0, "TestMap");
	}
}

void TestLevel_Map::Update(float _Delta)
{
	
}

void TestLevel_Map::Release()
{

}