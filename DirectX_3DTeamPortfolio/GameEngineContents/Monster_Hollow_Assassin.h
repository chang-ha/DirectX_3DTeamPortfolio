#pragma once
#include "Monster_Hollow.h"

enum class Enum_Hollow_Assassin_State
{
	Max,
};

// Ό³Έν : 
class Monster_Hollow_Assassin : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_Hollow_Assassin();
	~Monster_Hollow_Assassin();

	// delete Function
	Monster_Hollow_Assassin(const Monster_Hollow_Assassin & _Other) = delete;
	Monster_Hollow_Assassin(Monster_Hollow_Assassin && _Other) noexcept = delete;
	Monster_Hollow_Assassin& operator=(const Monster_Hollow_Assassin & _Other) = delete;
	Monster_Hollow_Assassin& operator=(Monster_Hollow_Assassin && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

protected:
	Enum_Hollow_Assassin_State AssassinState = Enum_Hollow_Assassin_State::Max;

	void ChangeState(Enum_Hollow_Assassin_State _State);
	void StateUpdate(float _Delta);
};

