#include "PreCompile.h"
#include "TestLevel_ObjectTest.h"

#include "Object_Ladder1.h"
#include "Object_Ladder2.h"
#include "Object_Ladder3.h"
#include "Object_Ladder4.h"
#include "Object_Ladder5.h"
#include "Object_Ladder6.h"
#include "TestMapObjcet.h"
#include "ContentsLight.h"
#include "Object_BossDoor.h"
#include "Object_CastleDoor .h"
#include "Object_Desk.h"
#include "Object_Skeleton.h"
#include "Object_Skeleton1.h"
#include "Object_StartDoor.h"
#include "Object_bonfire.h"
#include "Object_Table.h"
//#include "Object_HumanTree.h"
#include "Object_CandleHuman.h"
#include "Object_Torchlight.h"
#include "Player.h"

TestLevel_ObjectTest::TestLevel_ObjectTest() 
{
}

TestLevel_ObjectTest::~TestLevel_ObjectTest() 
{
}

void TestLevel_ObjectTest::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);
	//Å×½ºÆ®
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		GetMainCamera()->Transform.SetWorldPosition({ Object->Transform.GetWorldPosition() });
	}
}
void TestLevel_ObjectTest::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_ObjectTest::Start()
{
	ContentLevel::Start();
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 1, 1 });
	GetMainCamera()->Transform.SetWorldPosition({ 2500.0f, -3000.0f, -9000.0f });
	std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(0);
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.7f, 0.7f, 0.7f, 1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);
}
void TestLevel_ObjectTest::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}
void TestLevel_ObjectTest::Release()
{

}