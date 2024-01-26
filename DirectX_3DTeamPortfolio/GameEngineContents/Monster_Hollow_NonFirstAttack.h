#pragma once
#include "Monster_Hollow.h"

enum class Enum_Hollow_State
{
	Pray1,
	Pray2,
	Pray3,
	PrayToBeScared1,
	PrayToBeScared2,
	PrayToBeScared3,
	BeScared,
	PrayToIdle1,
	PrayToIdle2,
	PrayToIdle3,
	BeScaredToIdle,
	Idle,
	//Walk,
	//Run,
	RH_VerticalSlash,
	RH_HorizontalSlash,
	RH_ComboAttack,
	RH_TwinSlash,
	AttackFail,
	Hit,
	HitToDeath,
	Death,
	Max,
};

// ���� : 
class Monster_Hollow_NonFirstAttack : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_Hollow_NonFirstAttack();
	~Monster_Hollow_NonFirstAttack();

	// delete Function
	Monster_Hollow_NonFirstAttack(const Monster_Hollow_NonFirstAttack & _Other) = delete;
	Monster_Hollow_NonFirstAttack(Monster_Hollow_NonFirstAttack && _Other) noexcept = delete;
	Monster_Hollow_NonFirstAttack& operator=(const Monster_Hollow_NonFirstAttack & _Other) = delete;
	Monster_Hollow_NonFirstAttack& operator=(Monster_Hollow_NonFirstAttack && _Other) noexcept = delete;

	void SetStatePray1()
	{
		//PrevState = Enum_Hollow_State::Pray1;
		ChangeState(Enum_Hollow_State::Pray1);
	}
	void SetStatePray2()
	{
		//PrevState = Enum_Hollow_State::Pray2;
		ChangeState(Enum_Hollow_State::Pray2);
	}
	void SetStatePray3()
	{
		//PrevState = Enum_Hollow_State::Pray3;
		ChangeState(Enum_Hollow_State::Pray3);
	}

protected:
	void Start() override;
	void Update(float _Delta) override;


	

private:
	float StateTime = 0.0f;

protected:
	Enum_Hollow_State HollowState = Enum_Hollow_State::Max;
	//Enum_Hollow_State PrevState = Enum_Hollow_State::Max;

	void ChangeState(Enum_Hollow_State _State);
	void StateUpdate(float _Delta);


protected:
	// State Function
	void State_Pray1_Start();
	void State_Pray1_Update(float _Delta);

	void State_Pray2_Start();
	void State_Pray2_Update(float _Delta);

	void State_Pray3_Start();
	void State_Pray3_Update(float _Delta);

	void State_PrayToBeScared1_Start();
	void State_PrayToBeScared1_Update(float _Delta);

	void State_PrayToBeScared2_Start();
	void State_PrayToBeScared2_Update(float _Delta);

	void State_PrayToBeScared3_Start();
	void State_PrayToBeScared3_Update(float _Delta);

	void State_BeScared_Start();
	void State_BeScared_Update(float _Delta);

	void State_PrayToIdle1_Start();
	void State_PrayToIdle1_Update(float _Delta);

	void State_PrayToIdle2_Start();
	void State_PrayToIdle2_Update(float _Delta);

	void State_PrayToIdle3_Start();
	void State_PrayToIdle3_Update(float _Delta);

	void State_BeScaredToIdle_Start();
	void State_BeScaredToIdle_Update(float _Delta);

	void State_Idle_Start();
	void State_Idle_Update(float _Delta);

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

	void State_Hit_Start();
	void State_Hit_Update(float _Delta);

	void State_HitToDeath_Start();
	void State_HitToDeath_Update(float _Delta);

	void State_Death_Start();
	void State_Death_Update(float _Delta);
};

