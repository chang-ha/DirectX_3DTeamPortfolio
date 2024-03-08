#pragma once
#include <GameEngineCore\GameEngineSpriteRenderer.h>

// Ό³Έν :
class ContentsAlphaSpriteRenderer : public GameEngineSpriteRenderer
{
public:
	// constrcuter destructer
	ContentsAlphaSpriteRenderer();
	~ContentsAlphaSpriteRenderer();

	// delete Function
	ContentsAlphaSpriteRenderer(const ContentsAlphaSpriteRenderer& _Other) = delete;
	ContentsAlphaSpriteRenderer(ContentsAlphaSpriteRenderer&& _Other) noexcept = delete;
	ContentsAlphaSpriteRenderer& operator=(const ContentsAlphaSpriteRenderer& _Other) = delete;
	ContentsAlphaSpriteRenderer& operator=(ContentsAlphaSpriteRenderer&& _Other) noexcept = delete;

protected:

	void Start() override;

private:

};

