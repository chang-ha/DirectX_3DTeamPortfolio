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
		float scale = 2.f;
		Data.AmbientLight = float4(scale, scale, scale, 1.0f);
		Data.SpcPow = 200.0f;
		Data.LightPower = 500.f;

		Test_Light->SetLightData(Data);
	}

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	
	{
		TestPlayer = CreateActor<Player>(0, "Player");
		TestPlayer->Transform.SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		TestPlayer->Transform.SetWorldRotation({ 0.f, 165.f, 0.f });
		TestPlayer->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(TestPlayer.get());
	}

	{
		std::shared_ptr<WorldMap> Object = CreateActor<WorldMap>(0, "WorldMap");
	}

	GetMainCamera()->Transform.SetLocalPosition({ -2800.f, -2500.f, 6700.f });
	GetMainCamera()->Transform.SetLocalRotation({0.f, 165.f, 0.f});
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
}

void TestLevel_Boss::Release()
{

}