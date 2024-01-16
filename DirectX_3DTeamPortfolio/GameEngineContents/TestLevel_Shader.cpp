#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "FXAAEffect.h"
#include <GameEngineCore/BlurPostEffect.h>
#include "ContentsLight.h"
#include "TestObject_Shader.h"

TestLevel_Shader::TestLevel_Shader() 
{
}

TestLevel_Shader::~TestLevel_Shader()
{
}

void TestLevel_Shader::LevelStart(GameEngineLevel* _PrevLevel)
{
}

void TestLevel_Shader::LevelEnd(GameEngineLevel* _NextLevel)
{
}

void TestLevel_Shader::Start()
{
	GameEngineInput::AddInputObject(this);

	ContentLevel::Start();

	// GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, 3000.0f });
	// GetMainCamera()->Transform.AddWorldRotation({ 0.f, 180.f, 0.f });

	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	// Test Ground
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	physx::PxMaterial* mMaterial = GameEnginePhysX::GetDefaultMaterial();
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	//GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	GetMainCamera()->Transform.AddLocalPosition({ 0.0f, 0.0f, -300.0f });

	//CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 0.0f,0.0f,10.0f });
	HollowSoldier->GetMainRenderer()->RenderBaseInfoValue.IsNormal = 0;

	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 100.0f,0.0f,10.0f });

	HollowSoldier = CreateActor<TestObject_Shader>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ -100.0f,0.0f,10.0f });


	Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
	Boss_Object->Transform.SetLocalPosition({ 300.f, 0.f, 0.f });


	{
		Test_Light1 = CreateActor<ContentsLight>(static_cast<int>(Enum_UpdateOrder::Light),"MainLight");
		Test_Light1->SetLightType(Enum_LightType::Point);
		//Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();
		Test_Light1->Transform.SetWorldRotation(float4{ 0.0f,0.0f, 0.0f });

		Data.DifLightPower = 4.0f;
		Data.SpcLightPower = 2.0f;
		Data.SpcPow = 100.0f;
		//Data.AmbientLight = float4(0.4f;

		Test_Light1->SetLightData(Data);
	}
}

void TestLevel_Shader::Update(float _Delta)
{

	float MoveSpeed = 300.0f;
	 
	if (true == GameEngineInput::IsPress('A', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::LEFT * _Delta * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::FORWARD * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::FORWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('S', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::BACKWARD * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::BACKWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('Q', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('E', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
	}


	if (true == GameEngineInput::IsPress('Z', this))
	{
		Test_Light1->Transform.AddLocalRotation(float4::UP * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalRotation(float4::UP * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('C', this))
	{
		Test_Light1->Transform.AddLocalRotation(float4::DOWN * _Delta * MoveSpeed);
		GetMainCamera()->Transform.AddLocalRotation(float4::DOWN * _Delta * MoveSpeed);
	}

}

void TestLevel_Shader::Release()
{
}
