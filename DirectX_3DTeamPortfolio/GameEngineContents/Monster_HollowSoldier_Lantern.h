#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Lantern_State
{
	Stay,
	Idle,
	IdleToStay,
	StayToIdle,
	Walk_Front,
	Walk_Back,
	Walk_Left,
	Walk_Right,
	Run,
	Scout,
	AwakeHollows,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	TH_VerticalSlash,
	RH_ComboAttack,
	RH_RunToSlash,
	Scout_Turn_Left_Twice,
	Turn_Left,
	Turn_Right,
	Turn_Left_Twice,
	Turn_Right_Twice,
	AttackFail,
	Parrying,
	Hit_Front,
	Hit_Back,
	Hit_Left,
	Hit_Right,
	HitToDeath,
	BackAttackHit,
	BackAttackDeath,
	AfterGuardBreakHit,
	AfterGuardBreakDeath,
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

	void SetStateStay()
	{
		ChangeState(Enum_HollowSoldier_Lantern_State::Stay);
	}

	void WakeUp() override;

	void Reset() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}
private:
	float StateTime = 0.0f;

	bool IsAttack = false;

	float WalkToChangeTime = 0.0f;
	float WalkTime = 0.0f;

	float ScoutTime = 0.0f;

	bool AwakeValue = false;

protected:
	Enum_HollowSoldier_Lantern_State LanternState = Enum_HollowSoldier_Lantern_State::Max;
	std::shared_ptr<GameEngineCollision> AwakeCollision;

	void ChangeState(Enum_HollowSoldier_Lantern_State _State);
	void StateUpdate(float _Delta);

	void ChangeAttackState();

	void ChangeHitState();

	std::shared_ptr<GameEngineCollision> SwordCollision;
	Monster_HitInteraction Sword;

protected:
	void State_Stay_Start();
	void State_Stay_Update(float _Delta);

	void State_Idle_Start();
	void State_Idle_Update(float _Delta);

	void State_IdleToStay_Start();
	void State_IdleToStay_Update(float _Delta);

	void State_StayToIdle_Start();
	void State_StayToIdle_Update(float _Delta);

	void State_Walk_Front_Start();
	void State_Walk_Front_Update(float _Delta);

	void State_Walk_Back_Start();
	void State_Walk_Back_Update(float _Delta);

	void State_Walk_Left_Start();
	void State_Walk_Left_Update(float _Delta);

	void State_Walk_Right_Start();
	void State_Walk_Right_Update(float _Delta);

	void State_Run_Start();
	void State_Run_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_AwakeHollows_Start();
	void State_AwakeHollows_Update(float _Delta);

	void State_RH_VerticalSlash_Start();
	void State_RH_VerticalSlash_Update(float _Delta);

	void State_RH_HorizontalSlash_Start();
	void State_RH_HorizontalSlash_Update(float _Delta);

	void State_TH_VerticalSlash_Start();
	void State_TH_VerticalSlash_Update(float _Delta);

	void State_RH_ComboAttack_Start();
	void State_RH_ComboAttack_Update(float _Delta);

	void State_RH_RunToSlash_Start();
	void State_RH_RunToSlash_Update(float _Delta);

	void State_Scout_Turn_Left_Twice_Start();
	void State_Scout_Turn_Left_Twice_Update(float _Delta);

	void State_Turn_Left_Start();
	void State_Turn_Left_Update(float _Delta);

	void State_Turn_Right_Start();
	void State_Turn_Right_Update(float _Delta);

	void State_Turn_Left_Twice_Start();
	void State_Turn_Left_Twice_Update(float _Delta);

	void State_Turn_Right_Twice_Start();
	void State_Turn_Right_Twice_Update(float _Delta);

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

	void State_BackAttackDeath_Start();
	void State_BackAttackDeath_Update(float _Delta);

	void State_AfterGuardBreakHit_Start();
	void State_AfterGuardBreakHit_Update(float _Delta);

	void State_AfterGuardBreakDeath_Start();
	void State_AfterGuardBreakDeath_Update(float _Delta);

	void State_Death_Start();
	void State_Death_Update(float _Delta);
};

