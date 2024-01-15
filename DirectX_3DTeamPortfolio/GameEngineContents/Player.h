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
	Move_Stop
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
	float Time = 0.0f;
	float Speed = 100.0f;
	std::shared_ptr<GameEngineFBXRenderer> FBXRenderer;
	std::shared_ptr<GameEnginePhysXCapsule> Capsule;
	GameEngineState PlayerState;
	float MoveSpeed = 100.0f;
};
