#include "PreCompile.h"
#include "TestLevel_MapObject.h"
#include "Player.h"
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
#include "Object_bonfire.h"
#include "Object_Table.h"
#include "Object_HumanTree.h"
#include "Object_CandleHuman.h"
#include "Object_Torchlight.h"


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
		std::shared_ptr<Player> Object = CreateActor<Player>(0, "Player");
		Object->Transform.SetWorldPosition({ -9160, 2313, -4327 });
	

		std::shared_ptr<TestMapObjcet> Object2 = CreateActor<TestMapObjcet>(0, "Player");
		Object2->Transform.SetWorldPosition({ -9160, 2313, -4327 });

		//-8880, 2030, -4427
	}
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
	/*std::shared_ptr<ContentsLight> TestObject0 = CreateActor<ContentsLight>(0);
	LightData Data = TestObject0->GetLightData();

	Data.DifLightPower = 3.0f;
	Data.AmbientLight = float4(0.7f, 0.7f, 0.7f, 1.0f);
	Data.SpcPow = 200.0f;

	TestObject0->SetLightData(Data);*/

	std::shared_ptr<ContentsLight> Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "mainDirect");
	LightData Data = Light->GetLightData();
	Light->CreateShadowMap();

	//Data.DifLightPower = 0.1f;
	Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
	Data.LightColor = float4(1.0f, 1.0f, 0.7f);
	Data.LightPower = 2.5f;
	Data.ForceLightPower = 0.25f;

	Light->Transform.SetLocalPosition({ -3400.0f, 10101.0f, -5331.0f });
	Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


	Light->SetLightData(Data);


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
	//화톳불

	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -1125, -2489 , 3232 });
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -16547, 3372 , 2144 });
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
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
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
	}

	{
		std::shared_ptr<Object_HumanTree> Object = CreateActor<Object_HumanTree>(1);
	}

	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
	}

	//횃불
	//1
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -7286, -550 , 14098 });
		Object->Transform.SetWorldRotation({ 0, 0, 0 });
	}
	//2
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6465, -550 , 14515 });
		Object->Transform.SetWorldRotation({ 0, 0, 0 });
	}
	//3
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6035, -437 , 9824 });
		Object->Transform.SetWorldRotation({ 0, -90, 0 });
	}
	//4
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6889, -350 , 9890 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
	}
	//5
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15436, 2548 , 2582 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
	}
	//6
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15265, 2548 , 2249 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
	}
	//7
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -12890, -1940 , 2970 });
		Object->Transform.SetWorldRotation({ 0, -25, 0 });
	}
	//8
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6050, 193 , 6861 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
	}
	//9
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -5760, 193 , 7011 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
	}
	//10
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15440, 2683 , -4280 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
	}
	//11
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15790, 2683 , -4225 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
	}
	//12
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15960, 2683 , -4239 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
	}
	//13
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16320, 2683 , -4208 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
	}
	//14
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16720, 3110 , 230 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
	}
	//15
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16280, 3110 , 285 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
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
