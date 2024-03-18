#include "PreCompile.h"
#include "UIGaugeRenderer.h"
//
//UIGaugeRenderer::UIGaugeRenderer()
//{
//}
//
//UIGaugeRenderer::~UIGaugeRenderer()
//{
//}
//
//void UIGaugeRenderer::Start()
//{
//	GameEngineRenderer::Start();
//
//	ImageTransform.SetParent(Transform);
//
//	GameEngineRenderer::SetMesh("Rect");
//
//}
//
//void UIGaugeRenderer::Update(float _Delta)
//{
//	if (true == IsImageSize)
//	{
//		float4 Scale = float4(CurSprite.GetScale());
//		Scale.Z = 1.0f;
//		Scale.W = 0.0f;
//		SetImageScale(Scale * AutoScaleRatio);
//	}
//
//	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();
//}
//
//void UIGaugeRenderer::SetImageScale(const float4& _Scale)
//{
//	ImageTransform.SetLocalScale(_Scale);
//}
//
//void UIGaugeRenderer::AddImageScale(const float4& _Scale)
//{
//	ImageTransform.AddLocalScale(_Scale);
//}
//
//
//void UIGaugeRenderer::Render(GameEngineCamera* _Camera, float _Delta)
//{
//	float4 ParentScale = Transform.GetLocalScale();
//	float4 Scale = ImageTransform.GetLocalScale();
//
//	float4 CalPivot = Pivot;
//	CalPivot.X -= 0.5f;
//	CalPivot.Y -= 0.5f;
//
//	float4 PivotPos;
//	PivotPos.X = Scale.X * CalPivot.X;
//	PivotPos.Y = Scale.Y * CalPivot.Y;
//
//	ImageTransform.SetLocalPosition(PivotPos);
//
//	ImageTransform.TransformUpdate();
//	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
//
//	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture, IsUserSampler);
//}
//
//void UIGaugeRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
//{
//	Sprite = GameEngineSprite::Find(_Name);
//
//	if (nullptr == Sprite)
//	{
//		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
//	}
//
//	CurSprite = Sprite->GetSpriteData(index);
//	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
//}
//
//void UIGaugeRenderer::AutoSpriteSizeOn()
//{
//	IsImageSize = true;
//}
//
//void UIGaugeRenderer::AutoSpriteSizeOff()
//{
//	IsImageSize = false;
//}
//
//void UIGaugeRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
//{
//	const TransformData& Data = ImageTransform.GetConstTransformDataRef();
//	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.SpritePivot);
//	GetShaderResHelper().SetConstantBufferLink("GaugeInfo", GaugeInfoValue);
//	SetSprite("NSet.png");
//}
//
//GameEngineSpriteRenderer::GameEngineSpriteRenderer()
//{
//}
//
//GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
//{
//}
//
//void GameEngineSpriteRenderer::Start()
//{
//	GameEngineRenderer::Start();
//
//	ImageTransform.SetParent(Transform);
//
//	GameEngineRenderer::SetMesh("Rect");
//	GameEngineRenderer::SetMaterial("2DTexture");
//}
//
//void GameEngineSpriteRenderer::Update(float _Delta)
//{
//	if (true == IsImageSize)
//	{
//		float4 Scale = float4(CurSprite.GetScale());
//		Scale.Z = 1.0f;
//		Scale.W = 0.0f;
//		SetImageScale(Scale * AutoScaleRatio);
//	}
//
//	RenderBaseInfoValue.RenderScreenScale = CurSprite.GetScale();
//
//	ImageTransform.TransformUpdate();
//
//	Transform.CalculationViewAndProjection(GetCamera()->Transform.GetConstTransformDataRef());
//	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
//
//	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture, IsUserSampler);
//}
//
//void GameEngineSpriteRenderer::SetImageScale(const float4& _Scale)
//{
//	ImageTransform.SetLocalScale(_Scale);
//}
//
//void GameEngineSpriteRenderer::AddImageScale(const float4& _Scale)
//{
//	ImageTransform.AddLocalScale(_Scale);
//}
//
//void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int index /*= 0*/)
//{
//	Sprite = GameEngineSprite::Find(_Name);
//	if (nullptr == Sprite)
//	{
//		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
//	}
//
//	CurSprite = Sprite->GetSpriteData(index);
//	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
//}
//
//void GameEngineSpriteRenderer::AutoSpriteSizeOn()
//{
//	IsImageSize = true;
//}
//
//void GameEngineSpriteRenderer::AutoSpriteSizeOff()
//{
//	IsImageSize = false;
//}
//
//void GameEngineSpriteRenderer::SetMaterialEvent(std::string_view _Name, int _Index)
//{
//	GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);
//	GetShaderResHelper().SetConstantBufferLink("ColorData", ColorDataValue);
//	SetSprite("NSet.png");
//}
//
//void GameEngineSpriteRenderer::SetMaskTexture(std::string_view _Texture, MaskMode _Mask)
//{
//	//std::shared_ptr<GameEngineFrameAnimation> TempCurFrameAnimation = CurFrameAnimations;
//	//std::shared_ptr<GameEngineSprite> TempSprite = Sprite;
//	//SpriteData TempCurSprite = CurSprite;
//
//	//GameEngineRenderer::SetMaterial("2DTextureMask");
//
//	//if (CurFrameAnimations != TempCurFrameAnimation)
//	//{
//	//	CurFrameAnimations = TempCurFrameAnimation;
//	//}
//
//	//if (Sprite != TempSprite)
//	//{
//	//	Sprite = TempSprite;
//	//	CurSprite = TempCurSprite;
//	//}
//
//	RenderBaseInfoValue.IsMask = 1;
//	RenderBaseInfoValue.MaskMode = static_cast<int>(_Mask);
//	GetShaderResHelper().SetTexture("MaskTex", _Texture);
//	std::shared_ptr<GameEngineTexture> Ptr = GameEngineTexture::Find(_Texture);
//	RenderBaseInfoValue.MaskScreeneScale = Ptr->GetScale();
//}
//
//void GameEngineSpriteRenderer::BillboardUpdate(float4 _CameraRotation)
//{
//
//	//ImageTransform.SetWorldRotation(_CameraRotation);
//	Transform.SetWorldRotation(_CameraRotation);
//
//}
//
//void GameEngineSpriteRenderer::SetSampler(std::string_view _Name)
//{
//	std::shared_ptr<GameEngineRenderUnit> Unit = CreateAndFindRenderUnit(0);
//	Unit->ShaderResHelper.SetSampler("DiffuseTexSampler", _Name);
//	IsUserSampler = false;
//}