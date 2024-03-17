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

	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Monster_LothricKn> LothricKn = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	LothricKn->SetIdleType(Enum_Lothric_IdleType::Sit);
	LothricKn->SetWPosition(float4(100.0f, 0.0f, 0.0f));

	//std::shared_ptr<Monster_LothricKn> LothricKn1 = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn1");
	//LothricKn1->SetIdleType(Enum_Lothric_IdleType::Standing);
	//LothricKn1->SetWPosition(float4(300.0f, 0.0f, 0.0f));


	// std::shared_ptr<Monster_HollowSoldier_Sword> Hollow = CreateActor<Monster_HollowSoldier_Sword>(static_cast<int>(Enum_UpdateOrder::Monster), "Hollow");
	// Hollow->SetWPosition(float4(-400.0f, 0.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 180.0f, 0.0f));
	//Hollow->Transform.SetWorldRotation(float4(0.0f, 90.0f, 0.0f));
	// Hollow->SetStateIdle1();

	/*std::shared_ptr<Monster_Hollow_Unarmed> Unarmed = CreateActor<Monster_Hollow_Unarmed>(static_cast<int>(Enum_UpdateOrder::Monster), "Unarmed");
	Unarmed->SetWPosition(float4(-200.0f, 0.0f, 0.0f));*/
	//std::shared_ptr<Monster_Hollow_Unarmed> UnarmedHollow = CreateActor<Monster_Hollow_Unarmed>(static_cast<int>(Enum_UpdateOrder::Monster), "UnarmedHollow");
	//UnarmedHollow->SetWPosition(float4(-700.0f, 0.0f, 0.0f));

	GetMainCamera()->Transform.SetWorldPosition(float4(0.0f, 0.0f, 0.0f));
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_HollowSoldier_Sword>(Enum_UpdateOrder::Monster);
}