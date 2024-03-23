#pragma once

// 설명 :
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

	void CreateAlertManger();
	void CreateBossUI(class Boss_Vordt* _pBoss);
	void CreateAndCheckEsteUI(class Player* _pPlayer);
	void CreateAndCheckPlayerGaugeBar(class Player* _pPlayer);

	void AllUIActorReset();

	void BossUIOn();

	std::shared_ptr<class UIPlayerGaugeBar> GetPlayerUI() { return PlayerGaugeBar; }

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release()override;

	void LevelStart(GameEngineLevel* _PrevLevel) override {}
	void LevelEnd(GameEngineLevel* _NextLevel) override {}

	// 액터 생성
	

private:
	std::shared_ptr<class UIAlertMaanger> AlertMaanger = nullptr;
	std::shared_ptr<class BossHpUI> BossHpObject = nullptr;
	std::shared_ptr<class UIPlayerEquip> EsteUI = nullptr;
	std::shared_ptr<class UIPlayerGaugeBar> PlayerGaugeBar = nullptr;

	class Boss_Vordt* Boss_Object;
	bool BossDeath = false;

};

