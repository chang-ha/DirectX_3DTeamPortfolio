#include "PreCompile.h"
#include "BlurPostEffect.h"

BlurPostEffect::BlurPostEffect() 
{
	RenderBaseInfoValue.ScreenSize = GameEngineCore::MainWindow.GetScale();
}

BlurPostEffect::~BlurPostEffect() 
{
}

void BlurPostEffect::Start()
{
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("BlurPostEffect");

	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();
	ArrScreenSize.push_back(WindowScale);

	// EffectUnit.ShaderResHelper.SetStructedBufferLink("ArrScreenSize", ArrScreenSize);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "LINEAR");

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
}
void BlurPostEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();
	EffectTarget->Copy(0, ResultTarget, 0);
}