#pragma once
#include <GameEngineCore/GAMEENGINERENDERTARGET.H>

struct LutInfo 
{
	float Lutweight;
	float Def1;
	float Def2;
	float Def3;
};

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

	static std::vector<std::string> LUTNames;
	static LutInfo MainLutInfoValue;
	static void Load();

	static void SetCurLUTNameValue(std::string_view _str)
	{
		CurLUTNameValue = _str;
	}

protected:

private:
	void Start() override;
	void EffectProcess(float _DeltaTime) override;

	static std::string CurLUTNameValue;

};

