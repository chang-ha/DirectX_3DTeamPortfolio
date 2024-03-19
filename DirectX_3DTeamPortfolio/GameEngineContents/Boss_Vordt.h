#pragma once
#include "BaseActor.h"
#include "Monster_HitInteraction.h"

#define STAT_COOLDOWN 1.f
#define HIT_COOLDOWN 0.5f

// Ό³Έν :
class Boss_State_GUI : public GameEngineGUIWindow
{
	friend class Boss_Vordt;
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	
protected:

private:
	std::vector<const char*> StateNames;
	std::vector<int> StateIndex;
	Boss_Vordt* Linked_Boss = nullptr;
	void Reset();
};

enum Enum_BossState
{
	// Move & Others
	Null = 0,
	Howling,
	Idle,
	Walk_Front,
	Walk_Right,
	Walk_Left,
	Rush_Front,
	Jump_Back,
	Jump_Right,
	Jump_Left,
	Turn_Right,
	Turn_Left,
	Turn_Right_Twice,
	Turn_Left_Twice,
	Hitten_Front,
	Hitten_Back,
	Hitten_Right,
	Hitten_Left,
	Hitten_Groggy,
	Groggy,
	Death,
	Death_Groggy,

	// Attack
	Breath,
	Combo1_Step1,
	Combo1_Step2,
	Combo1_Step3,
	Combo2_Step1,
	Combo2_Step2,
	Sweap_Twice_Right,
	Sweap_Twice_Left,
	Hit_Down_001_Front,
	Hit_Down_001_Right,
	Hit_Down_001_Left,
	Hit_Down_004,
	Hit_Down_005,
	Hit_Down_006,
	Thrust,
	Sweep_001,
	Sweep_002,
	Rush_Attack_001,
	Rush_Attack_002,
	Rush_Turn,
	Rush_Hit_Turn,
	Rush_Hit_Turn_Rush,
};

enum Enum_TargetDis
{
	Dis_Null = -1,
	Dis_Attach = 0,
	Dis_Close = 1,
	Dis_Middle = 2,
	Dis_Long = 3,
	Dis_Far = 4,
	Dis_OutOfRange = 5,
};

enum Enum_TargetDeg
{
	Deg_Null = -1,
	Deg_Front = 0,
	Deg_Side = 1,
	Deg_Back = 2
};

struct TargetState
{
	int mTargetDis = Enum_TargetDis::Dis_Null;
	int mTargetDeg = Enum_TargetDeg::Deg_Null;
};

enum Enum_Boss_Phase
{
	Phase_Null = 0,
	Phase_1 = 1,
	Phase_2 = 2,
};

struct AI_State
{
	AI_State()
	{

	}

	AI_State(float _StateCoolDown)
		: StateCoolDown(_StateCoolDown)
	{

	}

	AI_State(float _StateCoolDown, float _InitCurCoolDown)
		: StateCoolDown(_StateCoolDown), CurCoolDown(_InitCurCoolDown)
	{

	}

	void Update(float _Delta);

	float StateCoolDown = 0.f;
	float CurCoolDown = 0.f;
};

class Vordt_HitCollision
{
	friend class Boss_Vordt;
	std::shared_ptr<BoneSocketCollision> BodyCollision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_Claf_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_ClafWist1_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_Toe_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_Foot_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_UpArmTwist_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_ForeArm_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> L_Hand_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_Claf_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_ClafWist1_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_Toe_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_Foot_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_UpArmTwist_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_ForeArm_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> R_Hand_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> Neck_Collision = nullptr;
	std::shared_ptr<BoneSocketCollision> Throw_Collision = nullptr;

	void Off();
	void On();
	void Release();
};

class Vordt_AttackCollision
{
	friend class Boss_Vordt;
	Monster_HitInteraction mBodyHitInteraction;
	std::shared_ptr<BoneSocketCollision> BodyCollision = nullptr;
	Monster_HitInteraction mHeadHitInteraction;
	std::shared_ptr<BoneSocketCollision> HeadCollision = nullptr;
	Monster_HitInteraction mWeaponHitInteraction;
	std::shared_ptr<BoneSocketCollision> WeaponCollision = nullptr;
	Monster_HitInteraction mHandHitInteraction;
	std::shared_ptr<BoneSocketCollision> R_HandCollision = nullptr;

