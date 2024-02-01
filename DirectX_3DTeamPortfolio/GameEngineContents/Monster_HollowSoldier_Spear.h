#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Spear_State
{
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier_Spear : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Spear();
	~Monster_HollowSoldier_Spear();

	// delete Function
	Monster_HollowSoldier_Spear(const Monster_HollowSoldier_Spear & _Other) = delete;
	Monster_HollowSoldier_Spear(Monster_HollowSoldier_Spear && _Other) noexcept = delete;
	Monster_HollowSoldier_Spear& operator=(const Monster_HollowSoldier_Spear & _Other) = delete;
	Monster_HollowSoldier_Spear& operator=(Monster_HollowSoldier_Spear && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

protected:
	Enum_HollowSoldier_Spear_State SpearState = Enum_HollowSoldier_Spear_State::Max;

	void ChangeState(Enum_HollowSoldier_Spear_State _State);
	void StateUpdate(float _Delta);

protected:
	// State Function
};

