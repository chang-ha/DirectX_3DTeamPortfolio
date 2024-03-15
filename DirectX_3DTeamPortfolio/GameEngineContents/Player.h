#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineState.h>
#include "BasePlayer.h"
// 서버용
#include <GameEngineBase/GameEngineNetObject.h>
#include "ConnectIDPacket.h"
#include "BaseActor.h"
#include "CameraCapsule.h"
#include "Weapon.h"
#include "shield.h"
#include "Player_HitInteraction.h"
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
	RockOn,

	Forward_Hit, 
	Left_Hit,
	Right_Hit,
	Backward_Hit,

	Forward_Middle_Hit,
	Left_Middle_Hit,
	Right_Middle_Hit,
	Backward_Middle_Hit,

	Forward_Big_Hit,
	Backward_Big_Hit,

	Death,
	ladder_Up_Start,
	ladder_Up_Left,
	ladder_Up_Right,
	ladder_Up_Stop_Left,
	ladder_Up_Stop_Right,
	ladder_Down_Start,
	ladder_Down_Left,
	ladder_Down_Right,
	ladder_Down_Stop_Left,
	ladder_Down_Stop_Right,

	Weak_Shield_block,
	Middle_Shield_block,
	Big_Shield_block,
	Parring_Attack, 
	Attack_Block, 
	Sit_Down,
	Stand_Up, 
	ladder_Fast_Down_Start,
	ladder_Fast_Down,
	ladder_Fast_Down_Stop,
	fail,
	landing,
	StaminaCheck
};

// 설명 :
class Player :  public GameEngineNetObject , public BaseActor
{
public:
	// constrcuter destructer

	static Player* Main_Player;
	int Bone_index_01 = 53;
	int Bone_index_02 = 17;
	Player();
	~Player();

	// delete Function
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
	void Player_State();

	void SoundFrameEvent();

	float4 BoneWorldPos(int _BoneIndex);
	void CameraRotation(float Delta);
	bool FrontStabCheck(const float4& _WPos, float _RotY) const;
	std::shared_ptr<Weapon> GetWeapon()
	{
		return Weapon_Actor;
	}
	std::shared_ptr<shield> GetShield()
	{
		return Shield_Actor;
	}


	std::shared_ptr<GameEngineActor> Actor_test_02;

	float4 CameraDir = {};
	float4 Camera_Distance = {};

	bool testa = false;
	bool testaa = false;
	bool testaaa = false;
	

	
	float Camera_Pos_Y = 0.0f;
	

	std::shared_ptr<GameEngineActor> Actor_test;
	float Delta_Time = 0.0f;

	bool GetHit(const HitParameter& _Para);
	bool GetHitToShield(const HitParameter& _Para);

	
	int GetPotion() const
	{
		return Potion;
	}


protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	

private:
	int Potion = 5;
	GameEngineSoundPlayer Sound; 

	float Poise_Time = 0.0f;
	//float Stamina = 100.0f;
	float Hp = 100.0f;


	float4 MoveDir;
	GameEngineState PlayerStates;
	EventParameter Mini_Event;



	std::string BoneName;

	std::shared_ptr<GameEngineCollision> Player_Col;

	std::shared_ptr<GameEngineCollision> Parring_Attack_Col;
	std::shared_ptr<BoneSocketCollision> Body_Col;
	std::shared_ptr<BoneSocketCollision> Shield_Col;
	std::shared_ptr<BoneSocketCollision> Attack_Col;

	std::shared_ptr<GameEngineCollision> Arround_Col;


	PlayerState StateValue = PlayerState::Idle;
	float Mouse_Pos = 0.0f;
	


	bool TimeCheck = false;
	bool Attack_Check = false;

	bool Rotation_Check_X = false;
	bool Rotation_Check_X_Plus = false;
	bool Rotation_Check_X_Mus = false;

	bool Rotation_Check_Y = false;
	bool Rotation_Check_Y_Plus = false;
	bool Rotation_Check_Y_Mus = false;
	bool Parring_Check = false;
	EventParameter Body_Event;
	EventParameter Labber_Event;
	EventParameter Labber_Middle_Event;
	EventParameter Labber_Top_Event;
	EventParameter Shield_Event;
	EventParameter Parring_Event;


	EventParameter Arround_Event;

	Player_HitInteraction Sword;


	bool Rotation_Player_Check = false;
	bool Rotation_Player_Plus = false;
	bool Rotation_Player_Mus = false;

	

	float MonsterAngle = 0.0f;


	bool Rock_On_Check = false;
	bool Rabber_Collision_Check = false;
	bool Rock_on_Time_Check = false;
	float Time = 0.0f;
	float Rock_on_Time = 0.0f;
	
	float Speed = 1000.0f;
	float MoveSpeed = 0.0f;
	float DeltaTime = 0.0f;

	

	
	float4 Player_Pos = {};

	bool IsFreeCameraValue = false;
	bool Cameratest = false;
	bool Rock_OnOff = false;


	float Angle = 0.0f;
	float Labber_Angle = 0.0f;
	//float MonsterAngle = 0.0f;

	float Monser_Dir = 0.0f;
	std::vector<int> MonsterAngles;
	int Number = 0;

	std::vector<GameEngineActor*> Monster_Actor;
	std::vector<GameEngineActor*> Parring_Monster_Actor;
	

	std::shared_ptr<CameraCapsule> Cameracapsule;
	std::shared_ptr<Weapon> Weapon_Actor;
	std::shared_ptr<shield> Shield_Actor;

	float4 CameraPos = {};
	float Mouse_Ro_X = 0.0f;
	float Mouse_Ro_Y = 0.0f;
	float4 PrevPos = {};
	
	float Camera_Pos_X = 0.0f;



	float degree_X = 0.0f;
	float degree_Y = 0.0f;
	
	float4 ASS = {};

	float Monster_Degree = 0.0f;

	std::shared_ptr<class ContentsHitRenderer> HitRenderer;
	std::shared_ptr<class ContentsHitRenderer> StrikeRenderer;
};



