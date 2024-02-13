#include "PreCompile.h"
#include "BloomEffect.h"

BloomEffect::BloomEffect() 
{
}

BloomEffect::~BloomEffect()
{
}

void BloomEffect::Start()
{

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

	BlurTarget = GameEngineRenderTarget::Create();
	BlurTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

	CombineTarget = GameEngineRenderTarget::Create();
	CombineTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);


	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("BloomBright");


	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "EngineBaseSampler");

	BlurUnit.SetMesh("fullrect");
	BlurUnit.SetMaterial("BloomBlur");

	BlurUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	BlurUnit.ShaderResHelper.SetTexture("BrightTex", BlurTarget->GetTexture(0));
	BlurUnit.ShaderResHelper.SetSampler("BrightTexSampler", "EngineBaseSampler");


	CombineUnit.SetMesh("fullrect");
	CombineUnit.SetMaterial("BloomCombine");

	CombineUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	CombineUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "EngineBaseSampler");
	CombineUnit.ShaderResHelper.SetTexture("BlurTex", BlurTarget->GetTexture(0));
	CombineUnit.ShaderResHelper.SetSampler("BlurTexSampler", "EngineBaseSampler");


	
}

void BloomEffect::EffectProcess(float _DeltaTime)
{
	ResultTarget->Clear();
	BlurTarget->Clear();
	CombineTarget->Clear();

	//Bright 프로세스
	BlurTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	// Blur 프로세스
	CombineTarget->Setting();
	BlurUnit.Render();
	BlurUnit.ShaderResHelper.AllShaderResourcesReset();

	//Combine 프로세스

	ResultTarget->Setting();
	CombineUnit.Render();
	CombineUnit.ShaderResHelper.AllShaderResourcesReset();


	EffectTarget->Copy(0, ResultTarget, 0);
}

