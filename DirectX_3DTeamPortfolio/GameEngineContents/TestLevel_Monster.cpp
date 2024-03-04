#include "PreCompile.h"
#include "TestLevel_Monster.h"

#include <GameEngineCore/GameEngineGUI.h>

#include "ContentsLight.h"

#include "Monster_LothricKn.h"
#include "Monster_HollowSoldier_RoundShield.h"
#include "Monster_HollowSoldier_Sword.h"
#include "Monster_HollowSoldier_Spear.h"
#include "Monster_HollowSoldier_Lantern.h"
#include "Monster_Hollow_Unarmed.h"
#include "Monster_Hollow_RaggedRobes.h"

TestLevel_Monster::TestLevel_Monster() 
{
	GameEngineInput::AddInputObject(this);
}

TestLevel_Monster::~TestLevel_Monster() 
{
}

void TestLevel_Monster::Start()
{
	ContentLevel::Start();

	// Light
	{
		std::shared_ptr<ContentsLight> Test_Light1 = CreateActor<ContentsLight>(0);

		Test_Light1->SetLightType(Enum_LightType::Directional);
		Test_Light1->CreateShadowMap();
		Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();

		Data.DifLightPower = 3.0f;
		Data.SpcPow = 50.0f;
		Data.AmbientLight = float4(0.4f);
		Data.LightPower = 5.0f;

		Test_Light1->SetLightData(Data);
	}

	// Physx Plane
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	// CameraSetting
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);
	GetMainCamera()->Transform.SetLocalPosition({0.0f, 0.0f, -200.0f});
}

void TestLevel_Monster::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	static bool TriggerOn =false;
	static float TriggerTime = 0.0f;
	if (true == GameEngineInput::IsDown('H', this))
	{
		GameEngineSound::Sound3DPlay("c128008001.wav", float4::ZERO);
		GameEngineSound::Sound3DPlay("c128008001.wav", float4::ZERO);
		TriggerOn = true;
	}

	if (TriggerOn)
	{
		TriggerTime += _Delta;
		if (TriggerTime > 0.2f)
		{
			GameEngineSound::Sound3DPlay("c128008500b.wav", float4::ZERO);
			GameEngineSound::Sound3DPlay("c128008500b.wav", float4::ZERO);
			GameEngineCore::MainWindow.WindowLoopOff();
		}
	}

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Monster_LothricKn> LothricKn = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	LothricKn->SetWPosition(float4(100.0f, 0.0f, 0.0f));

	std::shared_ptr<Monster_LothricKn> LothricKn2 = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn2");
	LothricKn2->SetWPosition(float4(300.0f, 0.0f, 0.0f));

	std::shared_ptr<Monster_HollowSoldier_Lantern> Hollow = CreateActor<Monster_HollowSoldier_Lantern>(static_cast<int>(Enum_UpdateOrder::Monster), "Hollow");
	Hollow->SetWPosition(float4(-500.0f, 0.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 180.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 90.0f, 0.0f));
	Hollow->SetStateStay();

	GetMainCamera()->Transform.SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_HollowSoldier_Lantern>(Enum_UpdateOrder::Monster);
}