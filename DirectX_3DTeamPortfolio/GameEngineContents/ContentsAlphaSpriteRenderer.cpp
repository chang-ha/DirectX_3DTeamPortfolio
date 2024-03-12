#include "PreCompile.h"
#include "ContentsAlphaSpriteRenderer.h"

ContentsAlphaSpriteRenderer::ContentsAlphaSpriteRenderer() 
{
}

ContentsAlphaSpriteRenderer::~ContentsAlphaSpriteRenderer()
{
}

void ContentsAlphaSpriteRenderer::Load()
{
	{
		// Fire 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Effect");
		Dir.MoveChild("Candle");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Files[i].GetStringPath());
		}


		GameEngineSprite::CreateCut("CandleFire.dds", 8, 4);
		GameEngineSprite::CreateCut("CandleFire2.dds", 8, 4);
	}

	{
		// Fire 로드
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("Effect");
		Dir.MoveChild("Hit");
		std::vector<GameEngineFile> Files = Dir.GetAllFile();

		for (size_t i = 0; i < Files.size(); i++)
		{
			std::shared_ptr<GameEngineTexture> Texture = GameEngineTexture::Load(Files[i].GetStringPath());
		}


		GameEngineSprite::CreateCut("Hit.dds", 4, 2);
	}
}

void ContentsAlphaSpriteRenderer::Start()
{
	DefalutRenderPathValue = RenderPath::Alpha;

	SpriteRendererInfoValue.BlackAlpha = 1.0f;

	GameEngineSpriteRenderer::Start();
}

