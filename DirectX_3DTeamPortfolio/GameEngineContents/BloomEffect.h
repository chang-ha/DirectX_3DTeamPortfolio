#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

// Ό³Έν :
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
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

};

