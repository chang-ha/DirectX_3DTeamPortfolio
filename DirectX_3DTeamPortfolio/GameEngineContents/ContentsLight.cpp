#include "PreCompile.h"
#include "ContentsLight.h"

ContentsLight::ContentsLight() 
{
}

ContentsLight::~ContentsLight()
{
}

void ContentsLight::Start()
{
	GameEngineLight::Start();
	Transform.SetWorldScale(float4(25.f, 25.f, 25.f));
}

void ContentsLight::Update(float _DeltaTime)
{
	GameEngineLight::Update(_DeltaTime);
	if (true == IsDebugValue)
	{
		//Transform.SetWorldScale(float4(50.f, 50.f, 50.f));
		GameEngineDebug::DrawSphere2D(Transform, float4::GREEN, GetLevel()->GetMainCamera().get());
	}
}

