#pragma once

enum struct MonsterHpActor
{
	None,
	Off,
	Appear,
	Add,
};

#include <GameEngineCore/GameEngineActor.h>
class MonsterHpBar : public GameEngineActor
{
public:
	// constructer destructer
	MonsterHpBar();
	~MonsterHpBar();

	// delete Function
	MonsterHpBar(const MonsterHpBar& _Other) = delete;
	MonsterHpBar(MonsterHpBar&& _Other) noexcept = delete;
	MonsterHpBar& operator = (const MonsterHpBar& _Other) = delete;
	MonsterHpBar& operator = (MonsterHpBar&& _Other) noexcept = delete;

	void ChangeState(MonsterHpActor _State);
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
	std::shared_ptr<GameEngineSpriteRenderer> Monster_HpBackBar;
	std::shared_ptr<GameEngineSpriteRenderer> Monster_HpBar;
	std::shared_ptr<GameEngineSpriteRenderer> Monster_DamageBar;

	std::shared_ptr<GameEngineSpriteRenderer> MonsterDamageFont;
	MonsterHpActor MHpActor = MonsterHpActor::Off;

	float MonsterPrevHp = 0.0f;
	float MonsterCurHp = 100.0f;
	float MonsterHp = 100.0f;
	int MonsterSoul = 100;

	float CurTime = 0.0f;
	float LimitTime = 1.5f;

	GameEngineRandom DamRan;
	int DamageRandom = 0;
	int Damage = 0;
	int SumDam = 0;
	bool Dam = false;

	void DamageCal();
	void BarUpdate();

};

