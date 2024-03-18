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
#include "Object_HumanTree1.h"
#include "Object_HumanTree2.h"
#include "Object_HumanTree3.h"
#include "Object_HumanTree4.h"
#include "Object_HumanTree5.h"
#include "Object_CandleHuman.h"
#include "Object_Torchlight.h"
#include "Object_CandleHuman2.h"


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



	
	
	

	//std::shared_ptr<TestMapObjcet> Object2 = CreateActor<TestMapObjcet>(0, "Player");
	//Object2->Transform.SetWorldPosition({ -9160, 2313, -4327 });
	//Object2->Transform.SetWorldPosition({ -16476, 2440, -3785 });
	//-8033, -564, 3313
	//-8880, 2030, -4427
	//-16476.019531 Y : 2440.824463 Z : -3785.442383
	
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

	//GetMainCamera()->Transform.SetWorldPosition({ 2500.0f, -3000.0f, -9000.0f });
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
	Data.LightPower = 0.7f;
	Data.ForceLightPower = 8.0f;

	Light->Transform.SetLocalPosition({ -3400.0f, 10101.0f, -5331.0f });
	Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


	Light->SetLightData(Data);

	PlayerA = CreateActor<Player>(0, "Player");
	PlayerA->SetWorldPosition({ -8930, 2030 , -4427 });
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
		Object->SetPlayerRespawnPos({ -3925, 4130 , -1911 });
		VBonfire.push_back(Object);
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -1125, -2489 , 3232 });
		Object->SetPlayerRespawnPos({ -1125, -2495 , 3180 });
		VBonfire.push_back(Object);
	}
	{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		Object->Transform.SetWorldPosition({ -16547, 3372 , 2144 });
		Object->SetPlayerRespawnPos({ -16547, 3380 , 2100 });
		VBonfire.push_back(Object);
	}
	/*{
		std::shared_ptr<Object_bonfire> Object = CreateActor<Object_bonfire>(1);
		VBonfire.push_back(Object);
	}*/
	

	//사다리
	{
		 Ladder1 = CreateActor<Object_Ladder1>(1);
	}
	{
		Ladder2 = CreateActor<Object_Ladder2>(1);
	}
	{
		Ladder3 = CreateActor<Object_Ladder3>(1);
	}
	{
		Ladder4 = CreateActor<Object_Ladder4>(1);
	}
	{
		Ladder5 = CreateActor<Object_Ladder5>(1);
	}
	{
		Ladder6 = CreateActor<Object_Ladder6>(1);
	}


	{
		BossDoor = CreateActor<Object_BossDoor>(1);
	}
	{
		CastleDoor = CreateActor<Object_CastleDoor>(1);
	}
	{
		Desk = CreateActor<Object_Desk>(1);
	}
	/*{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
	}
	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
	}*/

	/*{
		std::shared_ptr<Object_StartDoor> Object = CreateActor<Object_StartDoor>(1);
	}*/
	
	/*{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
	}*/

	/*{
		std::shared_ptr<Object_HumanTree> Object = CreateActor<Object_HumanTree>(1);
	}*/

	/*{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
	}*/

	//횃불
	//1
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -7286, -550 , 14098 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//2
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6465, -550 , 14515 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//3
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6035, -437 , 9824 });
		Object->Transform.SetWorldRotation({ 0, -90, 0 });
		VTorchlight.push_back(Object);
	}
	//4
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6889, -350 , 9890 });
		Object->Transform.SetWorldRotation({ 0, 150, 0 });
		VTorchlight.push_back(Object);
	}
	//5
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15436, 2548 , 2582 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
		VTorchlight.push_back(Object);
	}
	//6
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15265, 2548 , 2249 });
		Object->Transform.SetWorldRotation({ 0, 60, 0 });
		VTorchlight.push_back(Object);
	}
	//7
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -12890, -1940 , 2970 });
		Object->Transform.SetWorldRotation({ 0, -25, 0 });
		VTorchlight.push_back(Object);
	}
	//8
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6050, 193 , 6861 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//9
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -5760, 193 , 7011 });
		Object->Transform.SetWorldRotation({ 0, -20, 0 });
		VTorchlight.push_back(Object);
	}
	//10
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15440, 2683 , -4280 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//11
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15790, 2683 , -4225 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//12
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15960, 2683 , -4239 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//13
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16320, 2683 , -4208 });
		Object->Transform.SetWorldRotation({ 0, 8, 0 });
		VTorchlight.push_back(Object);
	}
	//14
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16720, 3110 , 230 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
		VTorchlight.push_back(Object);
	}
	//15
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -16280, 3110 , 285 });
		Object->Transform.SetWorldRotation({ 0, 180, 0 });
		VTorchlight.push_back(Object);
	}
	//16
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -230, -2205 , 4460 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//17
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -654 ,-2205 , 5294 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//18
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1076, -2205 , 6123 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//19
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -1509, -2205 , 6969 });
		Object->Transform.SetWorldRotation({ 0, -120, 0 });
		VTorchlight.push_back(Object);
	}
	//20
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -2758, -2205 , 3187 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//21
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3196, -2205 , 4048 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//22
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3618, -2205 , 4876 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//23
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -4045, -2205 , 5715 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//24
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6979, -252 , 8556 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//25
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -6705, -252 , 8015 });
		Object->Transform.SetWorldRotation({ 0, 65, 0 });
		VTorchlight.push_back(Object);
	}
	//26
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -3497, -2236 , 7094 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//27
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -2934, -2236 , 7381 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//28
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -17716, -3039 , 2180 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//29
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -15512, 3079 , 1700 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//30
	{
		std::shared_ptr<Object_Torchlight> Object = CreateActor<Object_Torchlight>(1);
		Object->Transform.SetWorldPosition({ -17056, 2754 , 2799 });
		Object->Transform.SetWorldRotation({ 0, -30, 0 });
		VTorchlight.push_back(Object);
	}
	//촛불동상
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6611, 3400 , -3566 });
		VCandleHuman.push_back(Object);
	}

	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7511, 3400 , -3966 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7111, 3470 , -4116 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6961, 3482 , -4016 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6355, 3480 , -4178 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -5805, 3485 , -3878 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -11664, 2887 , -4428 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -11764, 2887 , -4428 });
		VCandleHuman.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12648, 2890 , -4339 });
		VCandleHuman.push_back(Object);
	}
	//2
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -7092, 3400 , -3759 });
		VCandleHuman2.push_back(Object);
	}

	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5651, 3490 , -3813 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5399, 3480 , -3308 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12379, 2970 , -4687 });
		VCandleHuman2.push_back(Object);
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12166, 2888 , -4414 });
		VCandleHuman2.push_back(Object);
	}

	//테이블

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 100 , 0 });
		Object->Transform.SetWorldPosition({ -9420, 2873 , -5022 });
		VTable.push_back(Object);
	}

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -8970, 2873 , -5022 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 10 , 0 });
		Object->Transform.SetWorldPosition({ -8320, 2873 , -4772 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -8270, 2873 , -4372 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12981, 1630 , 3222 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -16644, 2324 , 703 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 110 , 0 });
		Object->Transform.SetWorldPosition({ -17144, 2324 , 853 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 40 , 0 });
		Object->Transform.SetWorldPosition({ -16380, 2440 , -3867 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -15830, 2440 , -3817 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -11242, 996 , 5644 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -10892, 996 , 5794 });
		VTable.push_back(Object);
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 50 , 0 });
		Object->Transform.SetWorldPosition({ -11462, 996 , 6044 });
		VTable.push_back(Object);
	}

	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -4208, 4121 , -2223 });
		VHumanTree1.push_back(Object);
	}

	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.SetWorldPosition({ -5862, 3373 , -2474 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -7124, 3400 , -2627 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10304, 3630 , -4057 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -9779, 3625 , -3386 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -75 , 0 });
		Object->Transform.SetWorldPosition({ -11954, 2880 , -3783 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -15964, 3383 , 2464 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -16253, 3392 , 786 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15684, 2685 , -228 });
		VHumanTree1.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -16702, 2760 , -2225 });
		VHumanTree1.push_back(Object);
	}

	//타입2
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -110 , 0 });
		Object->Transform.SetWorldPosition({ -3863, 4132 , -829 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12805, 2028 , -2796 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 180 , 0 });
		Object->Transform.SetWorldPosition({ -15877, 3390 , 693 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -16953, 3387 , 1146 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -100 , 0 });
		Object->Transform.SetWorldPosition({ -16724, 2761 , -1474 });
		VHumanTree2.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12679, 2652 , 2944 });
		VHumanTree2.push_back(Object);
	}

	//3
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -5616, 3400 , -2408 });
		VHumanTree3.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10276, 3635 , -4497 });
		VHumanTree3.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -16323, 3383 , 1735 });
		VHumanTree3.push_back(Object);
	}

	//4
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -7280, 3410 , -3220 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -10125, 3628 , -3695 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12936, 2879 , -3303 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -120 , 0 });
		Object->Transform.SetWorldPosition({ -11593, 2229 , 5327 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15570, 3392 , 1287 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12659, 2020 , -2837 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -4312, 4131 , -1138 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6452, 3410 , -2587 });
		VHumanTree4.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -16699, 2763 , -1721 });
		VHumanTree4.push_back(Object);
	}

	//5

	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -4181, 4123 , -2059 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -3515, 4130 , -744 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -12085, 2893 , -3772 });
		VHumanTree5.push_back(Object);
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -11879, 2143 , 5269 });
		VHumanTree5.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1337, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1187, 4950 , -4534 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5299 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5149 });
		Object->Transform.SetWorldRotation({ 0, 120 , 0 });
		VSkeleton.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -1037, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
		VSkeleton1.push_back(Object);
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -937, 4950 , -4734 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
		VSkeleton1.push_back(Object);
	}
	//
	//Object_BossDoor
	//Object_CastleDoor
	//Object_Desk
	//Object_Skeleton
	//Object_Skeleton1
	//Object_StartDoor
	//Object_Sword
	//Object_Table
}
