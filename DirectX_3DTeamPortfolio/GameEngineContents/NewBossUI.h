#pragma once

//
//#include <GameEngineCore/GameEngineActor.h>
//class NewBossUI : public GameEngineActor
//{
//	enum struct eBarState
//	{
//		None,
//		Awake,
//		Idle,
//		Hit,
//		End,
//	};
//
//	enum struct eFontState
//	{
//		None,
//		Awake,
//		Idle,
//		Hit,
//		End,
//	};
//
//public:
//	// constructer destructer
//	NewBossUI();
//	~NewBossUI();
//
//	// delete Function
//	NewBossUI(const NewBossUI& _Other) = delete;
//	NewBossUI(NewBossUI&& _Other) noexcept = delete;
//	NewBossUI& operator = (const NewBossUI& _Other) = delete;
//	NewBossUI& operator = (NewBossUI&& _Other) noexcept = delete;
//
//	void SetParent(class Boss_Vordt* _Object);
//
//	void AwakeState();
//	void DeathProcess();
//
//protected:
//	void Start() override;
//	void Update(float _Delta) override;
//	void Release() override;
//
//private:
//	void ValidityCheck();
//
//	// State
//	void InitState();
//
//	void Start_Bar_Awake(GameEngineState* _Parent);
//	void Start_Bar_Idle(GameEngineState* _Parent);
//	void Start_Bar_Hit(GameEngineState* _Parent);
//	void Start_Bar_End(GameEngineState* _Parent);
//
//	void Update_Bar_Idle(float _Delta, GameEngineState* _Parent);
//	void Update_Bar_Hit(float _Delta, GameEngineState* _Parent);
//
//	void SetDamageGauge(int _BossHp);
//
//	void DamageCal();
//	void BossBarUpdate();
//
//private:
//	Boss_Vordt* Boss_Object = nullptr;
//
//	std::shared_ptr<GameEngineUIRenderer> Boss_HpBackBar;
//	std::shared_ptr<GameEngineUIRenderer> Boss_DamageBar;
//	std::shared_ptr<GameEngineUIRenderer> Boss_HpBar;
//	std::shared_ptr<GameEngineUIRenderer> Boss_Name;
//
//	std::shared_ptr<GameEngineUIRenderer> BossDamageFont;
//
//	GameEngineState BarState;
//	GameEngineState FontState;
//
//	int BossMaxHp = 0;
//	int BossHp = 0;
//	
//};
//
