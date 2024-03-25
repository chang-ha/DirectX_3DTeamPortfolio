#pragma once

#define UIVolume 0.6f

// 설명 :
class MainUIActor : public GameEngineActor
{
private:
	static GameEngineSoundPlayer UISoundActor;

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

	static void SoundPlay(std::string _Name, int _Loop = 0, float _VolumeValue = UIVolume);

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
	float EmberTime = 6.0f;
	bool BossDeath = false;

};

