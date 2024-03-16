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
	void CreateAndCheckEsteUI(class Player* _pPlayer);
	void CreateAndCheckPlayerGaugeBar(class Player* _pPlayer);

	void AllUIActorReset();

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::shared_ptr<class NewBossUI> BossHpObject = nullptr;
	std::shared_ptr<class UIPlayerEquip> EsteUI = nullptr;
	std::shared_ptr<class UIPlayerGaugeBar> PlayerGaugeBar = nullptr;

	//// PlayerIcon
	std::shared_ptr<GameEngineUIRenderer> PlayerIcon;
};

