#pragma once
#include "Monster_Hollow.h"

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

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

