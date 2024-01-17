#include "PreCompile.h"
#include "TestLevel_Monster.h"

#include "Monster_LothricKn.h"
#include "Monster_Hollow_Unarmed.h"


TestLevel_Monster::TestLevel_Monster() 
{
	GameEngineInput::AddInputObject(this);
}

TestLevel_Monster::~TestLevel_Monster() 
{
}

void TestLevel_Monster::Start()
{
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);
}

void TestLevel_Monster::Update(float _Delta)
{

}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	std::shared_ptr<Monster_LothricKn> LothricKn = CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	LothricKn->Transform.SetWorldPosition(float4(100.0f, 0.0f, 0.0f));

	std::shared_ptr<Monster_Hollow_Unarmed> Hollow = CreateActor<Monster_Hollow_Unarmed>(static_cast<int>(Enum_UpdateOrder::Monster), "Hollow");
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_Hollow_Unarmed>(Enum_UpdateOrder::Monster);
}