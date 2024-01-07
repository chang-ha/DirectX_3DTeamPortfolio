#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "FXAAEffect.h"
#include <GameEngineCore/BlurPostEffect.h>
#include <GameEngineCore/GameEngineLight.h>

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

	GetMainCamera()->GetCameraAllRenderTarget()->CreateEffect<FXAAEffect>();
	//GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -1000.0f });
	//GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	//CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	HollowSoldier = CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);

	HollowSoldier->Transform.AddLocalPosition({ 0.0f,0.0f,10.0f });
	//Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");

	{
		std::shared_ptr<GameEngineLight> TestObject0 = CreateActor<GameEngineLight>(0);
		LightData Data = TestObject0->GetLightData();

		Data.DifLightPower = 0.1f;
		Data.SpcPow = 200.0f;

		TestObject0->SetLightData(Data);
	}
}

void TestLevel_Shader::Update(float _Delta)
{
}

void TestLevel_Shader::Release()
{
}
