#pragma once
#include "Monster_Hollow.h"

enum class Enum_HollowSoldier_State
{
	Walk,
	Run,
	Max,
};

// Ό³Έν : 
class Monster_HollowSoldier : public Monster_Hollow
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

	

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
private:

	Enum_HollowSoldier_State State = Enum_HollowSoldier_State::Max;
};

