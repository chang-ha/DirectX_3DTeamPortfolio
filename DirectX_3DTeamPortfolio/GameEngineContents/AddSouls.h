#pragma once
#include "UIActor.h"

// 설명 :
class AddSouls : public UIActor
{
	enum class eAddState
	{
		Ready,
		FadeIn,
		Wait,
		FadeOut,
	};

	enum class eScoreState
	{
		Ready,
		UpScale,
		DownScale,
		AddScore,
	};

public:
	// constructer destructer
	AddSouls();
	~AddSouls();

	// delete Function
	AddSouls(const AddSouls& _Other) = delete;
	AddSouls(AddSouls&& _Other) noexcept = delete;
	AddSouls& operator = (const AddSouls& _Other) = delete;
	AddSouls& operator = (AddSouls&& _Other) noexcept = delete;

	static void AddUISoul(int _Souls);

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override {}

	void Reset() override {}

	void DetectSouls();


	// AddState
	void Start_AddState_Ready(GameEngineState* _Parent);
	void Start_AddState_FadeIn(GameEngineState* _Parent); // Fade
	void Start_AddState_Wait(GameEngineState* _Parent); // Fade 1.0f
	void Start_AddState_FadeOut(GameEngineState* _Parent);

	void Update_AddState_Ready(float _Delta, GameEngineState* _Parent);
	void Update_AddState_FadeIn(float _Delta, GameEngineState* _Parent);
	void Update_AddState_Wait(float _Delta, GameEngineState* _Parent); //
	void Update_AddState_FadeOut(float _Delta,GameEngineState* _Parent) ; // Ready, ScoreState.change(UpScale)

	void End_AddState_FadeOut(GameEngineState* _Parent); 

	// ScoreState
	void Start_ScoreState_Ready(GameEngineState* _Parent);
	void Start_ScoreState_UpScale(GameEngineState* _Parent); // 
	void Start_ScoreState_DownScale(GameEngineState* _Parent); // 
	void Start_ScoreState_AddScore(GameEngineState* _Parent); // Font 최소 사이즈?

	void Update_ScoreState_UpScale(float _Delta, GameEngineState* _Parent);
	void Update_ScoreState_DownScale(float _Delta, GameEngineState* _Parent); 
	void Update_ScoreState_AddScore(float _Delta, GameEngineState* _Parent); 

	void End_ScoreState_AddScore(GameEngineState* _Parent); 

	void SetFontFade(const float _Gamma);
	void SetFontScale(const std::shared_ptr<GameEngineUIRenderer>& _Renderer, const float _FontSize);
	void AddScore(int _Score);

	
private:
	std::shared_ptr<GameEngineUIRenderer> SoulsBack;
	std::shared_ptr<GameEngineUIRenderer> AddSoul;
	std::shared_ptr<GameEngineUIRenderer> SumSouls;

	GameEngineUIRenderer* DebugRenderer = nullptr;

	GameEngineState AddState;
	GameEngineState ScoreState;

	static int TotalScore;
	int CurUISouls = 0;
	int PlusScore = 0;
	int RenderScore = 0;
	int TargetScore = 0;


};

