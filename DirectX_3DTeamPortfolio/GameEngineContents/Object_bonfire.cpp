#include "PreCompile.h"
#include "Object_bonfire.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"


Object_bonfire::Object_bonfire()
{	
}

Object_bonfire ::~Object_bonfire()
{
}

void Object_bonfire::Start()
{

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o000100.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		//FBXRenderer->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		//FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	
	Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Bonfire);
	Col->SetCollisionType(ColType::AABBBOX3D);
	Col->Transform.SetLocalPosition({ 0, 50 , 0 });
	Col->Transform.SetWorldScale({100,100,100});

	GameEngineLevel* Level = GetLevel();
	Light = Level->CreateActor<ContentsLight>(Enum_UpdateOrder::Light, "BonFirePoint");
	Light->SetLightType(Enum_LightType::Point);

	//Light->IsDebugValue = true;

	LightData Data = Light->GetLightData();

	Data.LightPower = 50.0f;
	Data.LightColor = { 1.2f,0.7f,0.4f };
	Data.linearAttenuation = 0.04f;
	Data.quadraticAttenuation = 0.003f;

	Light->SetLightData(Data);

	//test
}

void Object_bonfire::Update(float _Delta)
{

	Light->Transform.SetLocalPosition(Transform.GetWorldPosition() + float4(0.f,40.f,0.f));
}
