#include "PreCompile.h"
#include "TestLevel_MapObject.h"

//오브젝트 헤더
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
#include "Object_Sword.h"
#include "Object_Table.h"
#include "Object_HumanTree.h"
#include "Object_CandleHuman.h"


//맵 헤더
#include "WorldMap.h"

TestLevel_MapObject::TestLevel_MapObject()
{

}

TestLevel_MapObject::~TestLevel_MapObject()
{

}

void TestLevel_MapObject::LevelStart(GameEngineLevel* _PrevLevel)
{
	ContentLevel::LevelStart(_PrevLevel);

	{
		std::shared_ptr<WorldMap> Object = CreateActor<WorldMap>(1, "WorldMap");
	}
	
	CreateObject();

}

void TestLevel_MapObject::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_MapObject::Start()
{
	ContentLevel::Start();

	

	//Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 0.0f);

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 1, 1 });

	
	/*LightData Data = TestObject0->GetLightData();


	Data.DifLightPower = 0.1f;
	Data.SpcLightPower = 5.0f;
	Data.AmbientLight = float4(0.7f,0.7f,0.7f,1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);*/

	GetMainCamera()->Transform.SetWorldPosition({ 2500.0f, -3000.0f, -9000.0f });
	std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(0);
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.7f, 0.7f, 0.7f, 1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);

}

void TestLevel_MapObject::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
	RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);

	if (true == GameEngineInput::IsDown('1', this))
	{
		GameEngineCamera::FreeSpeed = 50.0f;
	}

	if (true == GameEngineInput::IsDown('2', this))
	{
		GameEngineCamera::FreeSpeed = 1000.0f;
	}
	//RayCast({ 100.0f, }, { 0.0f,0.0f, 5.0f }, 1000.0f);
}

void TestLevel_MapObject::Release()
{

}

void TestLevel_MapObject::CreateObject()
{
	//테스트
	{
		std::shared_ptr<TestMapObjcet> Object = CreateActor<TestMapObjcet>(1);
	}

	//사다리
	{
		std::shared_ptr<Object_Ladder1> Object = CreateActor<Object_Ladder1>(1);
	}
	{
		std::shared_ptr<Object_Ladder2> Object = CreateActor<Object_Ladder2>(1);
	}
	{
		std::shared_ptr<Object_Ladder3> Object = CreateActor<Object_Ladder3>(1);
	}
	{
		std::shared_ptr<Object_Ladder4> Object = CreateActor<Object_Ladder4>(1);
	}
	{
		std::shared_ptr<Object_Ladder5> Object = CreateActor<Object_Ladder5>(1);
	}
	{
		std::shared_ptr<Object_Ladder6> Object = CreateActor<Object_Ladder6>(1);
	}


	{
		std::shared_ptr<Object_BossDoor> Object = CreateActor<Object_BossDoor>(1);
	}
	{
		std::shared_ptr<Object_CastleDoor> Object = CreateActor<Object_CastleDoor>(1);
	}
	{
		std::shared_ptr<Object_Desk> Object = CreateActor<Object_Desk>(1);
	}
	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
	}
	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
	}
	{
		std::shared_ptr<Object_StartDoor> Object = CreateActor<Object_StartDoor>(1);
	}
	{
		std::shared_ptr<Object_Sword> Object = CreateActor<Object_Sword>(1);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
	}

	{
		std::shared_ptr<Object_HumanTree> Object = CreateActor<Object_HumanTree>(1);
	}

	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
	}

	
	//Object_BossDoor
	//Object_CastleDoor
	//Object_Desk
	//Object_Skeleton
	//Object_Skeleton1
	//Object_StartDoor
	//Object_Sword
	//Object_Table
}
