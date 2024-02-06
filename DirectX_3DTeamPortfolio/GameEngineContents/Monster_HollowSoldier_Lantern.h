#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Lantern_State
{
	Idle,
	LanternIdle,
	//Walk,
	//Run,
	Scout,
	AwakeHollows,
	//---- Attack
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_RunToSlash,
	AttackFail,
	Parrying,
	Hit,
	HitToDeath,
	BackAttackHit,
	Death,
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier_Lantern : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Lantern();
	~Monster_HollowSoldier_Lantern();

	// delete Function
	Monster_HollowSoldier_Lantern(const Monster_HollowSoldier_Lantern & _Other) = delete;
	Monster_HollowSoldier_Lantern(Monster_HollowSoldier_Lantern && _Other) noexcept = delete;
	Monster_HollowSoldier_Lantern& operator=(const Monster_HollowSoldier_Lantern & _Other) = delete;
	Monster_HollowSoldier_Lantern& operator=(Monster_HollowSoldier_Lantern && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:


protected:
	Enum_HollowSoldier_Lantern_State LanternState = Enum_HollowSoldier_Lantern_State::Max;

	void ChangeState(Enum_HollowSoldier_Lantern_State _State);
	void StateUpdate(float _Delta);

protected:
	void State_Idle_Start();
	void State_Idle_Update(float _Delta);

	void State_LanternIdle_Start();
	void State_LanternIdle_Update(float _Delta);

	//void State_Walk_Start();
	//void State_Walk_Update(float _Delta);

	//void State_Run_Start();
	//void State_Run_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_AwakeHollows_Start();
	void State_AwakeHollows_Update(float _Delta);

	void State_RH_VerticalSlash_Start();
	void State_RH_VerticalSlash_Update(float _Delta);

	void State_RH_HorizontalSlash_Start();
	void State_RH_HorizontalSlash_Update(float _Delta);

	void State_RH_ComboAttack_Start();
	void State_RH_ComboAttack_Update(float _Delta);

	void State_RH_RunToSlash_Start();
	void State_RH_RunToSlash_Update(float _Delta);

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

