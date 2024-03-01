#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class DamageRenderer : public GameEngineActor
{
public:
	// constructer destructer
	DamageRenderer();
	~DamageRenderer();

	// delete Function
	DamageRenderer(const DamageRenderer& _Other) = delete;
	DamageRenderer(DamageRenderer&& _Other) noexcept = delete;
	DamageRenderer& operator = (const DamageRenderer& _Other) = delete;
	DamageRenderer& operator = (DamageRenderer&& _Other) noexcept = delete;

	void PushDamage(GameEngineObject* _Object, size_t _Damage);

	void DeleteDamage();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

	void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
	std::list<std::vector<std::shared_ptr<GameEngineSpriteRenderer>>*> DamageRenderList;
	std::shared_ptr<GameEngineSpriteRenderer> NewNumberRender;

	GameEngineRandom DamRan;
	float DamageRandom = 0.0f;
	float Damage = 0.0f;

	float CurTime = 0.0f;
	float Disappear = 1.0f;
};

