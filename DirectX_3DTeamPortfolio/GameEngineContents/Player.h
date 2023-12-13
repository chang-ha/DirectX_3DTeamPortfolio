#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>

enum class PlayerState
{
	Idle,
	Smoke,
	Move,
};

// 설명 :
class Player : public GameEngineActor
{
public:
	// constrcuter destructer
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	// 원래대로 
	// void Smoke_Stay()

private:
	std::shared_ptr<GameEngineFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEngineCollision> Col;
	GameEngineState PlayerState;
	float MoveSpeed = 100.0f;
};

