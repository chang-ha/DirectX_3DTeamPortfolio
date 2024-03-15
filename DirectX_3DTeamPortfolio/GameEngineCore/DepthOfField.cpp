#include "PreCompile.h"
#include "DepthOfField.h"

DepthOfField::DepthOfField() 
{
	RenderBaseInfoValue.ScreenSize = GameEngineCore::MainWindow.GetScale();
}

DepthOfField::~DepthOfField()
{
}

void DepthOfField::Init(std::shared_ptr<GameEngineCamera> _Camera)
{
	DepthOfFieldUnit.ShaderResHelper.SetTexture("PosTex", _Camera->GetCameraAllRenderTarget()->GetTexture(2));
}

void DepthOfField::Start()
{
	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

	BlurTarget = GameEngineRenderTarget::Create();
	BlurTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("BlurPostEffect");

	EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "Point");

	DepthOfFieldUnit.SetMesh("fullrect");
	DepthOfFieldUnit.SetMaterial("DepthOfField");

	DepthOfFieldUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	DepthOfFieldUnit.ShaderResHelper.SetTexture("BlurTex", BlurTarget->GetTexture(0));
	DepthOfFieldUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "Point");

	


}
void DepthOfField::EffectProcess(float _DeltaTime)
{
	BlurTarget->Clear();
	ResultTarget->Clear();

	BlurTarget->Setting();
	//ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	ResultTarget->Setting();
	DepthOfFieldUnit.Render();
	DepthOfFieldUnit.ShaderResHelper.AllShaderResourcesReset();


	EffectTarget->Copy(0, ResultTarget, 0);
}