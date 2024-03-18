#pragma once

struct FadeInfo
{
public:
	float4 FadeColor = float4::ZERO;
	float Ratio = 0.0f;
	float Temp0 = 0.0f;
	float Temp1 = 0.0f;
	float Temp2 = 0.0f;
};

enum class Enum_FadeType
{
	FadeIn,
	FadeOut,
};

// Ό³Έν :
class AllFadeEffect : public Effect
{
public:
	// constrcuter destructer
	AllFadeEffect();
	~AllFadeEffect();

	// delete Function
	AllFadeEffect(const AllFadeEffect& _Other) = delete;
	AllFadeEffect(AllFadeEffect&& _Other) noexcept = delete;
	AllFadeEffect& operator=(const AllFadeEffect& _Other) = delete;
	AllFadeEffect& operator=(AllFadeEffect&& _Other) noexcept = delete;

	static void Load();

	inline void SetFadeColor(const float4& _Color = float4::ZERO) { Info.FadeColor = _Color; }
	inline void SetFadeSpeed(float _Speed) { FadeSpeed = _Speed; }

	void FadeIn();
	void FadeOut();

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

private:
	FadeInfo Info;
	Enum_FadeType Type = Enum_FadeType::FadeOut;
	float FadeSpeed = 0.0f;

};
