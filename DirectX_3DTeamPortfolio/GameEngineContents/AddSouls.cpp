#include "PreCompile.h"
#include "AddSouls.h"

#include "BaseMonster.h"

#include "UI_Utils.h"


int AddSouls::TotalScore = 0;
void AddSouls::AddUISoul(int _Souls)
{
	TotalScore += _Souls;
}

AddSouls::AddSouls()
{
	GameEngineInput::AddInputObject(this);
}

AddSouls::~AddSouls()
{
}

#define SoulsPos {390.0f, -180.0f}

void AddSouls::Start()
{
	const float4 WinHScale = GlobalValue::GetWinScale().Half();

	SoulsBack = CreateComponent<GameEngineUIRenderer>();
	SoulsBack->SetSprite("SoulsBack.Png");
	SoulsBack->Transform.SetLocalPosition({ WinHScale.X - 90.0f, -WinHScale.Y + 90.0f});

	// 합쳐질 소울
	// Souls = CreateComponent<GameEngineUIRenderer>();
	// Souls->SetText(GlobalValue::OptimusFont, std::to_string(SoulAdd), 14.0f, float4{ 1,0,0,1 }, FW1_RIGHT);
	// Souls->Transform.SetLocalPosition({ WindowScale.X - 30.0f , -WindowScale.Y + 130.0f });
	// Souls->Off();

	// 합쳐질 소울
	AddSoul = CreateComponent<GameEngineUIRenderer>();
	AddSoul->SetText(GlobalValue::OptimusFont, "", 14.0f, float4{1,0,0,1}, FW1_RIGHT);
	// AddSoul->Transform.SetLocalPosition({ WindowScale.X - 30.0f , -WindowScale.Y + 130.0f });
	AddSoul->Off();

	// 합쳐진 소울
	SumSouls = CreateComponent<GameEngineUIRenderer>();
	SumSouls->SetText(GlobalValue::OptimusFont, "", 14.0f, float4{0,1,0,1}, FW1_RIGHT);
	SumSouls->On();
	// SumSouls->Transform.SetLocalPosition({ WindowScale.X - 30.0f ,  -WindowScale.Y + 100.0f});

	DebugRenderer;

	CreateStateParameter ScoreState_Ready;
	ScoreState_Ready.Start = std::bind(&AddSouls::Start_ScoreState_Ready, this, std::placeholders::_1);

	CreateStateParameter ScoreState_UpScale;
	CreateStateParameter ScoreState_DownScale;

	CreateStateParameter ScoreState_AddScore;
	ScoreState_AddScore.Start = std::bind(&AddSouls::Start_ScoreState_AddScore, this, std::placeholders::_1);
	ScoreState_AddScore.Stay = std::bind(&AddSouls::Update_ScoreState_AddScore, this, std::placeholders::_1, std::placeholders::_2);
	ScoreState_AddScore.End = std::bind(&AddSouls::End_ScoreState_AddScore, this, std::placeholders::_1);

	ScoreState.CreateState(eScoreState::Ready, ScoreState_Ready);
	ScoreState.CreateState(eScoreState::AddScore, ScoreState_AddScore);
}

void AddSouls::Update(float _Delta)
{
	AddState.Update(_Delta);
	ScoreState.Update(_Delta);

	if (GameEngineInput::IsDown('2', this))
	{
		TotalScore += ContentsRandom::RandomInt(1, 5) * 100;
		ScoreState.ChangeState(eScoreState::AddScore);
	}

	if (nullptr != DebugRenderer)
	{
		UIHandler::Update(_Delta, DebugRenderer, this);
	}

	// StateUpdate(_Delta);
	// // 폰트 실시간반영
	// FontUpdate();
}

void AddSouls::DetectSouls()
{
	if (AddSouls::TotalScore != CurUISouls)
	{
		const int Souls = AddSouls::TotalScore - CurUISouls;
		TotalScore += Souls;

		bool IsReady = (eAddState::Ready == static_cast<eAddState>(AddState.GetCurState()));
		if (IsReady)
		{
			AddSoul->ChangeText(std::to_string(Souls));
			AddState.ChangeState(eAddState::FadeIn);
		}
	}
}

