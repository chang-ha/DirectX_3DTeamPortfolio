#include "PreCompile.h"
#include "FogEffect.h"

FogEffect::FogEffect() 
{
}

FogEffect::~FogEffect()
{
}

FogInfo* FogEffect::MainFogInfo = nullptr;

void FogEffect::Init(std::shared_ptr<GameEngineCamera> _Camera)
{
	EffectUnit.ShaderResHelper.SetTexture("PosTex", _Camera->GetCameraAllRenderTarget()->GetTexture(2));

	MainFogInfo = &FogInfoValue;
}



void FogEffect::Update(float _DeltaTime, std::shared_ptr<GameEngineCamera> _Camera)
{
	FogInfoValue.CameraViewInverseMatrix = _Camera->Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();
}

void FogEffect::Start()
 {
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("Fog");

	EffectUnit.ShaderResHelper.SetTexture("SceneTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("SceneTexSampler", "EngineBaseSampler");
	EffectUnit.ShaderResHelper.SetSampler("PosTexSampler", "EngineBaseSampler");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("FogInfo", FogInfoValue);

	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

}

void FogEffect::EffectProcess(float _DeltaTime)
{

	ResultTarget->Clear();
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

