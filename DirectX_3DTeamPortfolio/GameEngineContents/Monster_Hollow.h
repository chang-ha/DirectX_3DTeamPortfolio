#pragma once
#include "BaseMonster.h"

enum class Enum_Hollow_MeshIndex
{
	Sword = 0,
	Spear = 1,
	Crossbow = 2,
	CircleShield = 3,
	WoodShield = 4,
	ChainMail = 5,
	ShoulderRobe = 6,
	Helmat = 7,
	InnerHood = 8,
	HeadChainMail = 9,
	RightKneePads = 10,
	LeftKneePads = 11,
	Shoes = 12,
	Lantern = 13,
	SmallLeatherVest = 14,
	Bone = 15,
	BeltLantern = 16,
	BrokenSword = 17,
	Dagger = 18,
	Pants = 19,
	OuterHood = 20,
	Shirt1 = 21,
	Shirt2 = 22,
	Belt1 = 23,
	Belt2 = 24,
	Belt3 = 25,
	BigLeatherVest = 26,
	ShortSkirt = 27,
	LongSkirt1 = 28,
	LongSkirt2 = 29,
	TopRobe = 30,
	Scarf = 31,
	ArmSleeve1 = 32,
	ArmSleeve2 = 33,
	UpperBody = 34,
	None
};

// ���� : 
class Monster_Hollow : public BaseMonster
{
public:
	// constrcuter destructer
	Monster_Hollow();
	~Monster_Hollow();

	// delete Function
	Monster_Hollow(const Monster_Hollow & _Other) = delete;
	Monster_Hollow(Monster_Hollow && _Other) noexcept = delete;
	Monster_Hollow& operator=(const Monster_Hollow & _Other) = delete;
	Monster_Hollow& operator=(Monster_Hollow && _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	//void MeshOnOffSwitch(Enum_Hollow_MeshIndex _Index);

	void LoadAnimation();

private:

};

