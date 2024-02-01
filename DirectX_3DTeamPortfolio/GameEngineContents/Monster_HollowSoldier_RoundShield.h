#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_RoundShield_State
{
	// 확정 x
	Idle1,
	Idle2,
	Idle3,	// GuardOn
	Scout,
	//Walk,
	//Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
	Guard,	// 공격 막힘
	GuardBreak,
	AttackFail,
	Parrying,
	Hit,
	HitToDeath,
	BackAttackHit,
	Death,
	Max
};

// 설명 : 
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
	// State Function

	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delat);

	void State_Idle3_Start();
	void State_Idle3_Update(float _Delta);

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

	void State_Guard_Start();
	void State_Guard_Update(float _Delta);

	void State_GuardBreak_Start();
	void State_GuardBreak_Update(float _Delta);

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

