#include "PreCompile.h"
#include "Stage_Lothric.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "Player.h"
#include "WorldMap.h"
#include <GameEngineCore\FogEffect.h>
#include "FXAAEffect.h"
#include "Monster_HollowSoldier.h"
#include "LUTEffect.h"

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
		NewRenderer->RenderBaseInfoValue.BaseColor = float4(0.0f,0.0f,0.0f,1.0f);
	}	

	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->Transform.SetWorldPosition({ -1000.f, -2500.f, 3000.f });
		Boss_Object->Transform.SetWorldRotation({ 0.f, -30.f, 0.f });

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
		Data.LightPower = 2.5f;
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

	//
	// Fog
	{
		std::shared_ptr<FogEffect> Effect = GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FogEffect>();
		Effect->Init(GetMainCamera());
	}
	////FXAA
		
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<FXAAEffect>();
	GetMainCamera()->GetCameraDeferredTarget()->CreateEffect<LUTEffect>();

	// Building

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	{
		Player_Object = CreateActor<Player>(0, "Player");
		// 볼드 위치
		//Player_Object->Transform.SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		// 계단 위치
		Player_Object->Transform.SetWorldPosition({ -9910.0f, 2328.0f, -2894.0f });
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
	

	ContentLevel::Start();
	GameEngineInput::AddInputObject(this);
	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });
	CreateObject();
}

void Stage_Lothric::Update(float _Delta)
{
	ContentLevel::Update(_Delta);

	if (true == GameEngineInput::IsDown(VK_F6, this))
	{
		GameEngineGUI::AllWindowSwitch();
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
}