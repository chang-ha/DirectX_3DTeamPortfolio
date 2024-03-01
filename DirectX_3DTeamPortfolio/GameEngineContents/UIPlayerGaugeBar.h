#pragma once
#include "UIUnit.h"
//enum class Enum_BarType
//{
//	None,
//	Hp,
//	Mp,
//	Stamina
//};


#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class UIPlayerGaugeBar : public GameEngineActor
{
public:
	// constructer destructer
	UIPlayerGaugeBar();
	~UIPlayerGaugeBar();

	// delete Function
	UIPlayerGaugeBar(const UIPlayerGaugeBar& _Other) = delete;
	UIPlayerGaugeBar(UIPlayerGaugeBar&& _Other) noexcept = delete;
	UIPlayerGaugeBar& operator = (const UIPlayerGaugeBar& _Other) = delete;
	UIPlayerGaugeBar& operator = (UIPlayerGaugeBar&& _Other) noexcept = delete;

	UIUnit* CreateBarActor(Enum_BarType _Type, float _TotalSize);
	//void CreateBarActor(Enum_BarType _Type);
	UIUnit* FindBar(Enum_BarType _Type);

	void FindAndSetGauge(Enum_BarType _Type, float _Value);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

private:
	std::map<Enum_BarType, class UIUnit*> GaugeBars;

	UIUnit* HpBar = nullptr;
	UIUnit* MpBar = nullptr;
	UIUnit* StaminaBar = nullptr;

};