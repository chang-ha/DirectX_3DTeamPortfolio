#pragma once
#include "UIActor.h"

class NewBossUI : public UIActor
{
	enum struct eBarState
	{
		None,
		Active_Idle,
		Active_Hit,
		ZERO_HP,
	};

	enum struct eFontState
	{
		None,
		Awake,
		Idle,
		Hit,
		End,
	};

public:
	// constructer destructer
	NewBossUI();
	~NewBossUI();

	// delete Function
	NewBossUI(const NewBossUI& _Other) = delete;
	NewBossUI(NewBossUI&& _Other) noexcept = delete;
	NewBossUI& operator = (const NewBossUI& _Other) = delete;
	NewBossUI& operator = (NewBossUI&& _Other) noexcept = delete;

	void SetParent(class Boss_Vordt* _Object);

	void Awake();

	// 디버깅용
	void BossDamage(int _Damgae);

	// void Reset() override;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	// 유효성 체크
	void ValidityCheck();

	// State
	void InitState();

	// State_Bar
	void Start_Bar_Idle(GameEngineState* _Parent);
	void Start_Bar_End(GameEngineState* _Parent);

	void Update_Bar_Idle(float _Delta, GameEngineState* _Parent);
	void Update_Bar_Hit(float _Delta, GameEngineState* _Parent);
	void Update_Bar_End(float _Delta, GameEngineState* _Parent);

	void SetDamageGauge(int _BossHp);
	void SetHPGauge(int _BossHp);

private:
	class Boss_Vordt* pBoss = nullptr;

	std::shared_ptr<GameEngineUIRenderer> Boss_HpBackBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_DamageBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_HpBar;
	std::shared_ptr<GameEngineUIRenderer> Boss_Name;
	std::shared_ptr<GameEngineUIRenderer> BossDamageFont;

	GameEngineState BarState;
	GameEngineState FontState;

	int BossMaxHp = 0;
	int BossHp = 0;
	
};