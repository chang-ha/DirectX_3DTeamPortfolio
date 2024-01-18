#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>

// 서버용
#include <GameEngineBase/GameEngineNetObject.h>
#include "ConnectIDPacket.h"

enum class PlayerState
{
	Idle,
	Smoke,
	Move,
	Move_Stop,
	Slow_Walk, 
	Run, 
	Attack_01,
	Attack_02,
	Attack_03,
	Attack_04,
	Portion_01, 
	Portion_02,
	Portion_03,
	Portion_04, 
};

// 설명 :
class Player : public GameEngineActor, public GameEngineNetObject // 서버용
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
	void Player_State();
	bool check = false;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;

	// 서버용
	void ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet);

	// 원래대로 
	// void Smoke_Stay()

private:
	bool TimeCheck = false;
	bool Attack_Check = false;
	float Time = 0.0f;
	float Speed = 10.0f;
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXCapsule> Capsule;
	std::shared_ptr<GameEngineCollision> Col;
	GameEngineState PlayerState;
	float MoveSpeed = 100.0f;
	EventParameter Mini_Event;
	float DeltaTime = 0.0f;
};
