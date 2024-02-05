#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

// Ό³Έν :
class LUTEffect : public Effect
{
public:
	// constrcuter destructer
	LUTEffect();
	~LUTEffect();

	// delete Function
	LUTEffect(const LUTEffect& _Other) = delete;
	LUTEffect(LUTEffect&& _Other) noexcept = delete;
	LUTEffect& operator=(const LUTEffect& _Other) = delete;
	LUTEffect& operator=(LUTEffect&& _Other) noexcept = delete;

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

};

