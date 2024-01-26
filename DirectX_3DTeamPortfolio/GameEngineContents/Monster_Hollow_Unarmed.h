#pragma once
#include "Monster_Hollow_NonFirstAttack.h"

// Ό³Έν : 
class Monster_Hollow_Unarmed : public Monster_Hollow_NonFirstAttack
{
public:
	// constrcuter destructer
	Monster_Hollow_Unarmed();
	~Monster_Hollow_Unarmed();

	// delete Function
	Monster_Hollow_Unarmed(const Monster_Hollow_Unarmed & _Other) = delete;
	Monster_Hollow_Unarmed(Monster_Hollow_Unarmed && _Other) noexcept = delete;
	Monster_Hollow_Unarmed& operator=(const Monster_Hollow_Unarmed & _Other) = delete;
	Monster_Hollow_Unarmed& operator=(Monster_Hollow_Unarmed && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

