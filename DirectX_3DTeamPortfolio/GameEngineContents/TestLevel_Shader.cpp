#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "FXAAEffect.h"
#include <GameEngineCore/BlurPostEffect.h>

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

	//CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	HollowSoldier = CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);

	HollowSoldier->Transform.AddLocalPosition({ -300.0f,0.0f,10.0f });
	//Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
}

void TestLevel_Shader::Update(float _Delta)
{
}

void TestLevel_Shader::Release()
{
}
