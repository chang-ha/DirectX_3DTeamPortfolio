#include "PreCompile.h"
#include "FogEffect.h"

FogEffect::FogEffect() 
{
}

FogEffect::~FogEffect()
{
	FogEffect::MainFogInfo = nullptr;
}

FogInfo* FogEffect::MainFogInfo = nullptr;
 float FogEffect::FogTimeScale = 0.5f;

void FogEffect::Init(std::shared_ptr<GameEngineCamera> _Camera)
{
	EffectUnit.ShaderResHelper.SetTexture("PosTex", _Camera->GetCameraAllRenderTarget()->GetTexture(2));

	MainFogInfo = &FogInfoValue;
}

void FogEffect::Load()
{
	/*GameEngineDirectory Dir;
	Dir.MoveParentToExistsChild("ContentsResources");
	Dir.MoveChild("ContentsResources");
	Dir.MoveChild("Effect");
	Dir.MoveChild("Fog");
	std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" }, true);

	for (size_t i = 0; i < Files.size(); i++)
	{
		std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Files[i].GetStringPath());

		
	}*/
}



void FogEffect::Update(float _DeltaTime, std::shared_ptr<GameEngineCamera> _Camera)
{
	FogInfoValue.CameraViewInverseMatrix = _Camera->Transform.GetConstTransformDataRef().ViewMatrix.InverseReturn();

	//FogInfoValue.NoiseOffset += _DeltaTime * FogTimeScale;
}

void FogEffect::Start()
 {
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("Fog");

	std::shared_ptr<GameEngineTexture> Texutre = GameEngineTexture::Find("FogNoise2.png");

	EffectUnit.ShaderResHelper.SetTexture("SceneTex", EffectTarget->GetTexture(0));
	//EffectUnit.ShaderResHelper.SetTexture("NoiseTex", Texutre);
	EffectUnit.ShaderResHelper.SetSampler("SceneTexSampler", "EngineBaseSampler");
	EffectUnit.ShaderResHelper.SetSampler("PosTexSampler", "EngineBaseSampler");
	//EffectUnit.ShaderResHelper.SetSampler("NoiseTexSampler", "EngineBaseWRAPSampler");
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

