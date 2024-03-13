#include "PreCompile.h"
#include "Object_Torchlight.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"


Object_Torchlight::Object_Torchlight()
{	
}

Object_Torchlight ::~Object_Torchlight()
{
}

void Object_Torchlight::Start()
{
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o004660.FBX", "FBX_Static");
		//FBXRenderer->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		FBXRenderer->SetStatic();
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		//FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}
	{
		FireRender = CreateComponent<ContentsFireRenderer>(Enum_RenderOrder::Effect);
		FireRender->SetBillboardOn();
		FireRender->SetName("Fire");
		FireRender->Transform.SetLocalScale({ 70.f, 80.0f, 100.0f });
		
		float4 FirePos = { -4.0f, 41.0f, 83.0f };
		FireRender->Transform.SetLocalPosition(FirePos);
	

		//GameEngineLevel* Level = GetLevel();
		//Light = Level->CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "Point");
		//Light->SetLightType(Enum_LightType::Point);

		////Light->IsDebugValue = true;

		//LightData Data = Light->GetLightData();

		//Data.LightPower = 5.0f;
		//Data.LightColor = { 1.2f,0.7f,0.4f };

		//Light->SetLightData(Data);
	}
}

void Object_Torchlight::Update(float _Delta)
{
	//Light->Transform.SetLocalPosition(FireRender->Transform.GetWorldPosition());
}
