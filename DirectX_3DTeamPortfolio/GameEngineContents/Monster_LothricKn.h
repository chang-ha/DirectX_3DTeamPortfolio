#pragma once
#include "BaseMonster.h"

enum class Enum_LothricKn_State
{
	None,
	Debug,
	Sleep,
	Idle_Standing1,
	L_Side_Step, // L == Left
	R_Side_Step, // R == Right
	F_Step, // F == Forward
	B_Step, // B == Backward
	Run,
	Patrol,
	Combo_Att_11,
	Combo_Att_12,
	Combo_Att_13,
	Combo_Att_21,
	Combo_Att_22,
	Combo_Att_23,
	RH_Att_HitDown,
	LH_ShieldAttack,
	RH_Rear_Att,
	L_Turn,
	R_Turn,
	L_TurnTwice,
	R_TurnTwice,
	Idle_Sit,
	SitUp,
	DH_Hold,
	DH_UnHold,
	DH_Stab_Att,
	DH_Swing_Att,
	DH_L_Side_Step,
	DH_R_Side_Step,
	DH_F_Step,
	DH_B_Step,
	G_Up,
	G_Down,
	G_L_Side_Step,
	G_R_Side_Step,
	G_F_Step,
	G_B_Step,
	G_L_Turn,
	G_R_Turn,
	G_L_TurnTwice,
	G_R_TurnTwice,
	G_Run,
	G_Att_Bash,
};


// 설명 :
class Monster_LothricKn : public BaseMonster
{
	enum class eMeshInfo
	{
		Body,
		Cloak,
		Spear,
		Sword,
		Shield,
		LSword,
		Crossbow,
		Cloak_cloth,
		Close,
		Open,
		LShield,
		Weapon_Cloth,
		SwordCover,
	};

	enum class Enum_IdleType
	{
		Standing,
		Sit,
		None,
	};

	enum class Enum_Combat_State
	{
		Normal,
		Two_Handed,
		Gaurding,
		None,
	};

public:
	// constrcuter destructer
	Monster_LothricKn();
	~Monster_LothricKn();

	// delete Function
	Monster_LothricKn(const Monster_LothricKn& _Other) = delete;
	Monster_LothricKn(Monster_LothricKn&& _Other) noexcept = delete;
	Monster_LothricKn& operator=(const Monster_LothricKn& _Other) = delete;
	Monster_LothricKn& operator=(Monster_LothricKn&& _Other) noexcept = delete;

	void WakeUp() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void CreateFSM();

	// Start
	void Start_Debug(GameEngineState* _State);
	void StartSleep(GameEngineState* _State);
	void StartIdle_Standing1(GameEngineState* _State);
	void StartPatrol(GameEngineState* _State);
	void Start_Combo_Att_11(GameEngineState* _State);
	void Start_Combo_Att_12(GameEngineState* _State);
	void Start_Combo_Att_13(GameEngineState* _State);
	void Start_Combo_Att_21(GameEngineState* _State);
	void Start_Combo_Att_22(GameEngineState* _State);
	void Start_Combo_Att_23(GameEngineState* _State);
	void Start_RH_Att_HitDown(GameEngineState* _State);
	void StartLH_ShieldAttack(GameEngineState* _State);
	void Start_RH_Rear_Att(GameEngineState* _State);
	void Start_L_Turn(GameEngineState* _State);
	void Start_R_Turn(GameEngineState* _State);
	void Start_L_TurnTwice(GameEngineState* _State);
	void Start_R_TurnTwice(GameEngineState* _State);
	void Start_L_Side_Step(GameEngineState* _State);
	void Start_R_Side_Step(GameEngineState* _State);
	void Start_F_Step(GameEngineState* _State);
	void Start_B_Step(GameEngineState* _State);
	void Start_Run(GameEngineState* _State);
	void Start_Idle_Sit(GameEngineState* _State);
	void Start_SitUp(GameEngineState* _State);
	void Start_DH_Hold(GameEngineState* _State);
	void Start_DH_UnHold(GameEngineState* _State);
	void Start_DH_Stab_Att(GameEngineState* _State);
	void Start_DH_Swing_Att(GameEngineState* _State);
	void Start_DH_L_Side_Step(GameEngineState* _State);
	void Start_DH_R_Side_Step(GameEngineState* _State);
	void Start_DH_F_Step(GameEngineState* _State);
	void Start_DH_B_Step(GameEngineState* _State);
	void Start_G_Up(GameEngineState* _State);
	void Start_G_Down(GameEngineState* _State);
	void Start_G_L_Side_Step(GameEngineState* _State);
	void Start_G_R_Side_Step(GameEngineState* _State);
	void Start_G_F_Step(GameEngineState* _State);
	void Start_G_B_Step(GameEngineState* _State);
	void Start_G_L_Turn(GameEngineState* _State);
	void Start_G_R_Turn(GameEngineState* _State);
	void Start_G_L_TurnTwice(GameEngineState* _State);
	void Start_G_R_TurnTwice(GameEngineState* _State);
	void Start_G_Run(GameEngineState* _State);
	void Start_G_Att_Bash(GameEngineState* _State);
	
