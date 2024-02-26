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
	Walk,
	Walk3,
	Run,
	Run3,
	Attack1,	// Pike1
	Attack2,	// Pike1 - Pike2
	Attack3,	// Pike1 - Swing	// ��︮�� �ʴ� �޺�, �ٽ� Ȯ���غ���.
	Attack4,	// RunToPike
	Attack5,	// Swing
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
	Guard,			// ������� �ִϸ��̼� �ٽ� ã�ƾߵ�.
	GuardBreak,		// â�� �ִϸ��̼� ���� ������.
	AttackFail,
	Parrying,
	Hit,
	HitToDeath,
	BackAttackHit,
	Death,
	Max,
};

// ���� : 
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

protected:
	Enum_HollowSoldier_Spear_State SpearState = Enum_HollowSoldier_Spear_State::Max;

	void ChangeState(Enum_HollowSoldier_Spear_State _State);
	void StateUpdate(float _Delta);

	void ChangeAttackState();

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

	void State_Walk_Start();
	void State_Walk_Update(float _Delta);

	void State_Walk3_Start();
	void State_Walk3_Update(float _Delta);

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

