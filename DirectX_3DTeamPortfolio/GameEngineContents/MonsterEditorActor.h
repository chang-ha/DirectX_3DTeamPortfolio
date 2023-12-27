#pragma once

// Ό³Έν :
class MonsterEditorActor : public GameEngineActor
{
public:
	// constrcuter destructer
	MonsterEditorActor();
	~MonsterEditorActor();

	// delete Function
	MonsterEditorActor(const MonsterEditorActor& _Other) = delete;
	MonsterEditorActor(MonsterEditorActor&& _Other) noexcept = delete;
	MonsterEditorActor& operator=(const MonsterEditorActor& _Other) = delete;
	MonsterEditorActor& operator=(MonsterEditorActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<GameEngineFBXRenderer> Renderer;

};

