#pragma once

enum class Enum_EquipType
{
	None,
	Magic,
	Shield,
	Sword,
	Este
};

#include <GameEngineCore/GameEngineActor.h>
// Ό³Έν :
class UIEquipFrame : public GameEngineActor
{
public:
	// constructer destructer
	UIEquipFrame();
	~UIEquipFrame();

	// delete Function
	UIEquipFrame(const UIEquipFrame& _Other) = delete;
	UIEquipFrame(UIEquipFrame&& _Other) noexcept = delete;
	UIEquipFrame& operator = (const UIEquipFrame& _Other) = delete;
	UIEquipFrame& operator = (UIEquipFrame&& _Other) noexcept = delete;

	void SetEquipType(Enum_EquipType _Type)
	{
		Type = _Type;
	}

	void SetEquipSprite(Enum_EquipType _Type);

protected:
	void Start() override;

	void Release() override;

private:
	std::shared_ptr<GameEngineUIRenderer> Equip_Frame;
	Enum_EquipType Type = Enum_EquipType::None;
	std::shared_ptr<GameEngineUIRenderer> Equip;

	float4 FrameScale = 0.0f;
	float4 FixPos = 0.0f;
};