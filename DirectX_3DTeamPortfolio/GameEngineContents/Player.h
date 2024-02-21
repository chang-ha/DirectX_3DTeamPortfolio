#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>
#include "BasePlayer.h"
// 서버용
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

// 설명 :
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
	void CameraRotation(float Delta);
protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	//void CameraRotation(float Delta);

	// 서버용
	void ConnectIDPacketProcess(std::shared_ptr<ConnectIDPacket> _Packet);

	// 원래대로 
	// void Smoke_Stay()

private:
	float4 MoveDir;
	GameEngineState PlayerStates;
	EventParameter Mini_Event;
	std::string BoneName;
	std::shared_ptr<GameEngineCollision> Col;
	std::shared_ptr<GameEngineActor> SwordActor;
	
	PlayerState StateValue = PlayerState::Idle;
	float Mouse_Pos = 0.0f;
	
	

	bool TimeCheck = false;
	bool Attack_Check = false;
	bool Rotation_Check = false;
	bool Rotation_Check_Plus = false;
	bool Rotation_Check_Mus = false;
	float Time = 0.0f;
	float Speed = 1000.0f;
	float MoveSpeed = 0.0f;
	float DeltaTime = 0.0f;

	float4 Player_Pos = {};
	bool IsFreeCameraValue = false;

	float Angle = 0.0f;
	float MonsterAngle = 0.0f;
	std::shared_ptr<GameEngineActor> Actor_test;
	std::shared_ptr<GameEngineActor> Actor_test_02;


	float4 CameraPos = {};
	float Mouse_Ro_X = 0.0f;
	float Mouse_Ro_Y = 0.0f;
	float4 PrevPos = {};
	float Camera_Pos_Y = 0.0f;
	float Camera_Pos_X = 0.0f;


};
