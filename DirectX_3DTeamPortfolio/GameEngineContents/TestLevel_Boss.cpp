#include "PreCompile.h"
#include "TestLevel_Boss.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"

TestLevel_Boss::TestLevel_Boss()
{

}

TestLevel_Boss::~TestLevel_Boss()
{

}

void TestLevel_Boss::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestLevel_Boss::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_Boss::Start()
{
	ContentLevel::Start();

	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
	Boss_Object->Transform.SetLocalPosition({0.0f, 0.0f, 0.0f});

	{
		std::shared_ptr<ContentsLight> Test_Light1 = CreateActor<ContentsLight>(0);
		Test_Light1->SetLightType(Enum_LightType::Point);
		Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();

		Data.DifLightPower = 1.0f;
		Data.SpcPow = 50.0f;
		//Data.AmbientLight = float4(0.4f;

		Test_Light1->SetLightData(Data);
	}
}

void TestLevel_Boss::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Boss::Release()
{

}