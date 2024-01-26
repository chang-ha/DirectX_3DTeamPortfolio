#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Sword_State
{
	Idle1,
	Idle2,
	Scout,
	//Walk,
	//Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
	AttackFail,
	Parrying,
	Hit,
	HitToDeath,
	BackAttackHit,
	Death,
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier_Sword : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Sword();
	~Monster_HollowSoldier_Sword();

	// delete Function
	Monster_HollowSoldier_Sword(const Monster_HollowSoldier_Sword & _Other) = delete;
	Monster_HollowSoldier_Sword(Monster_HollowSoldier_Sword && _Other) noexcept = delete;
	Monster_HollowSoldier_Sword& operator=(const Monster_HollowSoldier_Sword & _Other) = delete;
	Monster_HollowSoldier_Sword& operator=(Monster_HollowSoldier_Sword && _Other) noexcept = delete;

	void SetStateIdle1()
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle1);
	}

	void SetStateIdle2()
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Idle2);
	}

	void SetStateScout()
	{
		ChangeState(Enum_HollowSoldier_Sword_State::Scout);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	float StateTime = 0.0f;

protected:
	Enum_HollowSoldier_Sword_State SoldierState = Enum_HollowSoldier_Sword_State::Max;

	void ChangeState(Enum_HollowSoldier_Sword_State _State);
	void StateUpdate(float _Delta);

protected:
	//State Function

	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_RH_VerticalSlash_Start();
	void State_RH_VerticalSlash_Update(float _Delta);

	void State_RH_HorizontalSlash_Start();
	void State_RH_HorizontalSlash_Update(float _Delta);

	void State_RH_ComboAttack_Start();
	void State_RH_ComboAttack_Update(float _Delta);

	void State_RH_TwinSlash_Start();
	void State_RH_TwinSlash_Update(float _Delta);

	void State_AttackFail_Start();
	void State_AttackFail_Update(float _Delta);

	void State_Parrying_Start();
	void State_Parrying_Update(float _Delta);

	void State_Hit_Start();
	void State_Hit_Update(float _Delta);

	void State_HitToDeath_Start();
	void State_HitToDeath_Update(float _Delta);

	void State_BackAttackHit_Start();
	void State_BackAttackHit_Update(float _Delta);

	void State_Death_Start();
	void State_Death_Update(float _Delta);
};

