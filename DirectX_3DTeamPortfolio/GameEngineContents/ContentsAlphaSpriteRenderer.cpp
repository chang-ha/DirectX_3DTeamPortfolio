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

	GameEngineSpriteRenderer::Start();
}