	void Off();
	void ResetRecord();
	void Release();
};

class Boss_Vordt : public BaseActor
{
	friend Boss_State_GUI;
public:
	// constructer destructer
	Boss_Vordt();
	~Boss_Vordt();

	// delete function
	Boss_Vordt(const Boss_Vordt& _Ohter) = delete;
	Boss_Vordt(Boss_Vordt&& _Ohter) noexcept = delete;
	Boss_Vordt& operator=(const Boss_Vordt& _Other) = delete;
	Boss_Vordt& operator=(Boss_Vordt&& _Other) noexcept = delete;

	void AI_Start();
	void AI_Stop();

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	bool GetHit(const HitParameter& _Para = HitParameter()) override;
	bool GetHitToShield(const HitParameter& _Para = HitParameter()) override;

private:
	// RockOnCollision
	std::shared_ptr<GameEngineCollision> RockOnCollision = nullptr;
	// HitCollision
	Vordt_HitCollision mHitCollision;
	// AttackCollision
	Vordt_AttackCollision mAttackCollision;
	void CollisionUpdate();

	bool AI_Off = false;
	std::shared_ptr<Boss_State_GUI> GUI = nullptr;

	void FrameEventInit();
	void StateInit();

	static constexpr float Distance_Standard = 500.f;
	static constexpr float Degree_Standard = 60.f;
	float Stat_CoolDown = STAT_COOLDOWN;

	float Hit_CoolDown = 0.f;
	int HitSoune_Count = 1;
	void HitUpdate(float _Delta);

	TargetState mTargetState;
	void TargetStateUpdate();

	Enum_Boss_Phase mBoss_Phase = Enum_Boss_Phase::Phase_1;
	int Rush_Combo_Count = 0;
	int Groggy_Count = 0;
	void PhaseChangeCheck();

	bool IsAwake = false;

	Enum_JumpTableFlag AI_MoveMent();
	Enum_JumpTableFlag AI_Attack();
	Enum_JumpTableFlag AI_Combo();
	Enum_JumpTableFlag AI_Dodge();
	std::map<Enum_BossState, AI_State> AI_States;
	bool ChangeAI_State(Enum_BossState _State);
	void AIUpdate(float _Delta);

	void MostPrioritzedUpdate();
	void DeathCheck();
	void GroggyCheck();

	// State
	////////////////////////// Move & Others
	// Howling
	void Howling_Start();
	void Howling_Update(float _Delta);
	void Howling_End();

	// Idle
	void Idle_Start();
	void Idle_Update(float _Delta);
	void Idle_End();

	// Walk
	void Walk_Front_Start();
	void Walk_Front_Update(float _Delta);
	void Walk_Front_End();

	void Walk_Right_Start();
	void Walk_Right_Update(float _Delta);
	void Walk_Right_End();

	void Walk_Left_Start();
	void Walk_Left_Update(float _Delta);
	void Walk_Left_End();

	// Rush_Front
	void Rush_Front_Start();
	void Rush_Front_Update(float _Delta);
	void Rush_Front_End();

	// Jump
	void Jump_Back_Start();
	void Jump_Back_Update(float _Delta);
	void Jump_Back_End();

	void Jump_Right_Start();
	void Jump_Right_Update(float _Delta);
	void Jump_Right_End();

	void Jump_Left_Start();
	void Jump_Left_Update(float _Delta);
	void Jump_Left_End();

	// Turn
	void Turn_Right_Start();
	void Turn_Right_Update(float _Delta);
	void Turn_Right_End();

	void Turn_Left_Start();
	void Turn_Left_Update(float _Delta);
	void Turn_Left_End();

	void Turn_Right_Twice_Start();
	void Turn_Right_Twice_Update(float _Delta);
	void Turn_Right_Twice_End();

	void Turn_Left_Twice_Start();
	void Turn_Left_Twice_Update(float _Delta);
	void Turn_Left_Twice_End();

	// Hitten
	void Hitten_Front_Start();
	void Hitten_Front_Update(float _Delta);
	void Hitten_Front_End();

