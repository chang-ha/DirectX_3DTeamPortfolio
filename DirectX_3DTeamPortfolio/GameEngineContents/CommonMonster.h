#pragma once

// Ό³Έν :
class CommonMonster : public GameEngineActor
{
public:
	// constrcuter destructer
	CommonMonster();
	~CommonMonster();

	// delete Function
	CommonMonster(const CommonMonster& _Other) = delete;
	CommonMonster(CommonMonster&& _Other) noexcept = delete;
	CommonMonster& operator=(const CommonMonster& _Other) = delete;
	CommonMonster& operator=(CommonMonster&& _Other) noexcept = delete;

	inline std::shared_ptr<GameContentsFBXRenderer> GetFBXRenderer() { return MainRenderer; }

protected:
	void Start() override;
	void Update(float _Delta) override {}
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override {}

protected:
	std::shared_ptr<GameContentsFBXRenderer> MainRenderer;
	GameEngineState MainState;

private:


};

