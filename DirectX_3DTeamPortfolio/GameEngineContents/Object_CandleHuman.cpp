#include "PreCompile.h"
#include "Object_CandleHuman.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"
#include "ContentsAlphaSpriteRenderer.h"
#include "ContentsHitRenderer.h"


Object_CandleHuman::Object_CandleHuman()
{	
}

Object_CandleHuman::~Object_CandleHuman()
{
}

void Object_CandleHuman::Start()
{
	//1
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetStatic();
		FBXRenderer->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100,100,100 });

		FBXRenderer->SetStatic();

		FBXRenderer->RenderBaseInfoValue.IsNormal = -1;
		//FBXRenderer->RenderBaseInfoValue.ForceSpecularColor = { 0.45f,0.35f,0.0f,1.0f };

	}
	{
		FireRender = CreateComponent<ContentsAlphaSpriteRenderer>(Enum_RenderOrder::Effect);
		FireRender->SetBillboardOn();
		FireRender->SetName("Fire");
		FireRender->AutoSpriteSizeOn();
		FireRender->Transform.SetLocalPosition({ -1.5f,90.f,37.f });
		FireRender->SetAutoScaleRatio({ 0.15f, 0.15f, 0.15f });

		FireRender->CreateAnimation("CandleFire", "CandleFire2.dds", 0.0666f, -1, -1);
		FireRender->ChangeAnimation("CandleFire");

		/*std::shared_ptr<ContentsHitRenderer> Render = CreateComponent<ContentsHitRenderer>(Enum_RenderOrder::Effect);

		Render->Transform.SetLocalPosition({ -1.5f,90.f,87.f });
		Render->SetAutoScaleRatio({ 0.15f, 0.15f, 0.15f });*/

		static int num = 0;
		num++;

		GameEngineLevel* Level = GetLevel();
		Light = Level->CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "CandlePoint_" + std::to_string(num));
		Light->SetLightType(Enum_LightType::Point);

		//Light->IsDebugValue = true;

		LightData Data = Light->GetLightData();

		Data.LightPower = 5.0f;
		Data.LightColor = { 1.2f,0.7f,0.4f };

		Light->SetLightData(Data);
	}

	Box = CreateComponent<GameEnginePhysXBox>();
	Box->PhysXComponentInit(50, 50, 50);
}

void Object_CandleHuman::Update(float _Delta)
{
	Light->Transform.SetLocalPosition(FireRender->Transform.GetWorldPosition());
}
