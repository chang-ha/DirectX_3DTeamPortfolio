#include "PreCompile.h"
#include "Stage_Lothric.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "Player.h"
#include "WorldMap.h"
#include <GameEngineCore\FogEffect.h>
#include <GameEngineCore\DepthOfField.h>
#include "FXAAEffect.h"
#include "Monster_HollowSoldier.h"
#include "Monster_LothricKn.h"
#include "LUTEffect.h"

#include "Monster_LothricKn.h"

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

Stage_Lothric::Stage_Lothric()
{

}

Stage_Lothric::~Stage_Lothric()
{

}

void Stage_Lothric::LevelStart(GameEngineLevel* _PrevLevel)
{
	{
		std::shared_ptr<GameEngineActor> Ground = CreateActor<GameEngineActor>(0);
		std::shared_ptr<GameEngineRenderer> NewRenderer = Ground->CreateComponent<GameEngineRenderer>();
		NewRenderer->SetMesh("Box");
		NewRenderer->SetMaterial("FBX_Static_Color");
		// NewRenderer->GetShaderResHelper().SetTexture("NormalTexture", "BumpNormal.gif");
		NewRenderer->Transform.SetLocalPosition({ 0.0f, -40000.0f, 0.0f });
		NewRenderer->Transform.SetLocalScale({ 1000000.0f, 100.0f, 1000000.0f });
		NewRenderer->RenderBaseInfoValue.BaseColor = float4(0.0f, 0.0f, 0.0f, 1.0f);
	}

	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->SetWorldPosition({ -1000.f, -2500.f, 3000.f });
		Boss_Object->SetWorldRotation({ 0.f, -30.f, 0.f });
		Boss_Object->Off();
	}


	// Light
	if (nullptr == Light)
	{
		Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "mainDirect");
		LightData Data = Light->GetLightData();
		Light->CreateShadowMap();

		//Data.DifLightPower = 0.1f;
		Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
		Data.LightColor = float4(1.0f, 1.0f, 0.7f);
		Data.LightPower = 10.0f;
		Data.ForceLightPower = 0.25f;

		Light->Transform.SetLocalPosition({ -12000.0f, 16200.0f, -4260.0f });
		Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


		Light->SetLightData(Data);
		//Light->IsDebugValue = true;
	}

	//{
	//	Light = CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "Point");
	//	Light->SetLightType(Enum_LightType::Point);
	//	LightData Data = Light->GetLightData();
	//	//Light->CreateShadowMap();

	//	//Data.DifLightPower = 0.1f;
	//	Data.AmbientLight = float4(0.05f, 0.05f, 0.025f, 1.0f);
	//	Data.LightColor = float4(1.0f, 1.0f, 0.7f);
	//	Data.LightPower = 2.5f;
	//	Data.ForceLightPower = 0.25f;

	//	Light->Transform.SetWorldPosition({ -2800.f, -2500.f, 6700.f });
	//	Light->Transform.SetLocalRotation({ 40.0f, 0.0f, 0.0f });


	//	Light->SetLightData(Data);
	//	Light->IsDebugValue = true;
	//}
	// 

	// DepthOfField
	{
		std::shared_ptr<DepthOfField> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<DepthOfField>();
		Effect->Init(GetMainCamera());
	}
	//
	// Fog
	/*{
		std::shared_ptr<FogEffect> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
		Effect->Init(GetMainCamera());
	}*/


	////FXAA

	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<LUTEffect>();

	// Building

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	{
		Player_Object = CreateActor<Player>(0, "Player");
		// 볼드 위치
		//Player_Object->Transform.SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		// 
		// 계단 위치
		//Player_Object->Transform.SetWorldPosition({ -9910.0f, 2328.0f, -2894.0f });
		// 
		// 시작 위치
		Player_Object->Transform.SetLocalPosition({ -1400.0f, 5101.0f, -5331.0f });

		Player_Object->Transform.SetWorldRotation({ 0.f, 165.f, 0.f });
		Player_Object->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(Player_Object.get());
	}
	/*{
		std::shared_ptr<Monster_HollowSoldier> GameMap = CreateActor<Monster_HollowSoldier>(0 );
		GameMap->Transform.SetWorldPosition({ -2900.f,-2500.f,6800.f });
	}*/

	{
		Map_Lothric = CreateActor<WorldMap>(0, "WorldMap");
	}

	{
		std::shared_ptr<Monster_LothricKn> Monster;
		Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Lothric1");
		Monster->SetWPosition(float4(-5443.0f, -876.f, 10681.f));
		Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Lothric2");
		Monster->SetWPosition(float4(-6276, -683, 13803));
	}

	// 몬스터 위치 셋팅
	SetAllMonster();

	std::shared_ptr<GameEngineCoreWindow> CoreWindow = GameEngineGUI::FindGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");

	if (nullptr != CoreWindow)
	{
		CoreWindow->AddDebugRenderTarget(1, "PlayLevelRenderTarget", GetMainCamera()->GetCameraAllRenderTarget());
		CoreWindow->AddDebugRenderTarget(2, "ForwardTarget", GetMainCamera()->GetCameraForwardTarget());
		CoreWindow->AddDebugRenderTarget(3, "DeferredLightTarget", GetMainCamera()->GetCameraDeferredLightTarget());
		CoreWindow->AddDebugRenderTarget(4, "DeferredTarget", GetMainCamera()->GetCameraDeferredTarget());
		//CoreWindow->AddDebugRenderTarget(5, "LightTarget", Light->GetShadowTarget());
		//CoreWindow->AddDebugRenderTarget(3, "HBAO", GetMainCamera()->GetCameraHBAOTarget());
	}
}

