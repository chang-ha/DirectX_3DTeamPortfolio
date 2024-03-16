#pragma once
#include "UIEquipFrame.h"

#include <GameEngineCore/GameEngineActor.h>
// 설명 :
class UIPlayerEquip : public GameEngineActor
{
public:
	// constructer destructer
	UIPlayerEquip();
	~UIPlayerEquip();

	// delete Function
	UIPlayerEquip(const UIPlayerEquip& _Other) = delete;
	UIPlayerEquip(UIPlayerEquip&& _Other) noexcept = delete;
	UIPlayerEquip& operator = (const UIPlayerEquip& _Other) = delete;
	UIPlayerEquip& operator = (UIPlayerEquip&& _Other) noexcept = delete;

	UIEquipFrame* CreatEquipActor(Enum_EquipType _Type);

	UIEquipFrame* FindFrame(Enum_EquipType _Type);

	void SetParent(class Player* _Object);

protected:
	void Start() override;
	void Update(float _Delta);

	void Release() override;

private:
	// 플레이어에게서 받아올 값
	Player* MaxEsteCheck = nullptr;

	std::map<Enum_EquipType, class UIEquipFrame*> EquipMent;

	UIEquipFrame* MagicFrame = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Sword;
	UIEquipFrame* SwordFrame = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Shield;
	UIEquipFrame* ShieldFrame = nullptr;

	void ChangeEsteImage();
	std::shared_ptr<GameEngineUIRenderer> Este;
	std::shared_ptr<GameEngineUIRenderer> EsteBack;
	std::shared_ptr<GameEngineUIRenderer> Equip_Este_Sub;
	UIEquipFrame* EsteFrame = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> EsteFont;
	std::shared_ptr<class GameEngineUIRenderer> EsteCount;
	int MaxEsteCount = 0; // 5;
	int CurEsteCount = 5;
	double StandardEste = 0;

	// EquipFrame 중심 위치값
	float4 FixPos = 0.0f;
};

