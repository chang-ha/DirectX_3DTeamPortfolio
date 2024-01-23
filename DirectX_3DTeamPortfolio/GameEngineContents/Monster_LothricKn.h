#pragma once
#include "BaseMonster.h"

// Ό³Έν :
class Monster_LothricKn : public BaseMonster
{
	enum class Enum_LothricKn_State
	{
		None,
		Sleep,
		Idle_Standing1,
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
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

private:
	void ResourcesLoad();
	void CreateFSM();

	// Start
	void StartSleep(GameEngineState* _State);
	void StartIdle_Standing1(GameEngineState* _State);
	void StartScout(GameEngineState* _State);
	void StartRH_Attack11(GameEngineState* _State);
	void StartRH_Attack12(GameEngineState* _State);
	void StartRH_Attack13(GameEngineState* _State);

	// Update
	void UpdateSleep(float _DeltaTime, GameEngineState* _State);
	void UpdateIdle_Standing1(float _DeltaTime, GameEngineState* _State);
	void UpdateScout(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack11(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack12(float _DeltaTime, GameEngineState* _State);
	void UpdateRH_Attack13(float _DeltaTime, GameEngineState* _State);

	// State Func
	bool IsFrame(int _StartFrame, int _EndFrame = -1) const;
	void DebugCheck(float _Distance) const;

	// Collision
	template <typename EnumType, typename ActorType>
	std::shared_ptr<ActorType> FindEnemy(EnumType _ColOrder)
	{
		return TempFindEnemy<ActorType>(static_cast<int>(_ColOrder));
	}

	template <typename ActorType> 
	std::shared_ptr<ActorType> TempFindEnemy(int _ColOrder)
	{


		return;
	}

	std::shared_ptr<GameEngineActor> FindDummyByCollision();

private:
	std::shared_ptr<GameEngineCollision> AggroCollision;

	std::weak_ptr<GameEngineActor> wpDummy;
	
};