#pragma once
#include "BaseMonster.h"

enum class Enum_LothricKn_State
{
	None,
	Sleep,
	Idle_Standing1,
	Left_Turn_Twice,
	Left_Turn,
	Right_Turn_Twice,
	Right_Turn,
	Run,
	Patrol,
	Attack11,
	Attack12,
	Attack13,
	RH_SwordDownAttack,
	LH_ShieldAttack,
	RH_CAttack,
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

// Ό³Έν :
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
	void StartSleep(GameEngineState* _State);
	void StartIdle_Standing1(GameEngineState* _State);
	void StartPatrol(GameEngineState* _State);
	void StartRH_Attack11(GameEngineState* _State);
	void StartRH_Attack12(GameEngineState* _State);
	void StartRH_Attack13(GameEngineState* _State);
	void StartRH_SwordDownAttack(GameEngineState* _State);
	void StartLH_ShieldAttack(GameEngineState* _State);
	void StartRH_CAttack(GameEngineState* _State);

	// Update
	void UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State);
	void UpdatePatrol(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack11(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack12(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack13(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_SwordDownAttack(float _DeltaTime, GameEngineState* _State);
	void UpdateLH_ShieldAttack(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_CAttack(float _DeltaTime, GameEngineState* _State);

	// End
	void EndSleep(GameEngineState* _State);

	// State Func
	bool IsFrame(int _StartFrame, int _EndFrame = -1) const;
	float GetDirByDot(const float4& _OtherPos) const;

	// Collision
	void FindTarget();
	Enum_LothricKn_State GetStateToAggroTable();

private:
	std::shared_ptr<GameEngineCollision> PatrolCollision;

	const float FoV = 30.0f;

	MonsterDebugState Debug;
	
};