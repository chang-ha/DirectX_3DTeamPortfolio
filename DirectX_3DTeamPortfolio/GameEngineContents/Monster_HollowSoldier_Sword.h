#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_Sword_State
{
	Idle1,
	Idle2,
	Scout,
	Walk,
	Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
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

	int AttackPattern = 0;

protected:
	Enum_HollowSoldier_Sword_State SoldierState = Enum_HollowSoldier_Sword_State::Max;

	void ChangeState(Enum_HollowSoldier_Sword_State _State);
	void StateUpdate(float _Delta);

	void ChangeAttackState();

private:
	std::shared_ptr<GameEngineCollision> RecognizeCollision;
	std::shared_ptr<GameEngineCollision> AttackRangeCollision;

	bool IsRecognize = false;
	bool IsAttack = false;

	class GameEngineRandom RandomAttack;

protected:
	//State Function

	void State_Idle1_Start();
	void State_Idle1_Update(float _Delta);

	void State_Idle2_Start();
	void State_Idle2_Update(float _Delta);

	void State_Scout_Start();
	void State_Scout_Update(float _Delta);

	void State_Walk_Start();
	void State_Walk_Update(float _Delat);

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

	//void State_Attack4_Start();
	//void State_Attack4_Update(float _Delta);

	void State_Attack5_Start();
	void State_Attack5_Update(float _Delta);

	void State_Attack6_Start();
	void State_Attack6_Update(float _Delta);

	void State_Attack7_Start();
	void State_Attack7_Update(float _Delta);
	
	void State_Attack8_Start();
	void State_Attack8_Update(float _Delta);

	void State_Attack9_Start();
	void State_Attack9_Update(float _Delta);

	void State_Attack10_Start();
	void State_Attack10_Update(float _Delta);

	void State_Attack11_Start();
	void State_Attack11_Update(float _Delta);

	//void State_Attack12_Start();
	//void State_Attack12_Update(float _Delta);

	void State_Attack13_Start();
	void State_Attack13_Update(float _Delta);

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

