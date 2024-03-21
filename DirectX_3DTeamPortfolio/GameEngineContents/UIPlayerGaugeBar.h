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

	void Init(class Player* _PlayerObject);
	UIUnit* CreateBarActor(Enum_BarType _Type, float _TotalSize, Player* _PlayerObject);
	UIUnit* FindBar(Enum_BarType _Type);

	void FindAndSetGauge(Enum_BarType _Type, float _Value);

	void Emeber();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

private:
	Player* pPlayer = nullptr;
	std::map<Enum_BarType, class UIUnit*> GaugeBars;

	UIUnit* HpBar = nullptr;
	UIUnit* MpBar = nullptr;
	UIUnit* StaminaBar = nullptr;

	//// PlayerIcon
	std::shared_ptr<GameEngineUIRenderer> PlayerIcon;

};