#include "PreCompile.h"
#include "ContentsHitRenderer.h"

ContentsHitRenderer::ContentsHitRenderer() 
{
}

ContentsHitRenderer::~ContentsHitRenderer()
{
}

void ContentsHitRenderer::Start()
{
	ContentsAlphaSpriteRenderer::Start();

	SetBillboardOn(); 
	AutoSpriteSizeOn();

	CreateAnimation("Hit", "Hit.dds", 0.0666f, -1, -1);

	ChangeAnimation("Hit", true);

	SetEndEvent("Hit", [](GameEngineSpriteRenderer* _Render) {
		_Render->Off();
		});

	//Off();
}

