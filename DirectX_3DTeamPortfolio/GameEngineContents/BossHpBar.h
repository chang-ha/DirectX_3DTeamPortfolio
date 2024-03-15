#pragma once


#include <GameEngineCore/GameEngineActor.h>
class BossHpBar : public GameEngineActor
{
	enum struct eHpState
	{
		None,
		Off,
		Appear,
		Add,
	};

public:
	// constructer destructer
	BossHpBar();
	~BossHpBar();

	// delete Function
	BossHpBar(const BossHpBar& _Other) = delete;
	BossHpBar(BossHpBar&& _Other) noexcept = delete;
	BossHpBar& operator = (const BossHpBar& _Other) = delete;
	BossHpBar& operator = (BossHpBar&& _Other) noexcept = delete;

	void SetParent(class Boss_Vordt* _Object);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	// State
	void ChangeState(eHpState _State);
	void StateUpdate(float _Delta);


	void OffStart();
	void OffUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void AddStart();
	void AddUpdate(float _Delta);

private:
	Boss_Vordt* Boss_Object = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Boss_HpBackBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_DamageBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_HpBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Name;

	float BossPrevHp = 0.0f;
	float BossCurHp = 0.0f; // 1328.0f;
	float BossHp = 0.0f; // 1328;

	std::shared_ptr<GameEngineUIRenderer> BossDamageFont;
	eHpState BHpActor = eHpState::Off;
	
	float CurTime = 0.0f;
	float Time = 1.5f;

	GameEngineRandom DamRan;
	int DamageRandom = 0;
	int Damage = 0;
	int SumDam = 0;
	bool Dam = false;

	void DamageCal();
	void BossHpBarUpdate();
};

