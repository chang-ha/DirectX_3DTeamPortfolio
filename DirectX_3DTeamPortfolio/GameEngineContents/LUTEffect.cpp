#include "PreCompile.h"
#include "LUTEffect.h"

LUTEffect::LUTEffect() 
{
}

LUTEffect::~LUTEffect()
{
}

void LUTEffect::Start()
{

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("LUT");


	//EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "EngineBaseSampler");
	EffectUnit.ShaderResHelper.SetSampler("LUTTexSampler", "Point");


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

}

void LUTEffect::EffectProcess(float _DeltaTime)
{
	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find("30.Willis.png");

	EffectUnit.ShaderResHelper.SetTexture("LUTTex", Texture);

	ResultTarget->Clear();
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

