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

	void CreateBossUI(class Boss_Vordt* _pBoss);
	void CheckEsteUI(class Player* _pPlayer);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class BossHpBar> BossHpObject = nullptr;
	std::shared_ptr<class UIPlayerEquip> EsteUI = nullptr;
	//// PlayerIcon
	std::shared_ptr<GameEngineUIRenderer> PlayerIcon;

	std::shared_ptr<GameEngineUIRenderer> Textures;

	float ScaleSpeed = 100.0f;
};

