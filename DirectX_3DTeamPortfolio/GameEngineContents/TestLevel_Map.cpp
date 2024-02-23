#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"
#include "WorldMap.h"
#include "ContentsLight.h"
#include <GameEngineCore\FogEffect.h>
#include "FXAAEffect.h"

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
		//CoreWindow->AddDebugRenderTarget(5, "LightTarget", Test_Light1->GetShadowTarget());
		//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	}



	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 시작위치
	GetMainCamera()->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });
	// 
	//GetMainCamera()->Transform.SetLocalPosition({ -13921.0f, 3438.0f, -4173.0f });

	// 포그 관련
	std::shared_ptr< FogEffect> Effect =GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
	Effect->Init(GetMainCamera());
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FXAAEffect>();
	//{
	//	std::shared_ptr<GameEngineActor> Object = CreateActor<GameEngineActor>(0);
	//	std::shared_ptr<GameEngineRenderer> NewRenderer = Object->CreateComponent<GameEngineRenderer>();
	//	NewRenderer->SetMesh("Box");
	//	NewRenderer->SetMaterial("FBX_Static_Color");
	//	// NewRenderer->GetShaderResHelper().SetTexture("NormalTexture", "BumpNormal.gif");
	//	NewRenderer->Transform.SetLocalPosition({ 0.0f, -4000.0f, 0.0f });
	//	NewRenderer->Transform.SetLocalScale({ 3000.0f, 100.0f, 3000.0f });
	//	NewRenderer->RenderBaseInfoValue.BaseColor = float4(0.1f, 0.1f, 0.1f, 1.0f);
	//}



	// 빛
	std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "main");
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.05f,0.05f,0.05f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);
	TestObject0->IsDebugValue = true;
	TestObject0->CreateShadowMap(/*float4(4096, 4096)*/);
	//TestObject0->SetShadowRange(float4(4096, 4096));
	TestObject0->SetShadowRange(float4{ 16384,16384 });
	TestObject0->Transform.SetLocalPosition({ -3400.0f, 10101.0f, -5331.0f });
	TestObject0->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });

}

void TestLevel_Map::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);


	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
	}
}

void TestLevel_Map::Release()
{

}