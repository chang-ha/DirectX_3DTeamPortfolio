#pragma once
#include <GameEngineCore/GameEngineActor.h>

// 설명 :
class TitleLogo : public GameEngineActor
{
	enum class eLogoState
	{
		None,
		BanDai,
		FromSoft,
		DarkSoul,
		AnyButton,
		EndLogo,
		Done,
	};

	enum class eButtonState
	{
		None,
		BStart,
		BExit,
	};

	enum ButtonType
	{
		GameStart,
		GameExit,
	};

public:
	// constructer destructer
	TitleLogo();
	~TitleLogo();

	// delete Function
	TitleLogo(const TitleLogo& _Other) = delete;
	TitleLogo(TitleLogo&& _Other) noexcept = delete;
	TitleLogo& operator = (const TitleLogo& _Other) = delete;
	TitleLogo& operator = (TitleLogo&& _Other) noexcept = delete;

	void Ending();

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;


	// 로고 State
	void Update_BanDai(float _Delta, GameEngineState* _State);
	void Update_FromSoft(float _Delta, GameEngineState* _State);
	void Update_DarkSoul(float _Delta, GameEngineState* _State);
	void Update_AnyButton(float _Delta, GameEngineState* _State);
	void Update_EndLogo(float _Delta, GameEngineState* _State);

	void End_BanDai(GameEngineState* _State);
	void End_FromSoft(GameEngineState* _State);
	void End_DarkSoul(GameEngineState* _State);
	void End_AnyButton(GameEngineState* _State);
	void End_EndLogo(GameEngineState* _State);

	void Start_Done(GameEngineState* _State);

	// 버튼 State
	void Update_BStart(float _Delta, GameEngineState* _State);
	void Update_BExit(float _Delta, GameEngineState* _State);

	void End_BStart(GameEngineState* _State);
	void End_BExit(GameEngineState* _State);

private:
	std::shared_ptr<class GameEngineSpriteRenderer> DarkBack = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> BanDaiNamco_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> FromSoft_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> DarkSouls_Logo = nullptr;
	std::shared_ptr<class GameEngineSpriteRenderer> Inc_Logo = nullptr;

	std::shared_ptr<class GameEngineSpriteRenderer> AnyButtonBack = nullptr;
	std::shared_ptr<class GameEngineUIRenderer> AnyButtonFont;

	void SkipButton(GameEngineState* _State, eLogoState _StateName); // E
	void ButtonCreate();
	std::vector<std::shared_ptr<GameEngineActor>, std::shared_ptr<class GameEngineUIRenderer>> ButtonFont;
	std::shared_ptr<GameEngineUIRenderer> UtilRender;

	float FontScale = 20.0f;
	bool AnyBack = false;
	bool AnyBackColor = false;
	bool FontEnter = false;

	GameEngineState Logostate;

	GameEngineState ButtonState;

};

