#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"
#include "WorldMap.h"
#include "ContentsLight.h"
#include "FogEffect.h"

TestLevel_Map::TestLevel_Map()
{

}

TestLevel_Map::~TestLevel_Map()
{

}

void TestLevel_Map::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	{
		std::shared_ptr<WorldMap> Object = CreateActor<WorldMap>(0, "WorldMap");
		
	}

	//{
	//	std::shared_ptr<TestMap> Object = CreateActor<TestMap>(0, "TestMap");
	//}

}

void TestLevel_Map::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);

}

void TestLevel_Map::Start()
{
	GameEngineInput::AddInputObject(this);

	ContentLevel::Start();


	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	std::shared_ptr<GameEngineCoreWindow> CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(1, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		CoreWindow->AddDebugRenderTarget(2, "ForwardTarget", GetMainCamera()->GetCameraForwardTarget());
		CoreWindow->AddDebugRenderTarget(3, "DeferredLightTarget", GetMainCamera()->GetCameraDeferredLightTarget());
		CoreWindow->AddDebugRenderTarget(4, "DeferredTarget", GetMainCamera()->GetCameraDeferredTarget());
		//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	}

	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 시작위치
	GetMainCamera()->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });
	// 
	//GetMainCamera()->Transform.SetLocalPosition({ -13921.0f, 3438.0f, -4173.0f });

	std::shared_ptr< FogEffect> Effect =GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
	Effect->Init(GetMainCamera());

	// 빛
	std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(0);
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.7f,0.7f,0.7f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);

}

void TestLevel_Map::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Map::Release()
{

}