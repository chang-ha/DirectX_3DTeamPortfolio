#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_RoundShield_State
{
	Idle1,
	Idle2,
	Idle3,	// GuardOn
	Idle2ToIdle1,
	Idle1ToIdle2,
	Idle2ToIdle3,
	Idle3ToIdle2,
	Scout,
	Walk,
	Walk3,
	Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
	Attack1,
	Attack2,
	Attack3,
	Attack4,
	Attack5,
	Attack6,
	Attack7,
	Turn_Left2,
	Turn_Right2,
	Turn_Left_Twice2,
	Turn_Right_Twice2,
	Turn_Left1,
	Turn_Right1,
	Turn_Left_Twice1,
	Turn_Right_Twice1,
	Turn_Left3,
	Turn_Right3,
	Turn_Left_Twice3,
	Turn_Right_Twice3,
	Guard,	// 공격 막힘
	GuardBreak,
	AttackFail,
	Parrying,
	Hit,
	HitToDeath,
	BackAttackHit,
	Death,
	Max,
	
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

	void SetStateIdle3()
	{
		ChangeState(Enum_HollowSoldier_RoundShield_State::Idle3);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	float StateTime = 0.0f;
	int AttackPattern = 0;
	
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

	void State_Idle2ToIdle1_Start();
	void State_Idle2ToIdle1_Update(float _Delta);

	void State_Idle1ToIdle2_Start();
	void State_Idle1ToIdle2_Update(float _Delta);

	void State_Idle2ToIdle3_Start();
	void State_Idle2ToIdle3_Update(float _Delta);

	void State_Idle3ToIdle2_Start();
	void State_Idle3ToIdle2_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_Walk_Start();
	void State_Walk_Update(float _Delat);

	void State_Walk3_Start();
	void State_Walk3_Update(float _Delat);

	void State_Run_Start();
	void State_Run_Update(float _Delta);

	void State_RH_VerticalSlash_Start();
	void State_RH_VerticalSlash_Update(float _Delta);

	void State_RH_HorizontalSlash_Start();
	void State_RH_HorizontalSlash_Update(float _Delta);

	void State_RH_ComboAttack_Start();
	void State_RH_ComboAttack_Update(float _Delta);

	void State_RH_TwinSlash_Start();
	void State_RH_TwinSlash_Update(float _Delta);

	void State_Attack1_Start();
	void State_Attack1_Update(float _Delta);

	void State_Attack2_Start();
	void State_Attack2_Update(float _Delta);

	void State_Attack3_Start();
	void State_Attack3_Update(float _Delta);

	void State_Attack4_Start();
	void State_Attack4_Update(float _Delta);

	void State_Attack5_Start();
	void State_Attack5_Update(float _Delta);

	void State_Attack6_Start();
	void State_Attack6_Update(float _Delta);

	void State_Attack7_Start();
	void State_Attack7_Update(float _Delta);

	void State_Turn_Left2_Start();
	void State_Turn_Left2_Update(float _Delta);

	void State_Turn_Right2_Start();
	void State_Turn_Right2_Update(float _Delta);

	void State_Turn_Left_Twice2_Start();
	void State_Turn_Left_Twice2_Update(float _Delta);

	void State_Turn_Right_Twice2_Start();
	void State_Turn_Right_Twice2_Update(float _Delta);

	void State_Turn_Left1_Start();
	void State_Turn_Left1_Update(float _Delta);

	void State_Turn_Right1_Start();
	void State_Turn_Right1_Update(float _Delta);

	void State_Turn_Left_Twice1_Start();
	void State_Turn_Left_Twice1_Update(float _Delta);

	void State_Turn_Right_Twice1_Start();
	void State_Turn_Right_Twice1_Update(float _Delta);

	void State_Turn_Left3_Start();
	void State_Turn_Left3_Update(float _Delta);

	void State_Turn_Right3_Start();
	void State_Turn_Right3_Update(float _Delta);

	void State_Turn_Left_Twice3_Start();
	void State_Turn_Left_Twice3_Update(float _Delta);

	void State_Turn_Right_Twice3_Start();
	void State_Turn_Right_Twice3_Update(float _Delta);

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

