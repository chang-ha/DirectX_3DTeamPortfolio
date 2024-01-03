#include "PreCompile.h"
#include "FXAAEffect.h"

FXAAEffect::FXAAEffect() 
{
	RenderBaseInfoValue.ScreenSize = GameEngineCore::MainWindow.GetScale();
}

FXAAEffect::~FXAAEffect()
{
}

void FXAAEffect::Start()
{
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("FXAA");

	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "LINEAR");


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
}

void FXAAEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Clear();
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

