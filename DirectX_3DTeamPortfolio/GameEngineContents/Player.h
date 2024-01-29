#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>
#include "BasePlayer.h"
// ������
#include <GameEngineBase/GameEngineNetObject.h>
#include "ConnectIDPacket.h"
#include "BaseActor.h"

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
	
	Roll_Forward,
	Roll_Behind,
	Roll_Right,
	Roll_Left,
	Back_Step,
	Shield_Idle, 
	Shield_Move,
	Parrying,

};

// ���� :
class Player :  public GameEngineNetObject , public BaseActor
{
public:
	// constrcuter destructer

	static Player* Main_Player;
	int Bone_index_01 = 53;
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	void Player_State();
	bool check = false;
	std::shared_ptr<GameContentsFBXRenderer> Weapon;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;

	// ������
	void ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet);

	// ������� 
	// void Smoke_Stay()

private:
	float4 MoveDir;
	GameEngineState PlayerState;
	EventParameter Mini_Event;
	std::string BoneName;
	std::shared_ptr<GameEngineCollision> Col;
	std::shared_ptr<GameEngineActor> SwordActor;
	float Mouse_Pos = 0.0f;
	float Camera_Pos = 0.0f; 
	bool TimeCheck = false;
	bool Attack_Check = false;
	float Time = 0.0f;
	float Speed = 100.0f;
	float MoveSpeed = 0.0f;
	float DeltaTime = 0.0f;
};
