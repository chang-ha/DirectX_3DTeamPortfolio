#pragma once

// Ό³Έν :
class Boss_State_GUI : public GameEngineGUIWindow
{
	friend class Boss_Vordt;
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	
protected:

private:
	Boss_Vordt* Linked_Boss = nullptr;
	bool IsChasingCamera = false;
	bool ChasingFront = false;
};

enum class Enum_BossState
{
	Idle,
	Move,
};

class Boss_Vordt : public GameEngineActor
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

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameContentsFBXRenderer> BossFBXRenderer;
	std::shared_ptr<GameEngineCollision> BossCollision;
	std::shared_ptr<class GameEnginePhysXSphere> Sphere;
	std::shared_ptr<class GameEngjnePhysXBox> Box;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::shared_ptr<Boss_State_GUI> GUI = nullptr;

	// State
	GameEngineState BossState;
	void IdleStart();
	void IdleUpdate(float _Delta);
	void IdleEnd();
};

