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

	void InitUIPosition(class BaseMonster* pOwner, const float4* _pHeadBonePos);


protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	// Location 
	void PositionUpdate();

	// State
	void ChangeState(MonsterHpActor _State);
	void StateUpdate(float _Delta);

	void OffStart();
	void OffUpdate(float _Delta);

	void AppearStart();
	void AppearUpdate(float _Delta);

	void AddStart();
	void AddUpdate(float _Delta);

private:
	class BaseMonster* pOwner = nullptr;

	std::shared_ptr<GameEngineSpriteRenderer> BackBarRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> HpBarRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DamageBarRenderer;
	std::shared_ptr<GameEngineSpriteRenderer> DamageFontRenderer;
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

	// Poisition Init Var
	bool InitValue = false;

	const float4* BonePosPointer = nullptr;
	// 컴파일 타입 어셜션?
	static constexpr float HeightDist = 50.0f;

	void DamageCal();
	void MonsterBarUpdate();

};