	void Hitten_Back_Start();
	void Hitten_Back_Update(float _Delta);
	void Hitten_Back_End();

	void Hitten_Right_Start();
	void Hitten_Right_Update(float _Delta);
	void Hitten_Right_End();

	void Hitten_Left_Start();
	void Hitten_Left_Update(float _Delta);
	void Hitten_Left_End();

	void Hitten_Groggy_Start();
	void Hitten_Groggy_Update(float _Delta);
	void Hitten_Groggy_End();

	// Groggy
	void Groggy_Start();
	void Groggy_Update(float _Delta);
	void Groggy_End();

	// Death
	void Death_Start();
	void Death_Update(float _Delta);
	void Death_End();

	void Death_Groggy_Start();
	void Death_Groggy_Update(float _Delta);
	void Death_Groggy_End();

	////////////////////////// Attack

	// Breath
	void Breath_Start();
	void Breath_Update(float _Delta);
	void Breath_End();

	// Combo1
	void Combo1_Step1_Start();
	void Combo1_Step1_Update(float _Delta);
	void Combo1_Step1_End();

	void Combo1_Step2_Start();
	void Combo1_Step2_Update(float _Delta);
	void Combo1_Step2_End();

	void Combo1_Step3_Start();
	void Combo1_Step3_Update(float _Delta);
	void Combo1_Step3_End();

	// Combo1
	void Combo2_Step1_Start();
	void Combo2_Step1_Update(float _Delta);
	void Combo2_Step1_End();
	
	void Combo2_Step2_Start();
	void Combo2_Step2_Update(float _Delta);
	void Combo2_Step2_End();

	// Sweap
	void Sweap_Twice_Right_Start();
	void Sweap_Twice_Right_Update(float _Delta);
	void Sweap_Twice_Right_End();

	void Sweap_Twice_Left_Start();
	void Sweap_Twice_Left_Update(float _Delta);
	void Sweap_Twice_Left_End();

	// Hit_Down_001
	void Hit_Down_001_Front_Start();
	void Hit_Down_001_Front_Update(float _Delta);
	void Hit_Down_001_Front_End();

	void Hit_Down_001_Right_Start();
	void Hit_Down_001_Right_Update(float _Delta);
	void Hit_Down_001_Right_End();

	void Hit_Down_001_Left_Start();
	void Hit_Down_001_Left_Update(float _Delta);
	void Hit_Down_001_Left_End();

	// Hit_Down_004
	void Hit_Down_004_Start();
	void Hit_Down_004_Update(float _Delta);
	void Hit_Down_004_End();

	// Hit_Down_005
	void Hit_Down_005_Start();
	void Hit_Down_005_Update(float _Delta);
	void Hit_Down_005_End();

	// Hit_Down_006
	void Hit_Down_006_Start();
	void Hit_Down_006_Update(float _Delta);
	void Hit_Down_006_End();

	// Thrust
	void Thrust_Start();
	void Thrust_Update(float _Delta);
	void Thrust_End();

	// Sweep_001
	void Sweep_001_Start();
	void Sweep_001_Update(float _Delta);
	void Sweep_001_End();

	// Sweep_002
	void Sweep_002_Start();
	void Sweep_002_Update(float _Delta);
	void Sweep_002_End();

	///// Rush Attack
	// Rush_Attack_001
	void Rush_Attack_001_Start();
	void Rush_Attack_001_Update(float _Delta);
	void Rush_Attack_001_End();

	// Rush_Attack_002
	void Rush_Attack_002_Start();
	void Rush_Attack_002_Update(float _Delta);
	void Rush_Attack_002_End();

	// Rush&Turn
	void Rush_Turn_Start();
	void Rush_Turn_Update(float _Delta);
	void Rush_Turn_End();

	// Rush_Hit_Turn
	void Rush_Hit_Turn_Start();
	void Rush_Hit_Turn_Update(float _Delta);
	void Rush_Hit_Turn_End();

	// Rush_Hit_Turn_Rush
	void Rush_Hit_Turn_Rush_Start();
	void Rush_Hit_Turn_Rush_Update(float _Delta);
	void Rush_Hit_Turn_Rush_End();
};