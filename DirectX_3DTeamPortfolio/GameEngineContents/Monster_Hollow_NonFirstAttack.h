#pragma once
#include "Monster_Hollow.h"

enum class Enum_Hollow_State
{
	Pray1,
	Pray2,
	Pray3,
	PrayToBeScared,
	BeScared,
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

protected:
	void Start() override;
	void Update(float _Delta) override;


	

private:
	

protected:
	Enum_Hollow_State HollowState = Enum_Hollow_State::Max;

	void ChangeState(Enum_Hollow_State _State);
	void StateUpdate(float _Delta);


protected:
	// State Function
	void State_Pray1_Start();
	//void State_Pray1_Update(float _Delta);

	void State_Pray2_Start();
	//void State_Pray2_Update(float _Delta);

	void State_Pray3_Start();
	//void State_Pray3_Update(float _Delta);

	void State_PrayToBeScared_Start();
	void State_PrayToBeScared_Update(float _Delta);

	void State_BeScared_Start();
	void State_BeScared_Update(float _Delta);
};