void Stage_Lothric::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Stage_Lothric::Start()
{
	IsDebug = false;
	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	CreateObject();
}

void Stage_Lothric::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	float4 PPos = Player_Object->Transform.GetWorldPosition();

	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
	}
	if (true == GameEngineInput::IsDown('J', this))
	{
		Player_Object->Off();
	}

}

void Stage_Lothric::Release()
{
	if (nullptr != Boss_Object)
	{
		Boss_Object->Death();
		Boss_Object = nullptr;
	}

	if (nullptr != Player_Object)
	{
		Player_Object->Death();
		Player_Object = nullptr;
	}

	if (nullptr != Map_Lothric)
	{
		Map_Lothric->Death();
		Map_Lothric = nullptr;
	}

	if (nullptr != Light)
	{
		Light->Death();
		Light = nullptr;
	}
}

void Stage_Lothric::SetAllMonster()
{

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -2738.0f, 4120.0f, -1457.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -3874.0f, 4118.0f, -1151.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -5730.0f, 3409.0f, -2575.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6764.0f, 3400.0f, -3607.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -8496.0f, 2878.0f, -4483.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -9050.0f, 2033.0f, -4071.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -10210.0f, 2030.0f, -3207.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -11265.0f, 2891.0f, -4376.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -13050.0f, 2886.0f, -3783.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -14467.0f, 2893.0f, -4080.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -15491.0f, 2943.0f, -4392.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -14397.0f, 2277.0f, -2812.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -16297.0f, 2689.0f, -1427.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -15816.0f, 2683.0f, -472.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -17594.0f, 2834.0f, 1350.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -15476.0f, 2327.0f, 2870.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -11968.0f, 1924.0f, 3882.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -10196.0f, 984.0f, 4174.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -8623.0f, 907.0f, 3707.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -8546.0f, -683.0f, 3904.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -9154.0f, 542.0f, 5211.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -7885.0f, -538.0f, 5512.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -8476.0f, -548.0f, 7715.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6396.0f, -624.0f, 8055.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -6433.0f, -750.0f, 10232.0f });
		AllMonster.push_back(Monster);
	}

	{
		std::shared_ptr<BaseMonster> Monster = CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster, "Monster_LothricKn");
		Monster->SetResponPos({ -4026.0f, -1788.0f, 9562.0f });
		AllMonster.push_back(Monster);
	}

	AllMonsterOn();
}

void Stage_Lothric::AllMonsterOn()
{

	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->SetWorldPosition(AllMonster[i]->GetResponPos());
		AllMonster[i]->On();
	}
}

void Stage_Lothric::AllMonsterOff()
{
	for (size_t i = 0; i < AllMonster.size(); i++)
	{
		AllMonster[i]->Off();
	}
}

