#pragma once

enum class Enum_BarType
{
	None,
	Hp,
	Mp,
	Stamina
};

// Ό³Έν :
class UIUnit : public GameEngineActor
{
public:
	// constructer destructer
	UIUnit();
	~UIUnit();

	// delete Function
	UIUnit(const UIUnit& _Other) = delete;
	UIUnit(UIUnit&& _Other) noexcept = delete;
	UIUnit& operator = (const UIUnit& _Other) = delete;
	UIUnit& operator = (UIUnit&& _Other) noexcept = delete;


	void SetGauge(float _Value);

	void SetTotalGauge(float _Value);

	void SetBarType(Enum_BarType _Type)
	{
		Type = _Type;
	}

	void SetBarSprite(Enum_BarType _Type);

	void SetParent(class Player* _PlayerObject);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	Player* pPlayer = nullptr;

	float PixelGauge = 0.0f;

	float RenderTotalGauge = 0.0f;
	float RenderGauge = 0.0f;
	float RenderSpeed = 200.0f;

	Enum_BarType Type = Enum_BarType::None;

	std::shared_ptr<GameEngineUIRenderer> L_Bar;
	std::shared_ptr<GameEngineUIRenderer> C_Bar;
	std::shared_ptr<GameEngineUIRenderer> R_Bar;
	std::shared_ptr<GameEngineUIRenderer> GaugeBar;

	float4 LBarScale = float4::ZERO;

};

