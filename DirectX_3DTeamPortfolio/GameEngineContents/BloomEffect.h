#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct BloomInfo
{
	float Threshold = 0.0f;
	float Def1;
	float Def2;
	float Def3;
};

// Ό³Έν :
class BloomEffect : public Effect
{
public:
	// constrcuter destructer
	BloomEffect();
	~BloomEffect();

	static BloomInfo BloomInfoValue;

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

