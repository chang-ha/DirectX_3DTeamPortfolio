#include "PreCompile.h"
#include "GaugeRenderer.h"

void GaugeRenderer::MaterialLoad()
{
	std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("GaugeShader");
	Mat->SetVertexShader("GaugeShader_VS");
	Mat->SetPixelShader("GaugeShader_PS");
	Mat->SetDepthState("AlwaysDepth");
	Mat->SetRasterizer("EngineRasterizer");
}

GaugeRenderer::GaugeRenderer()
{
}

GaugeRenderer::~GaugeRenderer()
{
}

void GaugeRenderer::Start()
{
	GameEngineRenderer::Start();

	ImageTransform.SetParent(Transform);

	GameEngineRenderer::SetMesh("Rect");
	GameEngineRenderer::SetMaterial("GaugeShader");
}

void GaugeRenderer::Update(float _Delta)
{
	if (IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		SetImageScale(Scale * AutoScaleRatio);
	}

	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();

	ImageTransform.TransformUpdate();
	Transform.CalculationViewAndProjection(GetCamera()->Transform.GetConstTransformDataRef());
	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture, IsUserSampler);
}

void GaugeRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void GaugeRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}

void GaugeRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
{
	Sprite = GameEngineSprite::Find(_Name);
	if (nullptr == Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
		return;
	}

	CurSprite = Sprite->GetSpriteData(index);
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

void GaugeRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
{
	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("GaugeInfo", GaugeInfoValue);
	SetSprite("NSet.png");
}

void GaugeRenderer::BillboardUpdate(float4 _CameraRotation)
{
	Transform.SetWorldRotation(_CameraRotation);
}

void GaugeRenderer::SetGauge(float _Ratio)
{
	const float Ratio = std::clamp(_Ratio, 0.0f, 1.0f);
	GaugeInfoValue.Gauge = Ratio;
}