void Stage_Lothric::CreateObject()
{
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
		std::shared_ptr<Object_StartDoor> Object = CreateActor<Object_StartDoor>(1);
	}

	/*{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
	}*/

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

	//촛불동상
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6611, 3400 , -3566 });
	}

	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7511, 3400 , -3966 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -7111, 3470 , -4116 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -6961, 3482 , -4016 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6355, 3480 , -4178 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -5805, 3485 , -3878 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -11664, 2887 , -4428 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -11764, 2887 , -4428 });
	}
	{
		std::shared_ptr<Object_CandleHuman> Object = CreateActor<Object_CandleHuman>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12648, 2890 , -4339 });
	}
	//2
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -7092, 3400 , -3759 });
	}

	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5651, 3490 , -3813 });
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -5399, 3480 , -3308 });
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12379, 2970 , -4687 });
	}
	{
		std::shared_ptr<Object_CandleHuman2> Object = CreateActor<Object_CandleHuman2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12166, 2888 , -4414 });
	}
	//테이블

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 100 , 0 });
		Object->Transform.SetWorldPosition({ -9420, 2873 , -5022 });
	}

	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -8970, 2873 , -5022 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 10 , 0 });
		Object->Transform.SetWorldPosition({ -8320, 2873 , -4772 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -8270, 2873 , -4372 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12981, 1630 , 3222 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -16644, 2324 , 703 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 110 , 0 });
		Object->Transform.SetWorldPosition({ -17144, 2324 , 853 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 40 , 0 });
		Object->Transform.SetWorldPosition({ -16380, 2440 , -3867 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -15830, 2440 , -3817 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -11242, 996 , 5644 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -10892, 996 , 5794 });
	}
	{
		std::shared_ptr<Object_Table> Object = CreateActor<Object_Table>(1);
		Object->Transform.AddWorldRotation({ 0, 50 , 0 });
		Object->Transform.SetWorldPosition({ -11462, 996 , 6044 });
	}

	//인간트리
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 90 , 0 });
		Object->Transform.SetWorldPosition({ -4208, 4121 , -2223 });
	}

	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.SetWorldPosition({ -5862, 3373 , -2474 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -7124, 3400 , -2627 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10304, 3630 , -4057 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -9779, 3625 , -3386 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -75 , 0 });
		Object->Transform.SetWorldPosition({ -11954, 2880 , -3783 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -15964, 3383 , 2464 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -16253, 3392 , 786 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15684, 2685 , -228 });
	}
	{
		std::shared_ptr<Object_HumanTree1> Object = CreateActor<Object_HumanTree1>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -16702, 2760 , -2225 });
	}

	//타입2
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -110 , 0 });
		Object->Transform.SetWorldPosition({ -3863, 4132 , -829 });
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12805, 2028 , -2796 });
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 180 , 0 });
		Object->Transform.SetWorldPosition({ -15877, 3390 , 693 });
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -16953, 3387 , 1146 });
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, -100 , 0 });
		Object->Transform.SetWorldPosition({ -16724, 2761 , -1474 });
	}
	{
		std::shared_ptr<Object_HumanTree2> Object = CreateActor<Object_HumanTree2>(1);
		Object->Transform.AddWorldRotation({ 0, 0 , 0 });
		Object->Transform.SetWorldPosition({ -12679, 2652 , 2944 });
	}

	//3
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -5616, 3400 , -2408 });
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, -50 , 0 });
		Object->Transform.SetWorldPosition({ -10276, 3635 , -4497 });
	}
	{
		std::shared_ptr<Object_HumanTree3> Object = CreateActor<Object_HumanTree3>(1);
		Object->Transform.AddWorldRotation({ 0, 60 , 0 });
		Object->Transform.SetWorldPosition({ -16323, 3383 , 1735 });
	}

	//4
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -90 , 0 });
		Object->Transform.SetWorldPosition({ -7280, 3410 , -3220 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -10125, 3628 , -3695 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12936, 2879 , -3303 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -120 , 0 });
		Object->Transform.SetWorldPosition({ -11593, 2229 , 5327 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, 30 , 0 });
		Object->Transform.SetWorldPosition({ -15570, 3392 , 1287 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -12659, 2020 , -2837 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -30 , 0 });
		Object->Transform.SetWorldPosition({ -4312, 4131 , -1138 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -6452, 3410 , -2587 });
	}
	{
		std::shared_ptr<Object_HumanTree4> Object = CreateActor<Object_HumanTree4>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -16699, 2763 , -1721 });
	}

	//5

	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -4181, 4123 , -2059 });
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ 3515, 4130 , -744 });
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -40 , 0 });
		Object->Transform.SetWorldPosition({ -12085, 2893 , -3772 });
	}
	{
		std::shared_ptr<Object_HumanTree5> Object = CreateActor<Object_HumanTree5>(1);
		Object->Transform.AddWorldRotation({ 0, -60 , 0 });
		Object->Transform.SetWorldPosition({ -11879, 2143 , 5269 });
	}

	//뼛조각
	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1337, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -1187, 4950 , -4534 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5299 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
	}

	{
		std::shared_ptr<Object_Skeleton> Object = CreateActor<Object_Skeleton>(1);
		Object->Transform.SetWorldPosition({ -845, 4950 , -5149 });
		Object->Transform.SetWorldRotation({ 0, 120 , 0 });
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -1037, 4950 , -4634 });
		Object->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		std::shared_ptr<Object_Skeleton1> Object = CreateActor<Object_Skeleton1>(1);
		Object->Transform.SetWorldPosition({ -937, 4950 , -4734 });
		Object->Transform.SetWorldRotation({ 0, 90 , 0 });
	}
}