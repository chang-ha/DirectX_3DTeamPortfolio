#include "PreCompile.h"
#include "Object_CandleHuman.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"


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
		FBXRenderer->SetFBXMesh("o302565.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100,100,100 });
		FBXRenderer->SetStatic();
	}
	{
		FireRender = CreateComponent<ContentsFireRenderer>(Enum_RenderOrder::Effect);
		FireRender->SetBillboardOn();
		FireRender->SetName("Fire");
		FireRender->Transform.SetLocalScale({ 8.0f, 15.0f, 10.0f });

		float4 FirePos = { -1.5f, 87.0f, 35.0f };
		FireRender->Transform.SetLocalPosition(FirePos);


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

}
