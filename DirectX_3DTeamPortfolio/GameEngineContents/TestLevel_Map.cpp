#include "PreCompile.h"
#include "TestLevel_Map.h"
#include "TestMap.h"
#include "WorldMap.h"
#include "ContentsLight.h"
#include <GameEngineCore\FogEffect.h>
#include "FXAAEffect.h"
#include "Monster_LothricKn.h"


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



	// 몬스터 셋팅
	SetAllMonster();



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
		//CoreWindow->AddDebugRenderTarget(5, "LightTarget", Test_Light1->GetShadowTarget());
		//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	}



	//float4 HalfWindowScale = GameEngineCore::MainWindow.GetScale().Half();

	// 시작위치
	GetMainCamera()->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });


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
	TestObject0->CreateShadowMap();
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.05f,0.05f,0.05f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);
	TestObject0->IsDebugValue = true;
	TestObject0->CreateShadowMap(/*float4(4096, 4096)*/);
	//TestObject0->SetShadowRange(float4(4096, 4096));
	TestObject0->Transform.SetLocalPosition({ -3400.0f, 10101.0f, -5331.0f });
	TestObject0->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });

}

void TestLevel_Map::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);

	float4 Pos = GetMainCamera()->Transform.GetWorldPosition();


	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
	}
}

void TestLevel_Map::Release()
{

}


void TestLevel_Map::SetAllMonster()
{
	// 18마리이상부터 문제가있는듯.
	// 18마리 아래에서도 터지거나 안터지거나 미지수 일수도있음.
	for (size_t i = 0; i < 18; i++)
	{
		{
			std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
			Monster->SetWorldPosition({ -2738.0f, 4120.0f, -1457.0f });
		}
	}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -2738.0f, 4120.0f, -1457.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -3874.0f, 4118.0f, -1151.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -5730.0f, 3409.0f, -2575.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -6764.0f, 3400.0f, -3607.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -8496.0f, 2878.0f, -4483.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -9050.0f, 2033.0f, -4071.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -10210.0f, 2030.0f, -3207.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -11265.0f, 2891.0f, -4376.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -13050.0f, 2886.0f, -3783.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -14467.0f, 2893.0f, -4080.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -15491.0f, 2943.0f, -4392.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -14397.0f, 2277.0f, -2812.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -16297.0f, 2689.0f, -1427.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -15816.0f, 2683.0f, -472.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -17594.0f, 2834.0f, 1350.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -15476.0f, 2327.0f, 2870.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -11968.0f, 1924.0f, 3882.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -10196.0f, 984.0f, 4174.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -8623.0f, 907.0f, 3707.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -8546.0f, -683.0f, 3904.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -9154.0f, 542.0f, 5211.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -7885.0f, -538.0f, 5512.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -8476.0f, -548.0f, 7715.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -2738.0f, 4435.0f, -1457.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -6396.0f, -624.0f, 8055.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -6433.0f, -750.0f, 10232.0f });
	//	AllMonster.push_back(Monster);
	//}

	//{
	//	std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
	//	Monster->SetResponPos({ -4026.0f, -1788.0f, 9562.0f });
	//	AllMonster.push_back(Monster);
	//}


	AllMonsterOn();
}

void TestLevel_Map::AllMonsterOn()
{

	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->On();
	}
}

void TestLevel_Map::AllMonsterOff()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->Off();
	}
}