		// Update  G_Run
	void Update_Debug(float _DeltaTime, GameEngineState* _State);
	void UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State);
	void UpdatePatrol(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_11(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_12(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_13(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_21(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_22(float _DeltaTime, GameEngineState* _State);
	void Update_Combo_Att_23(float _DeltaTime, GameEngineState* _State);
	void Update_RH_Att_HitDown(float _DeltaTime, GameEngineState* _State);
	void UpdateLH_ShieldAttack(float _DeltaTime, GameEngineState* _State);
	void Update_RH_Rear_Att(float _DeltaTime, GameEngineState* _State);
	void Update_L_Turn(float _DeltaTime, GameEngineState* _State);
	void Update_R_Turn(float _DeltaTime, GameEngineState* _State);
	void Update_L_TurnTwice(float _DeltaTime, GameEngineState* _State);
	void Update_R_TurnTwice(float _DeltaTime, GameEngineState* _State);
	void Update_L_Side_Step(float _DeltaTime, GameEngineState* _State);
	void Update_R_Side_Step(float _DeltaTime, GameEngineState* _State);
	void Update_F_Step(float _DeltaTime, GameEngineState* _State);
	void Update_B_Step(float _DeltaTime, GameEngineState* _State);
	void Update_Run(float _DeltaTime, GameEngineState* _State);
	void Update_Idle_Sit(float _DeltaTime, GameEngineState* _State);
	void Update_SitUp(float _DeltaTime, GameEngineState* _State);
	void Update_DH_Hold(float _DeltaTime, GameEngineState* _State);
	void Update_DH_UnHold(float _DeltaTime, GameEngineState* _State);
	void Update_DH_Stab_Att(float _DeltaTime, GameEngineState* _State);
	void Update_DH_Swing_Att(float _DeltaTime, GameEngineState* _State);
	void Update_DH_Walk(float _DeltaTime, GameEngineState* _State);
	void Update_G_Up(float _DeltaTime, GameEngineState* _State);
	void Update_G_Down(float _DeltaTime, GameEngineState* _State);
	void Update_G_Walk(float _DeltaTime, GameEngineState* _State);
	void Update_G_L_Turn(float _DeltaTime, GameEngineState* _State);
	void Update_G_R_Turn(float _DeltaTime, GameEngineState* _State);
	void Update_G_L_TurnTwice(float _DeltaTime, GameEngineState* _State);
	void Update_G_R_TurnTwice(float _DeltaTime, GameEngineState* _State);
	void Update_G_Run(float _DeltaTime, GameEngineState* _State);
	void Update_G_Att_Bash(float _DeltaTime, GameEngineState* _State);
	


	// End
	void EndSleep(GameEngineState* _State);

	// State Func
	bool IsFrame(int _StartFrame, int _EndFrame = -1) const;
	bool IsFrameOnce(int _StartFrame);

	void StateTimeSet(float _fMin, float _fMax);
	void ResetStateTime();

	// 자식에서 함수 재정의해서 사용할 것
	Enum_TargetAngle GetTargetAngle_e() const override
	{
		return BaseMonster::GetTargetAngle_e(FRONT_ANGLE, SIDE_ANGLE);
	}

	Enum_TargetDist GetTargetDistance_e() const override
	{
		return BaseMonster::GetTargetDistance_e(CLOSE_RANGE, MELEE_RANGE, MEDIUM_RANGE);
	}

	float ConvertDistance_eTof(Enum_TargetDist _eTDist) const override;

	bool CanAttack(float _fDist, float _fDir) const;
	bool IsTargetInAngle(float _fAngle) const;

	void RotToTarget(float _DeltaTime, float _fSpeed);
	
	Enum_LothricKn_State GetStateToAggroTable();

	Enum_LothricKn_State GetStateToMovementTable() const;
	Enum_LothricKn_State GetStateToMovementTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToNormalMovementTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToDHMovementTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToGMovementTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;

	Enum_LothricKn_State GetStateToAttackTable();
	Enum_LothricKn_State GetStateToAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle);
	Enum_LothricKn_State GetStateToNormalAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle);
	Enum_LothricKn_State GetStateToDHAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToGAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;

	Enum_LothricKn_State GetStateToDodgeTable() const;
	Enum_LothricKn_State GetStateToDodgeTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToNormalDodgeTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToDHDodgeTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;
	Enum_LothricKn_State GetStateToGDodgeTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle) const;

	// Collision
	void FindTarget();

private:
	std::shared_ptr<GameEngineCollision> PatrolCollision;  

	Enum_IdleType IdleType = Enum_IdleType::None;
	Enum_Combat_State CombatState = Enum_Combat_State::None;

	int AttackRecord = 0;
	float fMaxStateTime = 0.0f;

	static constexpr float CLOSE_RANGE = 3.0f;
	static constexpr float MELEE_RANGE = 5.0f;
	static constexpr float MEDIUM_RANGE = 7.0f;
	static constexpr float LONG_RANGE = 10.0f;
	static constexpr float FRONT_ANGLE = 75.0f;
	static constexpr float SIDE_ANGLE = 115.0f;
	static constexpr float BACK_ANGLE = 150.0f;

	static constexpr float MIN_ROT_ANGLE = 3.0f;
	static constexpr float ROTSPEED_TO_TARGET = 510.0f;
	
};