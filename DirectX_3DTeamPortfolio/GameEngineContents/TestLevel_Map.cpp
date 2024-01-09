#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"
#include <GameEngineCore/GameEngineLight.h>

TestLevel_Map::TestLevel_Map()
{

}

TestLevel_Map::~TestLevel_Map()
{

}

void TestLevel_Map::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		std::shared_ptr<TestMap> Object = CreateActor<TestMap>(0, "TestMap");
	}
}

void TestLevel_Map::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_Map::Start()
{
	GameEngineInput::AddInputObject(this);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	// 빛
	std::shared_ptr<GameEngineLight> TestObject0 = CreateActor<GameEngineLight>(0);
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.7f,0.7f,0.7f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);

}

void TestLevel_Map::Update(float _Delta)
{
	
}

void TestLevel_Map::Release()
{

}