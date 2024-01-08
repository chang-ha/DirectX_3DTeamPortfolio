#pragma once

enum class Enum_BossState
{
	Idle,
	Move,
};

class Boss_Vordt : public GameEngineActor
{
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
	std::shared_ptr<GameEngineFBXRenderer> BossFBXRenderer;
	std::shared_ptr<GameEngineCollision> BossCollision;
	std::shared_ptr<class GameEnginePhysXSphere> Sphere;
	std::shared_ptr<class GameEngjnePhysXBox> Box;
	std::shared_ptr<class GameEnginePhysXCapsule> Capsule;
	std::shared_ptr<class GameEnginePhysXTriMesh> TriMesh;
	GameEngineState BossState;
};

