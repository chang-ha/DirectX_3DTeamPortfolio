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
	std::vector<const char*> AniNames;
	Boss_Vordt* Linked_Boss = nullptr;
	bool IsChasingCamera = false;
	bool ChasingFront = false;
	float4 ChasingCameraPos = float4(0.f, 100.f, -1200.f);
};

enum class Enum_BossState
{
	Idle,
	Move,
	Hit_Down_004,
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
	// Howling
	void Idle_Start();
	void Idle_Update(float _Delta);
	void Idle_End();
	// Idle

	// Walk

	//
	void Hit_Down_004_Start();
	void Hit_Down_004_Update(float _Delta);
	void Hit_Down_004_End();
};