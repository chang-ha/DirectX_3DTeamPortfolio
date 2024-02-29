#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
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

protected:
	void Start() override;
	void Update(float _Delta) override;

	void Release() override;

private:
	std::shared_ptr<GameEngineUIRenderer> Boss_HpBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Hp;
	std::shared_ptr<GameEngineUIRenderer> Boss_DamageBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Name;

	float BossPrevHp = 0;
	float BossCurHp = 1328;
	float BossHp = 1328;
	int BossSoul = 3000;
	//float Damage = 0;

	std::shared_ptr<GameEngineUIRenderer> BossDamageFont;
	
	float CurTime = 0.0f;
	float Time = 1.0f;
	int i = 0;

	GameEngineRandom DamRan;
	int DamageRandom = 0;
	int Damage = 0;
	bool Dam = false;

	void DamageCal();
};

