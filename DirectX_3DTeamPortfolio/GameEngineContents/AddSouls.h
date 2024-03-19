#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum struct SoulsActor
{
	None,
	Appear,
	Add,
	Sum,
};

// Ό³Έν :
class AddSouls : public GameEngineActor
{
public:
	// constructer destructer
	AddSouls();
	~AddSouls();

	// delete Function
	AddSouls(const AddSouls& _Other) = delete;
	AddSouls(AddSouls&& _Other) noexcept = delete;
	AddSouls& operator = (const AddSouls& _Other) = delete;
	AddSouls& operator = (AddSouls&& _Other) noexcept = delete;

	void ChangeState(SoulsActor _State);
	void StateUpdate(float _Delta);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void AppearStart();
	void AddStart();
	void SumStart();

	void AppearUpdate(float _Delta);
	void AddUpdate(float _Delta);
	void SumUpdate(float _Delta);

	void FontUpdate();

private:
	float4 WindowScale = float4::ZERO;
	std::shared_ptr<GameEngineUIRenderer> SoulsBack;
	std::shared_ptr<GameEngineUIRenderer> AddSoul;
	std::shared_ptr<GameEngineUIRenderer> SumSouls;

	int Souls = 0;
	int SoulAdd = 0;

	float FontTime = 0.0f;
	float FontSizeTime = 0.3f;
	float FontSize = 14.0f;

	SoulsActor SoulState = SoulsActor::None;
};

