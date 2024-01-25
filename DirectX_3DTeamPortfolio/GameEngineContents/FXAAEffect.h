#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

// Ό³Έν :
class FXAAEffect : public Effect
{
public:
	// constrcuter destructer
	FXAAEffect();
	~FXAAEffect();

	// delete Function
	FXAAEffect(const FXAAEffect& _Other) = delete;
	FXAAEffect(FXAAEffect&& _Other) noexcept = delete;
	FXAAEffect& operator=(const FXAAEffect& _Other) = delete;
	FXAAEffect& operator=(FXAAEffect&& _Other) noexcept = delete;

protected:

private:


	void Start() override;
	void EffectProcess(float _DeltaTime) override;

};

