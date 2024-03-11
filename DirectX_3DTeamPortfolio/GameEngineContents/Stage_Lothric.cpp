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