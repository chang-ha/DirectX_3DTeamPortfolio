#pragma once
#include "ContentsAlphaSpriteRenderer.h"

// Ό³Έν :
class ContentsHitRenderer : public ContentsAlphaSpriteRenderer
{
public:
	// constrcuter destructer
	ContentsHitRenderer();
	~ContentsHitRenderer();

	// delete Function
	ContentsHitRenderer(const ContentsHitRenderer& _Other) = delete;
	ContentsHitRenderer(ContentsHitRenderer&& _Other) noexcept = delete;
	ContentsHitRenderer& operator=(const ContentsHitRenderer& _Other) = delete;
	ContentsHitRenderer& operator=(ContentsHitRenderer&& _Other) noexcept = delete;

protected:
	void Start() override;
private:

};

