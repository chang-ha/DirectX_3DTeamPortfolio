#pragma once

// ���� :
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

	void Reset();
};

enum class Enum_BossState
{
	// Move & Others
	Howling,
	Idle,
	Walk,
	Jump,
	Turn,
	Hitten,
	Death,
	// Attack
	Breath,
	Combo1,
	Combo2,
	Sweap_Twice,
	Hit_Down_001,
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

enum Enum_RotDir
{
	Not_Rot = 0,
	Left = -1,
	Right = 1,
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

	inline void SetTargeting(GameEngineActor* _Target)
	{
		Target = _Target;
	}

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<GameContentsFBXRenderer> BossFBXRenderer;
	std::shared_ptr<GameEngineCollision> BossCollision;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::shared_ptr<Boss_State_GUI> GUI = nullptr;

	// Targeting
	float TargetAngle = 0.f;
	GameEngineActor* Target = nullptr;

	float RotSpeed = 0.f;
	Enum_RotDir RotDir = Enum_RotDir::Not_Rot;

	void CalcuTargetAngle();

	// State
	GameEngineState BossState;

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
	void Walk_Start();
	void Walk_Update(float _Delta);
	void Walk_End();

	// Jump
	void Jump_Start();
	void Jump_Update(float _Delta);
	void Jump_End();

	// Turn
	void Turn_Start();
	void Turn_Update(float _Delta);
	void Turn_End();

	// Turn
	void Hitten_Start();
	void Hitten_Update(float _Delta);
	void Hitten_End();

	// Death
	void Death_Start();
	void Death_Update(float _Delta);
	void Death_End();

	////////////////////////// Attack

	// Breath
	void Breath_Start();
	void Breath_Update(float _Delta);
	void Breath_End();

	// Combo1
	void Combo1_Start();
	void Combo1_Update(float _Delta);
	void Combo1_End();

	// Combo1
	void Combo2_Start();
	void Combo2_Update(float _Delta);
	void Combo2_End();

	// Sweap
	void Sweap_Twice_Start();
	void Sweap_Twice_Update(float _Delta);
	void Sweap_Twice_End();

	// Hit_Down_001
	void Hit_Down_001_Start();
	void Hit_Down_001_Update(float _Delta);
	void Hit_Down_001_End();

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