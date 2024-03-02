#include "PreCompile.h"
#include "Stage_Lothric.h"
#include "Boss_Vordt.h"
#include "ContentsLight.h"
#include "Player.h"
#include "WorldMap.h"

Stage_Lothric::Stage_Lothric()
{

}

Stage_Lothric::~Stage_Lothric()
{

}

void Stage_Lothric::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Boss_Object)
	{
		Boss_Object = CreateActor<Boss_Vordt>(Enum_UpdateOrder::Monster, "Boss_Vordt");
		Boss_Object->Transform.SetWorldPosition({ -1000.f, -2500.f, 3000.f });
		Boss_Object->Transform.SetWorldRotation({ 0.f, -30.f, 0.f });
	}

	// Light
	if (nullptr == Light)
	{
		Light = CreateActor<ContentsLight>(0);
		LightData Data = Light->GetLightData();
		Light->CreateShadowMap();

		Data.DifLightPower = 0.1f;
		Data.AmbientLight = float4(0.7f, 0.7f, 0.7f, 1.0f);
		Data.SpcPow = 200.0f;

		Light->SetLightData(Data);
	}

	// Building

	GameEngineCore::GetBackBufferRenderTarget()->SetClearColor({ 0, 0, 0, 1 });

	{
		Player_Object = CreateActor<Player>(0, "Player");
		Player_Object->Transform.SetWorldPosition({ -2800.f, -2500.f, 6700.f });
		Player_Object->Transform.SetWorldRotation({ 0.f, 165.f, 0.f });
		Player_Object->SetTargeting(Boss_Object.get());
		Boss_Object->SetTargeting(Player_Object.get());
	}

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
		CoreWindow->AddDebugRenderTarget(5, "LightTarget", Light->GetShadowTarget());
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