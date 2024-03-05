#include "PreCompile.h"
#include "TestLevel_Boss.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "TestObject.h"

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
	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->Transform.SetWorldPosition({ -1000.f, -2450.f, 3000.f });
		Boss_Object->Transform.SetWorldRotation({0.f, -30.f, 0.f});
	}

	// Light
	if (nullptr == Test_Light)
	{
		Test_Light = CreateActor<ContentsLight>(0);
		Test_Light->CreateShadowMap();
		LightData Data = Test_Light->GetLightData();

		Data.DifLightPower = 0.1f;
		Data.AmbientLight = float4(0.7f, 0.7f, 0.7f, 1.0f);
		Data.SpcPow = 200.0f;

		Test_Light->SetLightData(Data);
	}

	// Building
	if (nullptr == TestObj)
	{
		// TestObj = CreateActor<TestObject>(0, "TestObj");
		// TestObj->Transform.SetLocalPosition({ 0.0f, 0.0f, -2000.0f });
	}

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	
	{
		TestPlayer = CreateActor<Player>(0, "Player");
		// TestPlayer->Transform.SetWorldPosition({-250.f, 0.f, 500.f});
		TestPlayer->Transform.SetWorldPosition({ -2800.f, -2000.f, 6700.f });
		TestPlayer->Transform.SetWorldRotation({ 0.f, 165.f, 0.f });
		TestPlayer->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(TestPlayer.get());
	}

	{
		std::shared_ptr<WorldMap> Object = CreateActor<WorldMap>(0, "WorldMap");
	}

	GetMainCamera()->Transform.SetLocalPosition({ -2800.f, -2000.f, 6700.f });
	GetMainCamera()->Transform.SetLocalRotation({0.f, 0.f, 0.f});
}

void TestLevel_Boss::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Boss_Object)
	{
		Boss_Object->Death();
		Boss_Object = nullptr;
	}

	if (nullptr != TestObj)
	{
		TestObj->Death();
		TestObj = nullptr;
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
	// physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	// physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	// physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	// Scene->addActor(*groundPlane);
}

void TestLevel_Boss::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);

	if (true == GameEngineInput::IsPress('D', this))
	{
		GetMainCamera()->Transform.AddWorldRotation({0.f, 30.f * _Delta, 0.f});
	}
}

void TestLevel_Boss::Release()
{

}