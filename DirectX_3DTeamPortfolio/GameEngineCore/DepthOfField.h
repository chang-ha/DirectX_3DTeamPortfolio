#pragma once
#include "GAMEENGINERENDERTARGET.H"
// Ό³Έν :
class DepthOfField : public Effect
{
public:
	// constrcuter destructer
	DepthOfField();
	~DepthOfField();

	// delete Function
	DepthOfField(const DepthOfField& _Other) = delete;
	DepthOfField(DepthOfField&& _Other) noexcept = delete;
	DepthOfField& operator=(const DepthOfField& _Other) = delete;
	DepthOfField& operator=(DepthOfField&& _Other) noexcept = delete;

	void Init(std::shared_ptr<GameEngineCamera> _Camera);

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	std::shared_ptr<GameEngineRenderTarget> BlurTarget = nullptr;


	GameEngineRenderUnit DepthOfFieldUnit;

};

