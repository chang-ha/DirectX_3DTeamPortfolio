#include "PreCompile.h"
#include "ContentsFireRenderer.h"


ContentsFireRenderer* ContentsFireRenderer::MainFire = nullptr;

ContentsFireRenderer::ContentsFireRenderer() 
{
}

ContentsFireRenderer::~ContentsFireRenderer()
{
}

void ContentsFireRenderer::Load()
{
	{
		// Fire ·Îµå
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Effect");
		Dir.MoveChild("Fire");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".dds", ".png"}, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Files[i].GetStringPath());
		}
	}

	
}

void ContentsFireRenderer::Start()
{
	/*ImageTransform.SetParent(Transform);*/
	GameEngineRenderer::Start();

	GameEngineRenderer::SetMesh("Rect");
	


	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->SetMaterial("Fire");

	DefalutRenderPathValue = RenderPath::Alpha;

	Unit->Camerapushback(DefalutRenderPathValue);

	Unit->ShaderResHelper.SetConstantBufferLink("FireInfo", FireInfoValue);


	Unit->ShaderResHelper.SetTexture("DiffuseTexture", GameEngineTexture::Find("fire02.png"));
	Unit->ShaderResHelper.SetTexture("AlphaTexture", GameEngineTexture::Find("firealpha02.png"));
	Unit->ShaderResHelper.SetTexture("NoiseTexture", GameEngineTexture::Find("firenoise01.dds"));
	Unit->ShaderResHelper.SetSampler("WrapSampler", "EngineBaseWRAPSampler");
	Unit->ShaderResHelper.SetSampler("ClampSampler", "EngineBaseSampler");
	Unit->ShaderResHelper.SetConstantBufferLink("FireInfo", FireInfoValue);

	MainFire = this;

	
}

void ContentsFireRenderer::Update(float _Delta)
{
	GameEngineRenderer::Update(_Delta);

	FireInfoValue.frameTime += _Delta * TimeScale;

	if (FireInfoValue.frameTime > 1000.0f)
	{
		FireInfoValue.frameTime -= 1000.0f;
	}




	
}

