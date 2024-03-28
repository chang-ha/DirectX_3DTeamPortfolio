#include "PreCompile.h"
#include "LUTEffect.h"
#include <algorithm> 

LUTEffect::LUTEffect() 
{
}

LUTEffect::~LUTEffect()
{
}

std::vector<std::string> LUTEffect::LUTNames;

std::string LUTEffect::CurLUTNameValue;
LutInfo LUTEffect::MainLutInfoValue;

void LUTEffect::Load()
{
	{
		// LUT ·Îµå
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("LUT");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".png" }, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Files[i].GetStringPath());

			LUTNames.push_back(Files[i].GetFileName());
		}

		std::sort(LUTNames.begin(), LUTNames.end());
		//LUTNames.sort
	}
}

void LUTEffect::Start()
{
	MainLutInfoValue.Lutweight = 0.666f;
	CurLUTNameValue = "16.Hughes.png";
	
	EffectUnit.SetMesh("fullrect");
	EffectUnit.SetMaterial("LUT");


	//EffectUnit.ShaderResHelper.SetConstantBufferLink("RenderBaseInfo", RenderBaseInfoValue);
	EffectUnit.ShaderResHelper.SetTexture("DiffuseTex", EffectTarget->GetTexture(0));
	EffectUnit.ShaderResHelper.SetSampler("DiffuseTexSampler", "EngineBaseSampler");
	EffectUnit.ShaderResHelper.SetSampler("LUTTexSampler", "Linear");
	EffectUnit.ShaderResHelper.SetConstantBufferLink("LutInfo", MainLutInfoValue);


	float4 WindowScale = GameEngineCore::MainWindow.GetScale();

	ResultTarget = GameEngineRenderTarget::Create();
	ResultTarget->AddNewTexture(DXGI_FORMAT_R32G32B32A32_FLOAT, WindowScale, float4::ZERONULL);

}

void LUTEffect::EffectProcess(float _DeltaTime)
{

	if ("" == CurLUTNameValue)
	{
		return;
	}

	std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Find(CurLUTNameValue);

	EffectUnit.ShaderResHelper.SetTexture("LUTTex", Texture);

	ResultTarget->Clear();
	ResultTarget->Setting();
	EffectUnit.Render();
	EffectUnit.ShaderResHelper.AllShaderResourcesReset();

	EffectTarget->Copy(0, ResultTarget, 0);
}

