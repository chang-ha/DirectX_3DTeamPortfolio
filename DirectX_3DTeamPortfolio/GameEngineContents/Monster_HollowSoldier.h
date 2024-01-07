#pragma once
#include "CommonMonster.h"

enum class HollowSoldier_MeshIndex
{
	Sword = 0,
	Spear = 1,
	Crossbow,
	CircleShield,
	WoodShield,
	ChainMail,
	ShoulderRobe,
	Helmat,
	InnerHood,
	HeadChainMail,
	RightKneePads,
	LeftKneePads,
	Shoes,
	Lantern,
	SmallLeatherVest,
	Bone,
	BeltLantern,
	BrokenSword,
	Dagger,
	Pants,
	OuterHood,
	Shirt1,
	Shirt2,
	Belt1,
	Belt2,
	Belt3,
	BigLeatherVest,
	ShortSkirt,
	LongSkirt1,
	LongSkirt2,
	TopRobe,
	Scarf,
	ArmSleeve1,
	ArmSleeve2,
	UpperBody
};

enum class HollowSoldier_State
{
	Walk,
	Run,
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier : public CommonMonster
{
public:
	// constrcuter destructer
	Monster_HollowSoldier();
	~Monster_HollowSoldier();

	// delete Function
	Monster_HollowSoldier(const Monster_HollowSoldier & _Other) = delete;
	Monster_HollowSoldier(Monster_HollowSoldier && _Other) noexcept = delete;
	Monster_HollowSoldier& operator=(const Monster_HollowSoldier & _Other) = delete;
	Monster_HollowSoldier& operator=(Monster_HollowSoldier && _Other) noexcept = delete;

	void MeshOnOffSwitch(HollowSoldier_MeshIndex _Index);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
private:
	
	

	HollowSoldier_State State = HollowSoldier_State::Max;
};