void AddSouls::SetFontFade(const float _Gamma)
{
	if (AddSoul)
	{
		AddSoul->SetTextAlpha(_Gamma);
	}
}

void AddSouls::SetFontScale(const std::shared_ptr<GameEngineUIRenderer>& _Renderer, const float _FontSize)
{
	if (nullptr != _Renderer)
	{
		AddSoul->ChangeFontScale(_FontSize);
	}
}

void AddSouls::AddScore(int _Score)
{
	if (SumSouls)
	{
		SumSouls->ChangeText(std::to_string(_Score));
	}
}

void AddSouls::Start_ScoreState_Ready(GameEngineState* _Parent)
{
}

void AddSouls::Start_ScoreState_UpScale(GameEngineState* _Parent)
{
	const int Score = AddSouls::TotalScore - RenderScore;
	TargetScore = AddSouls::TotalScore;
	PlusScore = Score;
	ScoreState.ChangeState(eScoreState::AddScore);
}

void AddSouls::Start_ScoreState_AddScore(GameEngineState* _Parent)
{

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
}

//
//void AddSouls::FontUpdate()
//{
//	AddSoul->SetText(GlobalValue::OptimusFont, "+" + std::to_string(SoulAdd), FontSize, float4{ 1,0,0,1 }, FW1_RIGHT);
//}
//
//void AddSouls::ChangeState(SoulsActor _State)
//{
//	if (_State != SoulState)
//	{
//		switch (_State)
//		{
//		case SoulsActor::Appear:
//			AppearStart();
//			break;
//		case SoulsActor::Add:
//			AddStart();
//			break;
//		case SoulsActor::Sum:
//			SumStart();
//			break;
//		case SoulsActor::None:
//			break;
//		}
//	}
//
//	SoulState = _State;
//}
//
//void AddSouls::StateUpdate(float _Delta)
//{
//	switch (SoulState)
//	{
//	case SoulsActor::Appear:
//		return AppearUpdate(_Delta);
//	case SoulsActor::Add:
//		return AddUpdate(_Delta);
//	case SoulsActor::Sum:
//		return SumUpdate(_Delta);
//	case SoulsActor::None:
//		break;
//	}
//}
//
//// 나타나서 크기가 커지는 곳
//void AddSouls::AppearStart()
//{
//	AddSoul->On();
//	AddSoul->Transform.SetLocalPosition({ WindowScale.X - 30.0f , -WindowScale.Y + 125.0f });
//	
//	SoulAdd += 100;
//	AddSoul->SetText(GlobalValue::OptimusFont,"+"+std::to_string(SoulAdd), FontSize, float4{1,0,0,1}, FW1_RIGHT);
//	FontTime = 0.0f;
//}
//
//void AddSouls::AppearUpdate(float _Delta)
//{
//	FontTime += _Delta;
//	FontSize += 10 * _Delta;
//
//	if (FontTime >= FontSizeTime)
//	{
//		AddSouls::ChangeState(SoulsActor::Add);
//		return;
//	}
//}
//
//// 크기가 줄어들고 나서 내려가는 곳
//void AddSouls::AddStart()
//{
//	FontTime = 0.0f;
//}
//
//void AddSouls::AddUpdate(float _Delta)
//{
//	FontTime += _Delta;
//	FontSize -= 10 * _Delta;
//
//	AddSoul->Transform.AddLocalPosition({ 0.0f, -50.0f * _Delta });
//
//	if (FontTime >= FontSizeTime)
//	{
//		AddSouls::ChangeState(SoulsActor::Sum);
//		AddSoul->Off();
//	}
//}
//
//// 내려온 소울이 합쳐지는 곳
//void AddSouls::SumStart()
//{
//	Souls += SoulAdd;
//	SumSouls->SetText(GlobalValue::OptimusFont, std::to_string(Souls), 14.0f, float4{ 1,1,1,1 }, FW1_RIGHT);
//}
//
//void AddSouls::SumUpdate(float _Delta)
//{
//
//}
//
//
//void AddSouls::LevelEnd(GameEngineLevel* _NextLevel)
//{
//	Death();
//}