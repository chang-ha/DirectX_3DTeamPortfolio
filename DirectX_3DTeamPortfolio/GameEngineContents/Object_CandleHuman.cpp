#include "PreCompile.h"
#include "Object_CandleHuman.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"
#include "ContentsAlphaSpriteRenderer.h"


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
<<<<<<< HEAD
		FBXRenderer->SetStatic();
=======
		FBXRenderer->RenderBaseInfoValue.IsNormal = -1;
>>>>>>> Develop
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



		GameEngineLevel* Level = GetLevel();
		Light = Level->CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "Point");
		Light->SetLightType(Enum_LightType::Point);

		//Light->IsDebugValue = true;

		LightData Data = Light->GetLightData();

		Data.LightPower = 5.0f;
		Data.LightColor = { 1.2f,0.7f,0.4f };

		Light->SetLightData(Data);
	}
}

void Object_CandleHuman::Update(float _Delta)
{
	Light->Transform.SetLocalPosition(FireRender->Transform.GetWorldPosition());
}
