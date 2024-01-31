#pragma once
#include "Monster_Hollow.h"

// ���� : 
class Monster_HollowSoldier_Crossbow : public Monster_Hollow
{
public:
	// constrcuter destructer
	Monster_HollowSoldier_Crossbow();
	~Monster_HollowSoldier_Crossbow();

	// delete Function
	Monster_HollowSoldier_Crossbow(const Monster_HollowSoldier_Crossbow & _Other) = delete;
	Monster_HollowSoldier_Crossbow(Monster_HollowSoldier_Crossbow && _Other) noexcept = delete;
	Monster_HollowSoldier_Crossbow& operator=(const Monster_HollowSoldier_Crossbow & _Other) = delete;
	Monster_HollowSoldier_Crossbow& operator=(Monster_HollowSoldier_Crossbow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:

};

