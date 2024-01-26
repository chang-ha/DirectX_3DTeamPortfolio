#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TitleLogo : public GameEngineActor
{
public:
	// constructer destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator = (const TitleLogo& _Other) = delete;
	TitleLogo& operator = (TitleLogo&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DarkBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BanDaiNamco_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FromSoft_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DarkSouls_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Inc_Logo = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> AnyButtonBack = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> FontRender;
	float FontScale = 20.0f;
	bool AnyBack = false;
	bool AnyBackColor = false;
	bool FontEnter = false;

	float Time = 0.0f;
	float FromSoftLogoTime = 5.0f;

};

