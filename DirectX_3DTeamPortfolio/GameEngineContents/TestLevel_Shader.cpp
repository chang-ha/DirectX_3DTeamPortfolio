#include"PreCompile.h"
#include "TestLevel_Shader.h"
#include "Boss_Vordt.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"

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

	CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	CreateActor<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);
	Boss_Object = CreateActor<Boss_Vordt>(0, "Boss_Vordt");
}

void TestLevel_Shader::Update(float _Delta)
{
}

void TestLevel_Shader::Release()
{
}
