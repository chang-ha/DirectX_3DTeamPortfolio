#include "PreCompile.h"
#include "FogEffect.h"

FogEffect::FogEffect() 
{
}

FogEffect::~FogEffect()
{
}

void FogEffect::Init(std::shared_ptr<GameEngineCamera> _Camera)
{
	EffectUnit.ShaderResHelper.SetTexture("PosTex", _Camera->GetCameraAllRenderTarget()->GetTexture(2));

}

void FogEffect::Update(std::shared_ptr<GameEngineCamera> _Camera)
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

}

void FogEffect::EffectProcess(float _DeltaTime)
{

	ResultTarget->Clear();
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

