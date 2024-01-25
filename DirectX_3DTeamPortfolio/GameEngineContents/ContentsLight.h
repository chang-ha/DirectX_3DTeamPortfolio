#pragma once
#include <GameEngineCore/GameEngineLight.h>


enum class Enum_LightType
{
	Directional,
	Point,
	//Spot
};

// Ό³Έν :
class ContentsLight : public GameEngineLight
{
public:
	// constrcuter destructer
	ContentsLight();
	~ContentsLight();

	// delete Function
	ContentsLight(const ContentsLight& _Other) = delete;
	ContentsLight(ContentsLight&& _Other) noexcept = delete;
	ContentsLight& operator=(const ContentsLight& _Other) = delete;
	ContentsLight& operator=(ContentsLight&& _Other) noexcept = delete;

	bool IsDebugValue = false;

	inline void SetLightType(Enum_LightType _Type)
	{
		LightData Data = GetLightData();

		Data.LightType = static_cast<int>(_Type);

		SetLightData(Data);
	}

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:

};

