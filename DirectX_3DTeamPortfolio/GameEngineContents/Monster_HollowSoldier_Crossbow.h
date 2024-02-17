#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Crossbow_State
{
	Idle,
	Idle2,
	//Walk,
	//Run,
	Scout,
	Fire,
	Sit_Fire,
	Hit,
	HitToDeath,
	Death,
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier_Crossbow : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Crossbow();
	~Monster_HollowSoldier_Crossbow();

	// delete Function
	Monster_HollowSoldier_Crossbow(const Monster_HollowSoldier_Crossbow & _Other) = delete;
	Monster_HollowSoldier_Crossbow(Monster_HollowSoldier_Crossbow && _Other) noexcept = delete;
	Monster_HollowSoldier_Crossbow& operator=(const Monster_HollowSoldier_Crossbow & _Other) = delete;
	Monster_HollowSoldier_Crossbow& operator=(Monster_HollowSoldier_Crossbow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

protected:
	Enum_HollowSoldier_Crossbow_State CrossbowState = Enum_HollowSoldier_Crossbow_State::Max;

	void ChangeState(Enum_HollowSoldier_Crossbow_State _State);
	void StateUpdate(float _Delta);

protected:
	// State Function

	void State_Idle_Start();
	void State_Idle_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);
	
	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_Fire_Start();
	void State_FIre_Update(float _Delta);

	void State_Sit_Fire_Start();
	void State_Sit_Fire_Update(float _Delta);

	void State_Hit_Start();
	void State_Hit_Update(float _Delta);

	void State_HitToDeath_Start();
	void State_HitToDeath_Update(float _Delta);

	void State_Death_Start();
	void State_Death_Update(float _Delta);
};

