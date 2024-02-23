#include "PreCompile.h"
#include "GameEngineLight.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"

GameEngineLight::GameEngineLight() 
{
	LightDataValue.ShadowTargetSizeX = 16384;
	LightDataValue.ShadowTargetSizeY = 16384;
	LightDataValue.LightNear = 0.1f;
	LightDataValue.LightFar = 100000.0f;
}

void GameEngineLight::ShadowTargetSetting()
{
	ShadowTarget->Clear();
	ShadowTarget->Setting();
}
GameEngineLight::~GameEngineLight() 
{
}

void GameEngineLight::CreateShadowMap(float4 _Size)
{
	ShadowTarget = GameEngineRenderTarget::Create();
	ShadowTargetStatic = GameEngineRenderTarget::Create();
	LightDataValue.ShadowTargetSizeX = _Size.X ;
	LightDataValue.ShadowTargetSizeY = _Size.Y ;


	// 자신만의 깊이버퍼를 가져야 한다. 텍스쳐를 만들지 않으므로 뷰포트도 따로 생성
	ShadowTarget->CreateDepthTexture(float4{ _Size.X, _Size.Y });
	ShadowTarget->CreateViewports(float4{ _Size.X, _Size.Y });
	ShadowTargetStatic->CreateDepthTexture(float4{ _Size.X, _Size.Y });
	ShadowTargetStatic->CreateViewports(float4{ _Size.X, _Size.Y });
}

void GameEngineLight::Start()
{
	GetLevel()->PushLight(GetDynamic_Cast_This<GameEngineLight>());

	// 이 텍스처 크기 바깥으로 나가면 그림자가 지지 않습니다.
	
}



void GameEngineLight::Update(float _DeltaTime)
{

}


void GameEngineLight::LightUpdate(GameEngineCamera* _Camera, float _DeltaTime)
{
	LightDataValue.CameraViewInverseMatrix = _Camera->Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();

	float4x4 CameraView = _Camera->Transform.GetConstTransformDataRef().ViewMatrix;

	LightDataValue.LightPos = Transform.GetWorldPosition();
	LightDataValue.LightDir = Transform.GetWorldForwardVector();
	LightDataValue.ViewLightPos = LightDataValue.LightPos * CameraView;
	LightDataValue.ViewLightDir = LightDataValue.LightDir * CameraView;
	LightDataValue.ViewLightDir.W = 0.0f;
	LightDataValue.ViewLightDir.Normalize();
	LightDataValue.ViewLightRevDir = -LightDataValue.ViewLightDir; // L
	LightDataValue.ViewLightRevDir.Normalize();

	LightDataValue.CameraPosition = _Camera->Transform.GetWorldPosition() * CameraView;

	LightDataValue.LightViewMatrix.LookToLH(
		Transform.GetWorldPosition(),
		Transform.GetWorldForwardVector(),
		Transform.GetWorldUpVector()
	);

	LightDataValue.LightProjectionMatrix.OrthographicLH(
		ShadowRange.X,
		ShadowRange.Y,
		LightDataValue.LightNear,
		LightDataValue.LightFar
	);

	LightDataValue.LightProjectionInverseMatrix = LightDataValue.LightProjectionMatrix.InverseReturn();
	LightDataValue.LightViewProjectionMatrix = LightDataValue.LightViewMatrix * LightDataValue.LightProjectionMatrix;
}