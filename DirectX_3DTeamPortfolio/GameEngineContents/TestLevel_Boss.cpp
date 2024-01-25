#include "PreCompile.h"
#include "TestLevel_Boss.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "TestObject.h"

// Test code
#include "Player.h"

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
		Boss_Object->Transform.SetWorldPosition({ 0.f, 0.f, 3000.f });
		Boss_Object->Transform.SetWorldRotation({0.f, 180.f, 0.f});
	}

	// Light
	if (nullptr == Test_Light)
	{
		Test_Light = CreateActor<ContentsLight>(0);
		Test_Light->SetLightType(Enum_LightType::Directional);
		Test_Light->IsDebugValue = true;
		LightData Data = Test_Light->GetLightData();

		Data.DifLightPower = 5.0f;
		Data.SpcPow = 50.0f;
		Data.AmbientLight = float4(0.4f);

		Test_Light->SetLightData(Data);
	}

	// Building
	if (nullptr == TestObj)
	{
		// TestObj = CreateActor<TestObject>(0, "TestObj");
		// TestObj->Transform.SetLocalPosition({ 0.0f, 0.0f, -2000.0f });
	}

	//{
	//	std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
	//	Object->Transform.SetWorldPosition({0.f, 0.f, 500.f});
	//	Boss_Object->SetTargeting(Object.get());
	//}

	GetMainCamera()->Transform.SetLocalPosition({0.f, 500.f, 0.f});
	GetMainCamera()->Transform.SetLocalRotation({10.f, 0.f, 0.f});
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
}

void TestLevel_Boss::Start()
{
	ContentLevel::Start();

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);
}

void TestLevel_Boss::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Boss::Release()
{

}