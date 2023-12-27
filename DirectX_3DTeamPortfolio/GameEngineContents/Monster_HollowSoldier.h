#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν : 
class Monster_HollowSoldier : public GameEngineActor
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
private:
	std::shared_ptr<GameEngineFBXRenderer> FBXRenderer;
};

