﻿#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"
#include "WorldMap.h"
#include "ContentsLight.h"
#include <GameEngineCore\FogEffect.h>
#include "FXAAEffect.h"
#include "TestMapObjcet.h"
#include "Object_BossDoor.h"


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
		std::shared_ptr<WorldMap> Object = CreateActor<WorldMap>(1, "WorldMap");
		
	}


	{
		std::shared_ptr<TestMapObjcet> Object = CreateActor<TestMapObjcet>(0, "TestMapObjcet");
	}

	//GetMainCamera()->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });
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
	//GetMainCamera()->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });
	GetMainCamera()->Transform.SetWorldPosition({ 2500.0f, -3000.0f, -9000.0f });
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

	if (true == GameEngineInput::IsDown('1',this))
	{
		GameEngineCamera::FreeSpeed = 50.0f;
	}
	
	if (true == GameEngineInput::IsDown('2', this))
	{
		GameEngineCamera::FreeSpeed = 1000.0f;
	}
}

void TestLevel_Map::Release()
{

}