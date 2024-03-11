#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Spear_State
{
	Idle1,
	Idle2,
	Idle3,
	Idle2ToIdle1,
	Idle1ToIdle2,
	Idle2ToIdle3,
	Idle3ToIdle2,
	Scout,
	Walk_Front2,
	Walk_Back2,
	Walk_Left2,
	Walk_Right2,
	Walk_Front3,
	Walk_Back3,
	Walk_Left3,
	Walk_Right3,
	Run,
	Run3,
	Attack1,	// Pike1
	Attack2,	// Pike1 - Pike2
	Attack3,	// Pike1 - Swing	// 어울리지 않는 콤보, 다시 확인해볼것.
	Attack4,	// StepAndPike
	Attack5,	// Swing
	Attack6,	// Swing - Pike1
	RunToPike,
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
	Guard,			// 여기부터 애니메이션 다시 찾아야됨.
	GuardBreak,		// 창병 애니메이션 따로 존재함.
	AttackFail,
	Parrying,
	Hit_Front,
	Hit_Back,
	Hit_Left,
	Hit_Right,
	HitToDeath,
	BackAttackHit,
	Death,
	Max,
};

// 설명 : 
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

	void SetStateIdle1()
	{
		ChangeState(Enum_HollowSoldier_Spear_State::Idle1);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	float StateTime = 0.0f;

	bool IsAttack = false;

	float WalkToChangeTime = 0.0f;
	float WalkTime = 0.0f;

protected:
	Enum_HollowSoldier_Spear_State SpearState = Enum_HollowSoldier_Spear_State::Max;

	void ChangeState(Enum_HollowSoldier_Spear_State _State);
	void StateUpdate(float _Delta);

	void ChangeAttackState();

	void ChangeHitState();

protected:
	// State Function
	
	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);

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

	void State_Walk_Front2_Start();
	void State_Walk_Front2_Update(float _Delta);

	void State_Walk_Back2_Start();
	void State_Walk_Back2_Update(float _Delta);

	void State_Walk_Left2_Start();
	void State_Walk_Left2_Update(float _Delta);

	void State_Walk_Right2_Start();
	void State_Walk_Right2_Update(float _Delta);

	void State_Walk_Front3_Start();
	void State_Walk_Front3_Update(float _Delta);

	void State_Walk_Back3_Start();
	void State_Walk_Back3_Update(float _Delta);

	void State_Walk_Left3_Start();
	void State_Walk_Left3_Update(float _Delta);

	void State_Walk_Right3_Start();
	void State_Walk_Right3_Update(float _Delta);

	void State_Run_Start();
	void State_Run_Update(float _Delta);

	void State_Run3_Start();
	void State_Run3_Update(float _Delta);

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

	void State_RunToPike_Start();
	void State_RunToPike_Update(float _Delta);

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

	void State_Hit_Front_Start();
	void State_Hit_Front_Update(float _Delta);

	void State_Hit_Back_Start();
	void State_Hit_Back_Update(float _Delta);

	void State_Hit_Left_Start();
	void State_Hit_Left_Update(float _Delta);

	void State_Hit_Right_Start();
	void State_Hit_Right_Update(float _Delta);

	void State_HitToDeath_Start();
	void State_HitToDeath_Update(float _Delta);

	void State_BackAttackHit_Start();
	void State_BackAttackHit_Update(float _Delta);

	void State_Death_Start();
	void State_Death_Update(float _Delta);
};

