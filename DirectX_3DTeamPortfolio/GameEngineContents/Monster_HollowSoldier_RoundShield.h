#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_RoundShield_State
{
	Max
};

// Ό³Έν : 
class Monster_HollowSoldier_RoundShield : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_RoundShield();
	~Monster_HollowSoldier_RoundShield();

	// delete Function
	Monster_HollowSoldier_RoundShield(const Monster_HollowSoldier_RoundShield & _Other) = delete;
	Monster_HollowSoldier_RoundShield(Monster_HollowSoldier_RoundShield && _Other) noexcept = delete;
	Monster_HollowSoldier_RoundShield& operator=(const Monster_HollowSoldier_RoundShield & _Other) = delete;
	Monster_HollowSoldier_RoundShield& operator=(Monster_HollowSoldier_RoundShield && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

	
protected:
	Enum_HollowSoldier_RoundShield_State ShieldState = Enum_HollowSoldier_RoundShield_State::Max;

	void ChangeState(Enum_HollowSoldier_RoundShield_State _State);
	void StateUpdate(float _Delta);

protected:
	
};

