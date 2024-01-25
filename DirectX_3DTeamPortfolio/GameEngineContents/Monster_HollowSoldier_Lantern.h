#pragma once
#include "Monster_Hollow.h"

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

protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};

