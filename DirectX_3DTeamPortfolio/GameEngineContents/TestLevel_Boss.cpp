#include "PreCompile.h"
#include "TestLevel_Boss.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"

// Test code
#include "Player.h"
#include "WorldMap.h"

TestLevel_Boss::TestLevel_Boss()
{

}

TestLevel_Boss::~TestLevel_Boss()
{

}

void TestLevel_Boss::LevelStart(GameEngineLevel* _PrevLevel)
{
	GameEngineCore::SetLimitFrame(31);

	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->Transform.SetWorldPosition({ -1100.f, -2500.f, 3000.f });
		// Boss_Object->Transform.SetWorldPosition({ 0.f, 0.f, 0.f});
		Boss_Object->Transform.SetWorldRotation({0.f, 180.f, 0.f});
		Boss_Object->AI_Start();
	}

	// Light
	if (nullptr == Test_Light1)
	{
		Test_Light1 = CreateActor<ContentsLight>(0);
		// Test_Light->CreateShadowMap();
		LightData Data = Test_Light1->GetLightData();

		Data.DifLightPower = 0.1f;
		float scale = 2.f;
		Data.AmbientLight = float4(scale, scale, scale, 1.0f);
		Data.SpcPow = 200.0f;
		Data.LightPower = 500.f;

		Test_Light1->SetLightData(Data);
	}

	Test_Light1->Transform.SetWorldPosition({ 0.f, 10000.f, 0.f });

	//if (nullptr == Test_Light)
	//{
	//	Test_Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "mainDirect");
	//	LightData Data = Test_Light->GetLightData();
	//	Test_Light->CreateShadowMap();

	//	Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
	//	Data.LightColor = float4(1.0f, 1.0f, 0.7f);
	//	Data.LightPower = 2.0f;
	//	Data.ForceLightPower = 0.25f;

	//	Test_Light->Transform.SetLocalPosition({ -12000.0f, 16200.0f, -4260.0f });
	//	Test_Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


	//	Test_Light->SetLightData(Data);
	//	//Light->IsDebugValue = true;
	//}

	// GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });
	
	if (nullptr == TestPlayer)
	{
		TestPlayer = CreateActor<Player>(0, "Player");
		TestPlayer->SetWorldPosition({ 0.f, 0.f, -2000.f });
		// TestPlayer->SetWorldPosition({ -9910.0f, 2328.0f, -2894.0f });
		TestPlayer->SetWorldRotation({ 0.f, 0.f, 0.f });
		TestPlayer->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(TestPlayer.get());
	}

	//if (nullptr == MapObject)
	//{
	//	MapObject = CreateActor<WorldMap>(0, "WorldMap");
	//}

	GetMainCamera()->Transform.SetLocalPosition({ 0.f, 0.f, 3000.f});
	GetMainCamera()->Transform.SetLocalRotation({0.f, 180.f, 0.f});

	//if (nullptr == Boss_Object)
	//{
	//	Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
	//	Boss_Object->SetWorldPosition({ -1000.f, -2450.f, 3000.f });
	//	Boss_Object->SetWorldRotation({ 0.f, -30.f, 0.f });
	//}

	//// Light
	//if (nullptr == Test_Light)
	//{
	//	Test_Light = CreateActor<ContentsLight>(0);
	//	// Test_Light->CreateShadowMap();
	//	LightData Data = Test_Light->GetLightData();

	//	Data.DifLightPower = 0.1f;
	//	float scale = 2.f;
	//	Data.AmbientLight = float4(scale, scale, scale, 1.0f);
	//	Data.SpcPow = 200.0f;
	//	Data.LightPower = 500.f;

	//	Test_Light->SetLightData(Data);
	//}

	//GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 1, 1, 1, 1 });

	//if (nullptr == TestPlayer)
	//{
	//	TestPlayer = CreateActor<Player>(0, "Player");
	//	TestPlayer->Transform.SetWorldPosition({ -2800.f, -2450.f, 6700.f });
	//	TestPlayer->Transform.SetWorldRotation({ 0.f, 165.f, 0.f });
	//	TestPlayer->SetTargeting(Boss_Object.get());
	//	Boss_Object->SetTargeting(TestPlayer.get());
	//}

	//if (nullptr == MapObject)
	//{
	//	MapObject = CreateActor<WorldMap>(0, "WorldMap");
	//}

	//GetMainCamera()->Transform.SetLocalPosition({ -2800.f, -2500.f, 6700.f });
	//GetMainCamera()->Transform.SetLocalRotation({ 0.f, 165.f, 0.f });
	IsDebug = true;
}

void TestLevel_Boss::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Boss_Object)
	{
		Boss_Object->Death();
		Boss_Object = nullptr;
	}

	if (nullptr != MapObject)
	{
		MapObject->Death();
		MapObject = nullptr;
	}

	if (nullptr != Test_Light1)
	{
		Test_Light1->Death();
		Test_Light1 = nullptr;
	}

	if (nullptr != TestPlayer)
	{
		TestPlayer->Death();
		TestPlayer = nullptr;
	}
}

void TestLevel_Boss::Start()
{
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->lockWrite();
	Scene->addActor(*groundPlane);
	Scene->unlockWrite();
}

void TestLevel_Boss::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TestLevel_Boss::Release()
{

}