#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class MainUIActor : public GameEngineActor
{
public:
	// constructer destructer
	MainUIActor();
	~MainUIActor();

	// delete Function
	MainUIActor(const MainUIActor& _Other) = delete;
	MainUIActor(MainUIActor&& _Other) noexcept = delete;
	MainUIActor& operator = (const MainUIActor& _Other) = delete;
	MainUIActor& operator = (MainUIActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	//// PlayerIcon
	std::shared_ptr<GameEngineUIRenderer> PlayerIcon;

	//// BackBar
	std::shared_ptr<GameEngineUIRenderer> HpBackBar_Left;
	std::shared_ptr<GameEngineUIRenderer> HpBackBar_Center;
	std::shared_ptr<GameEngineUIRenderer> HpBackBar_Right;

	std::shared_ptr<GameEngineUIRenderer> MpBackBar;
	std::shared_ptr<GameEngineUIRenderer> StaminaBackBar;

	//// HP Bar
	std::shared_ptr<GameEngineUIRenderer> MainHpBar;
	float CurHpScale = 0.0f;

	//// PP Bar
	std::shared_ptr<GameEngineUIRenderer> MainPPBar;

	float ScaleSpeed = 100.0f;
};

