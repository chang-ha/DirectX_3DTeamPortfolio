#include "PreCompile.h"
#include "AddSouls.h"

#include "BaseMonster.h"


int AddSouls::TotalScore = 0;
void AddSouls::AddUISoul(int _Souls)
{
	TotalScore += _Souls;
}

AddSouls::AddSouls()
{
}

AddSouls::~AddSouls()
{
}

#define SoulsPos {900.0f, -395.0f}
#define FontSize 20.0f

void AddSouls::Start()
{
	const float4 WinHScale = GlobalValue::GetWinScale().Half();

	SoulsBack = CreateComponent<GameEngineUIRenderer>();
	SoulsBack->SetSprite("SoulsBack.Png");
	SoulsBack->Transform.SetLocalPosition({ 835.0f, -433.0f});
	SoulsBack->GetImageTransform().SetLocalScale(float4(160.0f, 30.0f));

	const float4 GrayColor = float4(0.9f, 0.9f, 0.9f);

	// 합쳐질 소울
	AddSoul = CreateComponent<GameEngineUIRenderer>();
	AddSoul->SetText(GlobalValue::OptimusFont, "", FontSize, GrayColor, FW1_RIGHT);
	AddSoul->Transform.SetLocalPosition(float4(SoulsPos));
	AddSoul->On();

	// 합쳐진 소울
	SumSouls = CreateComponent<GameEngineUIRenderer>();
	SumSouls->SetText(GlobalValue::OptimusFont, "0", FontSize, GrayColor, FW1_RIGHT);
	SumSouls->Transform.SetLocalPosition(float4(900.0f, -421.0f));
	SumSouls->On();


	///// AddState
	CreateStateParameter AddState_Ready;
	AddState_Ready.Start = std::bind(&AddSouls::Start_AddState_Ready, this, std::placeholders::_1);

	CreateStateParameter AddState_FadeIn;
	AddState_FadeIn.Start = std::bind(&AddSouls::Start_AddState_FadeIn, this, std::placeholders::_1);
	AddState_FadeIn.Stay = std::bind(&AddSouls::Update_AddState_FadeIn, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter AddState_Wait;
	AddState_Wait.Start = std::bind(&AddSouls::Start_AddState_Wait, this, std::placeholders::_1);
	AddState_Wait.Stay = std::bind(&AddSouls::Update_AddState_Wait, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter AddState_FadeOut;
	AddState_FadeOut.Stay = std::bind(&AddSouls::Update_AddState_FadeOut, this, std::placeholders::_1, std::placeholders::_2);
	AddState_FadeOut.End = std::bind(&AddSouls::End_AddState_FadeOut, this, std::placeholders::_1);


	///// ScoreState
	CreateStateParameter ScoreState_ChangeScale;
	ScoreState_ChangeScale.Start = std::bind(&AddSouls::Start_ScoreState_ChangeScale, this, std::placeholders::_1);
	ScoreState_ChangeScale.Stay = std::bind(&AddSouls::Update_ScoreState_ChangeScale, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter ScoreState_AddScore;
	ScoreState_AddScore.Start = std::bind(&AddSouls::Start_ScoreState_AddScore, this, std::placeholders::_1);
	ScoreState_AddScore.Stay = std::bind(&AddSouls::Update_ScoreState_AddScore, this, std::placeholders::_1, std::placeholders::_2);
	ScoreState_AddScore.End = std::bind(&AddSouls::End_ScoreState_AddScore, this, std::placeholders::_1);

	AddState.CreateState(eAddState::Ready, AddState_Ready);
	AddState.CreateState(eAddState::FadeIn, AddState_FadeIn);
	AddState.CreateState(eAddState::Wait, AddState_Wait);
	AddState.CreateState(eAddState::FadeOut, AddState_FadeOut);


	ScoreState.CreateState(eScoreState::Ready, {});
	ScoreState.CreateState(eScoreState::ChangeScale, ScoreState_ChangeScale);
	ScoreState.CreateState(eScoreState::AddScore, ScoreState_AddScore);

	AddState.ChangeState(eAddState::Ready);
	ScoreState.ChangeState(eScoreState::Ready);
}

void AddSouls::Update(float _Delta)
{
	DetectSouls();

	AddState.Update(_Delta);
	ScoreState.Update(_Delta);
}

void AddSouls::DetectSouls()
{
	if (AddSouls::TotalScore != CurUISouls)
	{
		const int Souls = AddSouls::TotalScore - CurUISouls;
		CurUISouls = AddSouls::TotalScore;

		bool IsReady = (eAddState::Ready == static_cast<eAddState>(AddState.GetCurState()));
		if (IsReady)
		{
			AddSoul->ChangeText("+ " + std::to_string(Souls));
			AddState.ChangeState(eAddState::FadeIn);
		}
	}
}

///// 기능
void AddSouls::SetFontFade(const float _Gamma)
{
	ContentsDebug::NUllCheck(AddSoul.get());
	FontGamma = _Gamma;
	FontGamma = min(FontGamma, 1.0f);
	AddSoul->SetTextAlpha(FontGamma);
}
void AddSouls::AddFontFade(const float _Gamma)
{
	FontGamma += _Gamma;
	SetFontFade(FontGamma);
}
void AddSouls::SetFontScale(const std::shared_ptr<GameEngineUIRenderer>& _Renderer, const float _FontSize)
{
	if (nullptr != _Renderer)
	{
		_Renderer->ChangeFontScale(_FontSize);
	}
}
void AddSouls::AddScore(int _Score)
{
	if (SumSouls)
	{
		SumSouls->ChangeText(std::to_string(_Score));
	}
}
/////

static constexpr float FadeTime = 0.4f;
static constexpr float InitFade = 0.1f;

/////AddState
void AddSouls::Start_AddState_Ready(GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(AddSoul.get());
	AddSoul->Off();
	AddSoul->Transform.SetLocalPosition(SoulsPos);
}
void AddSouls::Start_AddState_FadeIn(GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(AddSoul.get());
	AddFontSize = FontSize;
	SetFontFade(0.1f);
	AddSoul->On();
}
void AddSouls::Start_AddState_Wait(GameEngineState* _Parent)
{
	SetFontScale(AddSoul, FontSize);
	SetFontFade(1.0f);
}
void AddSouls::Update_AddState_FadeIn(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > FadeTime)
	{
		_Parent->ChangeState(eAddState::Wait);
		return;
	}

	const float UpSize = 10.0f;
	float AddSize = UpSize * _Delta / FadeTime;
	if (_Parent->GetStateTime() > FadeTime * 0.5f)
	{
		AddSize *= -1.0f;
	}

	AddFontSize += AddSize;

	const float PlusGammaValue = _Delta * (1.0f - InitFade) / FadeTime;
	AddFontFade(PlusGammaValue);
	SetFontScale(AddSoul, AddFontSize);
}
void AddSouls::Update_AddState_Wait(float _Delta, GameEngineState* _Parent)
{
	const float WaitTime = 1.f;
	if (_Parent->GetStateTime() > WaitTime)
	{
		_Parent->ChangeState(eAddState::FadeOut);
	}
}
void AddSouls::Update_AddState_FadeOut(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > FadeTime)
	{
		_Parent->ChangeState(eAddState::Ready);
	}

	const float DownSpeed = 15.f;
	const float AddForce = -DownSpeed * _Delta / FadeTime;
	AddSoul->Transform.AddLocalPosition(float4(0.0f, AddForce));
	const float PlusGammaValue = _Delta * (1.0f - InitFade) / FadeTime;
	AddFontFade(-PlusGammaValue);
}

void AddSouls::End_AddState_FadeOut(GameEngineState* _Parent)
{
	bool StateReady = (eScoreState::Ready == static_cast<eScoreState>(ScoreState.GetCurState()));
	if (StateReady)
	{
		ScoreState.ChangeState(eScoreState::ChangeScale);
		return;
	}
}
/////




///// ScoreState

void AddSouls::Start_ScoreState_ChangeScale(GameEngineState* _Parent)
{
	const int Score = AddSouls::TotalScore - RenderScore;
	TargetScore = AddSouls::TotalScore;
	PlusScore = Score;

	ScoreFontSize = FontSize;
}

void AddSouls::Update_ScoreState_ChangeScale(float _Delta, GameEngineState* _Parent)
{
	const float StateTime = 0.4f;
	if (_Parent->GetStateTime() > StateTime)
	{
		_Parent->ChangeState(eScoreState::AddScore);
		return;
	}

	const float ChangeFontSize = 10.f;
	float AddSize = ChangeFontSize * _Delta / StateTime;
	if (_Parent->GetStateTime() > StateTime * 0.5f)
	{
		AddSize *= -1.0f;
	}

	ScoreFontSize += AddSize;
	SetFontScale(SumSouls, ScoreFontSize);
}

void AddSouls::Start_ScoreState_AddScore(GameEngineState* _Parent)
{
	ScoreFontSize = FontSize;
	SetFontScale(SumSouls, FontSize);
}

static constexpr float AddScore_StateTime = 0.5f;

void AddSouls::Update_ScoreState_AddScore(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > AddScore_StateTime)
	{
		_Parent->ChangeState(eScoreState::Ready);
		return;
	}

	const float AddRenderScore = (static_cast<float>(PlusScore) / AddScore_StateTime) * _Delta;
	RenderScore += static_cast<int>(AddRenderScore);
	AddScore(RenderScore);
}

void AddSouls::End_ScoreState_AddScore(GameEngineState* _Parent)
{
	SumSouls->ChangeText(std::to_string(TargetScore));
	RenderScore = TargetScore;
}