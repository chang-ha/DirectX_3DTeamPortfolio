#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Spear_State
{
	Idle1,
	Idle2,
	Idle3,
	//Walk,
	//Run,
	Scout,
	Attack1,	// Pike1
	Attack2,	// Pike1 - Pike2
	Attack3,	// Pike1 - Swing	// 어울리지 않는 콤보, 다시 확인해볼것.
	Attack4,	// RunToPike
	Attack5,	// Swing
	Guard,			// 여기부터 애니메이션 다시 찾아야됨.
	GuardBreak,		// 창병 애니메이션 따로 존재함.
	AttackFail,
	Parrying,
	Hit,
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
	
	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);

	void State_Idle3_Start();
	void State_Idle3_Update(float _Delta);

	//void State_Walk_Start();
	//void State_Walk_Update(float _Delta);

	//void State_Run_Start();
	//void State_Run_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

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

