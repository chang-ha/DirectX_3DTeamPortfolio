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
	Right_Walk,
	Front_Walk,
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
};

enum class Enum_MonsterDebugFlag
{
	None = 0,
	PatrolValue = (1 << 0),
};

class MonsterDebugState
{
public:
	bool IsFlag(Enum_MonsterDebugFlag _eValue)
	{
		BitMethod::IsOnFlag(DebugFlag, static_cast<int>(_eValue));
	}

	void SetFlag(Enum_MonsterDebugFlag _eValue, bool _bOn)
	{
		BitMethod::SetFlag(&DebugFlag, static_cast<int>(_eValue), _bOn);
	}

private:

	int DebugFlag = 0;
};

// ���� :
class Monster_LothricKn : public BaseMonster
{
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

	// Update
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

	// End
	void EndSleep(GameEngineState* _State);

	// State Func
	bool IsFrame(int _StartFrame, int _EndFrame = -1) const;
	bool IsFrameOnce(int _StartFrame);

	void StateTimeSet(float _fMin, float _fMax);
	void ResetStateTime();

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
	Enum_LothricKn_State GetStateToAttackTable();
	Enum_LothricKn_State GetStateToAttackTable(Enum_TargetDist _eTDist, Enum_TargetAngle _eTAngle);

	// Collision
	void FindTarget();

private:
	std::shared_ptr<GameEngineCollision> PatrolCollision;
	MonsterDebugState Debug;

	int AttackRecord = 0;
	float fMaxStateTime = 0.0f;

	static constexpr float CLOSE_RANGE = 1.0f;
	static constexpr float MELEE_RANGE = 3.0f;
	static constexpr float MEDIUM_RANGE = 5.0f;
	static constexpr float LONG_RANGE = 7.0f;
	static constexpr float FRONT_ANGLE = 75.0f;
	static constexpr float SIDE_ANGLE = 115.0f;
	static constexpr float BACK_ANGLE = 150.0f;

	static constexpr float MIN_ROT_ANGLE = 3.0f;
	static constexpr float ROTSPEED_TO_TARGET = 510.0f;
	
};