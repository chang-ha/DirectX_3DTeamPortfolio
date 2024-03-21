#pragma once
#include "UIActor.h"

class MonsterHpBar : public UIActor
{
	enum struct eState
	{
		None,
		Awake,
		Idle,
		Off,
	};

public:
	// constructer destructer
	MonsterHpBar();
	~MonsterHpBar();

	// delete Function
	MonsterHpBar(const MonsterHpBar& _Other) = delete;
	MonsterHpBar(MonsterHpBar&& _Other) noexcept = delete;
	MonsterHpBar& operator = (const MonsterHpBar& _Other) = delete;
	MonsterHpBar& operator = (MonsterHpBar&& _Other) noexcept = delete;

	void InitUIPosition(class BaseMonster* pOwner, const float4* _pHeadBonePos);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void Reset() override;

	// Location 
	void PositionUpdate();

	// State
	void InitState();

	// Start
	void Start_Awake(GameEngineState* _Parent);
	void Start_Off(GameEngineState* _Parent);

	// Update
	void Update_Idle(float _Delta, GameEngineState* _Parent);
	void Update_Off(float _Delta, GameEngineState* _Parent);

	void RendererOn();
	void RendererOff();

	void SetDamageGauge();
	void SetHPGauge();

private:
	class BaseMonster* pOwner = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> BackBarRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> HpBarRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DamageBarRenderer;


	// Poisition Init Var
	bool RenderValue = false;
	bool InitValue = false;

	const float4* BonePosPointer = nullptr;

	static constexpr float HeightDist = 50.0f;

	// State
	GameEngineState MainState;

	float BackBarScale = 0.0f;
	int MaxHp = 0;
	int RenderHp = 0;
	int DamgeRenderHp = 0;

	float OffTime = 0.0f;
	float DamageRenderTime = 0.0f;

};