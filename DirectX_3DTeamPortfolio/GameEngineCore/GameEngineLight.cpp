#include "PreCompile.h"
#include "GameEngineLight.h"
#include "GameEngineCamera.h"
#include "GameEngineRenderTarget.h"

GameEngineLight::GameEngineLight() 
{
	LightDataValue.ShadowTargetSizeX = 16384;
	LightDataValue.ShadowTargetSizeY = 16384;
	LightDataValue.LightNear = 0.1f;
	LightDataValue.LightFar = 2000.0f;
}

void GameEngineLight::ShadowTargetSetting()
{
	ShadowTarget->Clear();
	ShadowTarget->Setting();
}
GameEngineLight::~GameEngineLight() 
{
}

void GameEngineLight::Start()
{
	GetLevel()->PushLight(GetDynamic_Cast_This<GameEngineLight>());

	// �� �ؽ�ó ũ�� �ٱ����� ������ �׸��ڰ� ���� �ʽ��ϴ�.
	ShadowTarget = GameEngineRenderTarget::Create();
	//ShadowTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, { LightDataValue.ShadowTargetSizeX, LightDataValue.ShadowTargetSizeY }, float4::RED);
	// �ڽŸ��� ���̹��۸� ������ �Ѵ�. �ؽ��ĸ� ������ �����Ƿ� ����Ʈ�� ���� ����
	ShadowTarget->CreateDepthTexture(float4{ LightDataValue.ShadowTargetSizeX, LightDataValue.ShadowTargetSizeY });
	ShadowTarget->CreateViewports(float4{ LightDataValue.ShadowTargetSizeX, LightDataValue.ShadowTargetSizeY });
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