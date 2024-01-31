#pragma once
#include "Monster_Hollow.h"

// Ό³Έν : 
class Monster_HollowSoldier_Spear : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Spear();
	~Monster_HollowSoldier_Spear();

	// delete Function
	Monster_HollowSoldier_Spear(const Monster_HollowSoldier_Spear & _Other) = delete;
	Monster_HollowSoldier_Spear(Monster_HollowSoldier_Spear && _Other) noexcept = delete;
	Monster_HollowSoldier_Spear& operator=(const Monster_HollowSoldier_Spear & _Other) = delete;
	Monster_HollowSoldier_Spear& operator=(Monster_HollowSoldier_Spear && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

