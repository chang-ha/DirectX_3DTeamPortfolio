#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Sword_State
{
	Idle1,
	Idle2,
	Idle2ToIdle1,
	Idle1ToIdle2,
	Scout,
	Walk_Front,
	Walk_Back,
	Walk_Left,
	Walk_Right,
	Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
	RH_RunToSting,
	Attack1,
	Attack2,
	Attack3,
	//Attack4,
	Attack5,
	Attack6,
	Attack7,
	Attack8,
	Attack9,
	Attack10,
	Attack11,
	//Attack12,
	Attack13,
	Turn_Left2,
	Turn_Right2,
	Turn_Left_Twice2,
	Turn_Right_Twice2,
	Turn_Left1,
	Turn_Right1,
	Turn_Left_Twice1,
	Turn_Right_Twice1,
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

	float WalkToChangeTime = 0.0f;
	float WalkTime = 0.0f;
	float ScoutTime = 0.0f;

protected:
	Enum_HollowSoldier_Sword_State SoldierState = Enum_HollowSoldier_Sword_State::Max;

	void ChangeState(Enum_HollowSoldier_Sword_State _State);
	void StateUpdate(float _Delta);

	void ChangeAttackState();

	void ChangeHitState();

	std::shared_ptr<GameEngineCollision> SwordCollision;

	Monster_HitInteraction Sword;

private:
	bool IsRecognize = false;
	bool IsAttack = false;


protected:
	//State Function

	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);

	void State_Idle1ToIdle2_Start();
	void State_Idle1ToIdle2_Update(float _Delta);

	void State_Idle2ToIdle1_Start();
	void State_Idle2ToIdle1_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

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

	void State_RH_VerticalSlash_Start();
	void State_RH_VerticalSlash_Update(float _Delta);

	void State_RH_HorizontalSlash_Start();
	void State_RH_HorizontalSlash_Update(float _Delta);

	void State_RH_ComboAttack_Start();
	void State_RH_ComboAttack_Update(float _Delta);

	void State_RH_TwinSlash_Start();
	void State_RH_TwinSlash_Update(float _Delta);

	void State_RH_RunToSting_Start();
	void State_RH_RunToSting_Update(float _Delta);

	// Vertical
	void State_Attack1_Start();
	void State_Attack1_Update(float _Delta);

	// Vertical Horizontal
	void State_Attack2_Start();
	void State_Attack2_Update(float _Delta);

	// Vertical Horizontal TH
	void State_Attack3_Start();
	void State_Attack3_Update(float _Delta);

	//void State_Attack4_Start();
	//void State_Attack4_Update(float _Delta);

	// Vertical Horizontal ChargingSting
	void State_Attack5_Start();
	void State_Attack5_Update(float _Delta);

	// Vertical TwinSlash
	void State_Attack6_Start();
	void State_Attack6_Update(float _Delta);

	// Vertical TwinSlash TH
	void State_Attack7_Start();
	void State_Attack7_Update(float _Delta);
	
	// Vertical TH
	void State_Attack8_Start();
	void State_Attack8_Update(float _Delta);

	// TwinSlash
	void State_Attack9_Start();
	void State_Attack9_Update(float _Delta);

	// TwinSlash TH
	void State_Attack10_Start();
	void State_Attack10_Update(float _Delta);

	// Sting
	void State_Attack11_Start();
	void State_Attack11_Update(float _Delta);

	//void State_Attack12_Start();
	//void State_Attack12_Update(float _Delta);

	// TH
	void State_Attack13_Start();
	void State_Attack13_Update(float _Delta);

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

