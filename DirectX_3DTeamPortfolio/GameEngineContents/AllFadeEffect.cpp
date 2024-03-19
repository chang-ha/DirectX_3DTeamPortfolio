#include "PreCompile.h"
#include "AllFadeEffect.h"


void AllFadeEffect::Load()
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("AllFadeEffect");
	Mat->SetVertexShader("AllFadeEffect_VS");
	Mat->SetPixelShader("AllFadeEffect_PS");
	Mat->SetDepthState("AlwaysDepth");
	Mat->SetRasterizer("EngineRasterizer");
}

AllFadeEffect::AllFadeEffect()
{
}

AllFadeEffect::~AllFadeEffect()
{
}

void AllFadeEffect::Start()
{
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("AllFadeEffect");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("FadeInfo", Info);
	EffectUnit.ShaderResHelper.SetSampler("FadeTexSampler", "POINT");
	EffectUnit.ShaderResHelper.SetTexture("FadeTex", EffectTarget->GetTexture(0));

	const float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);
	FadeSpeed = 1.0f;
	Info.FadeColor = float4::ZERO;
}

void AllFadeEffect::EffectProcess(float _DeltaTime)
{
	const float TimeValue = FadeSpeed * _DeltaTime;

	if (Enum_FadeType::FadeIn == Type)
	{
		Info.Ratio -= TimeValue;
	}
	if (Enum_FadeType::FadeOut == Type)
	{
		Info.Ratio += TimeValue;
	}

	if (Info.Ratio < 0.0f || Info.Ratio > 1.0f)
	{
		Info.Ratio = std::clamp(Info.Ratio, 0.0f, 1.0f);
		OutputDebugStringA("FadeEffect Off");
		Off();
	}

	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

void AllFadeEffect::FadeIn()
{
	Type = Enum_FadeType::FadeIn; 
	Info.Ratio = 1.0f;
	On();
}

void AllFadeEffect::FadeOut() 
{
	Type = Enum_FadeType::FadeOut; 
	Info.Ratio = 0.0f;
	On();
}