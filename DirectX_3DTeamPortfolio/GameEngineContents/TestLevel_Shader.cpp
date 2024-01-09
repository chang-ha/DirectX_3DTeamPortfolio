#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "FXAAEffect.h"
#include <GameEngineCore/BlurPostEffect.h>
#include "ContentsLight.h"

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

	//GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
	GetMainCamera()->Transform.AddLocalPosition({ 0.0f, 0.0f, -500.0f });

	//CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	HollowSoldier = CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);

	HollowSoldier->Transform.AddLocalPosition({ 0.0f,0.0f,10.0f });
	HollowSoldier = CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ 200.0f,0.0f,10.0f });

	HollowSoldier = CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);
	HollowSoldier->Transform.AddLocalPosition({ -200.0f,0.0f,10.0f });


	{
		Test_Light1 = CreateActor<ContentsLight>(0);
		Test_Light1->SetLightType(Enum_LightType::Point);
		Test_Light1->IsDebugValue = true;
		LightData Data = Test_Light1->GetLightData();

		Data.DifLightPower = 1.0f;
		Data.SpcPow = 50.0f;
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
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::RIGHT * _Delta * MoveSpeed);
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::FORWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('S', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::BACKWARD * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('Q', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::UP * _Delta * MoveSpeed);
	}
	if (true == GameEngineInput::IsPress('E', this))
	{
		Test_Light1->Transform.AddLocalPosition(float4::DOWN * _Delta * MoveSpeed);
	}

}

void TestLevel_Shader::Release()
{
}
