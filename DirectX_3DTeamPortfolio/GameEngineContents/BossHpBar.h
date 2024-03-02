#pragma once

enum struct BossHpActor
{
	None,
	Off,
	Appear,
	Add,
};

#include <GameEngineCore/GameEngineActor.h>
class BossHpBar : public GameEngineActor
{
public:
	// constructer destructer
	BossHpBar();
	~BossHpBar();

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete;
	BossHpBar(BossHpBar&& _Other) noexcept = delete;
	BossHpBar& operator = (const BossHpBar& _Other) = delete;
	BossHpBar& operator = (BossHpBar&& _Other) noexcept = delete;

	void ChangeState(BossHpActor _State);
	void StateUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

	void OffStart();
	void OffUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void AddStart();
	void AddUpdate(float _Delta);

private:
	std::shared_ptr<GameEngineUIRenderer> Boss_HpBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Hp;
	std::shared_ptr<GameEngineUIRenderer> Boss_DamageBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Name;

	float BossPrevHp = 0.0f;
	float BossCurHp = 1328;
	float BossHp = 1328;
	int BossSoul = 3000;

	std::shared_ptr<GameEngineUIRenderer> BossDamageFont;
	BossHpActor BHpActor = BossHpActor::Off;
	
	float CurTime = 0.0f;
	float Time = 1.5f;
	int i = 0;

	GameEngineRandom DamRan;
	int DamageRandom = 0;
	int Damage = 0;
	int SumDam = 0;
	bool Dam = false;

	void DamageCal();
	void BossHpBarUpdate();
};

