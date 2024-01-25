#pragma once
#include "Monster_Hollow_NonFirstAttack.h"

// Ό³Έν : 
class Monster_Hollow_RaggedRobes : public Monster_Hollow_NonFirstAttack
{
public:
	// constrcuter destructer
	Monster_Hollow_RaggedRobes();
	~Monster_Hollow_RaggedRobes();

	// delete Function
	Monster_Hollow_RaggedRobes(const Monster_Hollow_RaggedRobes & _Other) = delete;
	Monster_Hollow_RaggedRobes(Monster_Hollow_RaggedRobes && _Other) noexcept = delete;
	Monster_Hollow_RaggedRobes& operator=(const Monster_Hollow_RaggedRobes & _Other) = delete;
	Monster_Hollow_RaggedRobes& operator=(Monster_Hollow_RaggedRobes && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

