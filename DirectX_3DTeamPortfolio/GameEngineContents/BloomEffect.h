#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

// ���� :
class BloomEffect : public Effect
{
public:
	// constrcuter destructer
	BloomEffect();
	~BloomEffect();

	// delete Function
	BloomEffect(const BloomEffect& _Other) = delete;
	BloomEffect(BloomEffect&& _Other) noexcept = delete;
	BloomEffect& operator=(const BloomEffect& _Other) = delete;
	BloomEffect& operator=(BloomEffect&& _Other) noexcept = delete;

protected:

private:

	GameEngineRenderUnit BlurUnit;
	GameEngineRenderUnit CombineUnit;

	std::shared_ptr<GameEngineRenderTarget> BlurTarget = nullptr;
	std::shared_ptr<GameEngineRenderTarget> CombineTarget = nullptr;

	void Start() override;
	void EffectProcess(float _DeltaTime) override;

};

