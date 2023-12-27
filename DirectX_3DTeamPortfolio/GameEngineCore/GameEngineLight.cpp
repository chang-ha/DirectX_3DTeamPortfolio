#include "PreCompile.h"
#include "GameEngineLight.h"
#include "GameEngineCamera.h"

GameEngineLight::GameEngineLight() 
{
}

GameEngineLight::~GameEngineLight() 
{
}

void GameEngineLight::Start()
{
	GetLevel()->PushLight(GetDynamic_Cast_This<GameEngineLight>());
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
	LightDataValue.ViewLightDir.Normalize();
	LightDataValue.ViewLightRevDir = -LightDataValue.ViewLightDir; // L
	LightDataValue.ViewLightRevDir.Normalize();

	LightDataValue.CameraPosition = _Camera->Transform.GetWorldPosition() * CameraView;

	//LightDataValue.LightViewMatrix.LookToLH(
	//	Transform.GetWorldPosition(),
	//	Transform.GetWorldForwardVector(),
	//	Transform.GetWorldUpVector()
	//);

	// ³ªÁß¿¡ 
	//LightDataValue.LightProjectionMatrix.LookToLH(
	//	Transform.GetWorldPosition(),
	//	Transform.GetWorldForwardVector(),
	//	Transform.GetWorldUpVector()
	//);

	LightDataValue.LightProjectionInverseMatrix = LightDataValue.LightProjectionMatrix.InverseReturn();
	LightDataValue.LightViewProjectionMatrix = LightDataValue.LightViewMatrix * LightDataValue.LightProjectionMatrix;
}