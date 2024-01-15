#pragma once
#include "BaseMonster.h"

// Ό³Έν :
class Monster_LothricKn : public BaseMonster
{
	enum class Enum_LothricKn_State
	{
		None,
		Idle_Standing1,
		Unwake,
		Scout,
		Attack11,
		Attack12,
		Attack13,

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


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	void ResourcesLoad();
	void CreateFSM();

	// Start
	void StartIdle_Standing1(GameEngineState* _State);
	void StartUnWake(GameEngineState* _State);
	void StartScout(GameEngineState* _State);
	void StartRH_Attack11(GameEngineState* _State);
	void StartRH_Attack12(GameEngineState* _State);
	void StartRH_Attack13(GameEngineState* _State);

	
	// Update
	void UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State);
	void UpdateUnWake(float _DeltaTime, GameEngineState* _State);
	void UpdateScout(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack11(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack12(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack13(float _DeltaTime, GameEngineState* _State);

public:
	const static Enum_MonsterType Type = Enum_MonsterType::LothricKn;

private:


	
};

