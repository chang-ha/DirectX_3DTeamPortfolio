#pragma once
#include "BaseMonster.h"
#include "Monster_HitInteraction.h"

enum class Enum_Hollow_MeshIndex
{
	Sword = 0,
	Spear = 1,
	Crossbow = 2,
	RoundShield = 3,
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

enum class Enum_Hollow_BoneType
{
	Spine = 7,
	RoundShield = 15,
	WoodShield = 16,
	Sword = 44,
};

// Ό³Έν : 
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
	void LevelStart(class GameEngineLevel* _NextLevel) override;
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

	//void MeshOnOffSwitch(Enum_Hollow_MeshIndex _Index);

	void CreateAnimation();
	void SettingRootMotion();
	void SettingSoundFrameEvent();
	void SoundLoad();

private:

protected:
	std::shared_ptr<GameEngineCollision> RecognizeCollision;
	//std::shared_ptr<GameEngineCollision> AttackRangeCollision;
	std::shared_ptr<GameEngineCollision> BodyCollision;
	std::shared_ptr<GameEngineCollision> MonsterCollision;

	void FindTarget();
	bool IsTargetInAngle(float _fAngle) const;
	void RotToTarget(float _Delta);

	int AttackPattern = 0;

	Enum_TargetDist GetTargetDistance_e() const override
	{
		return BaseMonster::GetTargetDistance_e(3.0f, 5.0f, 7.0f);
	}

};

