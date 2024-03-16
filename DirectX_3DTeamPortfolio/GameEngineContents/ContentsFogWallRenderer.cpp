#include "PreCompile.h"
#include "ContentsFogWallRenderer.h"

ContentsFogWallRenderer* ContentsFogWallRenderer::MainFogWall = nullptr;

ContentsFogWallRenderer::ContentsFogWallRenderer() 
{
}

ContentsFogWallRenderer::~ContentsFogWallRenderer()
{
}

void ContentsFogWallRenderer::Start()
{
	GameEngineRenderer::Start();

	GameEngineRenderer::SetMesh("Rect");

	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
	Unit->SetMaterial("FogWall");

	DefalutRenderPathValue = RenderPath::Alpha;

	Unit->Camerapushback(DefalutRenderPathValue);



	Unit->ShaderResHelper.SetTexture("DiffuseTexture", GameEngineTexture::Find("FogWall.dds"));
	Unit->ShaderResHelper.SetSampler("WrapSampler", "EngineBaseWRAPSampler");
	Unit->ShaderResHelper.SetSampler("ClampSampler", "EngineBaseSampler");
	Unit->ShaderResHelper.SetConstantBufferLink("FogWallInfo", FogWallInfoValue);

	MainFogWall = this;
}

void ContentsFogWallRenderer::Update(float _Delta)
{

	GameEngineRenderer::Update(_Delta);

	FogWallInfoValue.frameTime += _Delta * TimeScale;

	if (FogWallInfoValue.frameTime > 1000.0f)
	{
		FogWallInfoValue.frameTime -= 1000.0f;
	}
}

