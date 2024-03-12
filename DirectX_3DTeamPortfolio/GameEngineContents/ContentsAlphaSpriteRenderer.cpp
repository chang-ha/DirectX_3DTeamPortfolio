#include "PreCompile.h"
#include "ContentsAlphaSpriteRenderer.h"

ContentsAlphaSpriteRenderer::ContentsAlphaSpriteRenderer() 
{
}

ContentsAlphaSpriteRenderer::~ContentsAlphaSpriteRenderer()
{
}

void ContentsAlphaSpriteRenderer::Start()
{
	DefalutRenderPathValue = RenderPath::Alpha;

	SpriteRendererInfoValue.BlackAlpha = 1.0f;

	GameEngineSpriteRenderer::Start();
}

