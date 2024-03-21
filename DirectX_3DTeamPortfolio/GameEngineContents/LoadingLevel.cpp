#include "PreCompile.h"
#include "LoadingLevel.h"

#include "Stage_Lothric.h"

#include "AllFadeEffect.h"

#include "UILoading.h"

static constexpr const char* PlayLevelName = "STAGE_LOTHRIC";

Enum_LevelFlag LoadingLevel::LoadingFlag = Enum_LevelFlag::None;
LoadingLevel::LoadingLevel() 
{
}

LoadingLevel::~LoadingLevel() 
{
}


void LoadingLevel::Start()
{
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	FadeObject = GetLevelRenderTarget()->CreateEffect<AllFadeEffect>();
	FadeObject->Off();

	CreateStateParameter LoadingState;
	LoadingState.Start = std::bind(&LoadingLevel::Start_Loading, this, std::placeholders::_1);
	LoadingState.Stay = std::bind(&LoadingLevel::Update_Loading, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter WaitState;
	WaitState.Stay = std::bind(&LoadingLevel::Update_Wait, this, std::placeholders::_1, std::placeholders::_2);

	CreateStateParameter FadeOutState;
	FadeOutState.Start = std::bind(&LoadingLevel::Start_FadeOut, this, std::placeholders::_1);
	FadeOutState.Stay = std::bind(&LoadingLevel::Update_FadeOut, this, std::placeholders::_1, std::placeholders::_2);

	LevelState.CreateState(eLoadingState::Loading, LoadingState);
	LevelState.CreateState(eLoadingState::Wait, WaitState);
	LevelState.CreateState(eLoadingState::FadeOut, FadeOutState);

	LoadingObject = CreateActor<UILoading>(Enum_UpdateOrder::UI);

	LoadingThread.Initialize("LoadingThread", 1);
}

void LoadingLevel::Update(float _Delta) 
{
	LevelState.Update(_Delta);
}

void LoadingLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	if (Enum_LevelFlag::Loading_Resouce == LoadingFlag
		|| Enum_LevelFlag::Loading_Reset == LoadingFlag)
	{
		LevelState.ChangeState(eLoadingState::Loading);
	}
}

void LoadingLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	LoadingFlag = Enum_LevelFlag::Play;
}


void LoadingLevel::Start_Loading(GameEngineState* _Parent)
{
	if (LoadingObject)
	{
		LoadingObject->On();
	}
	
	if (nullptr != FadeObject)
	{
		FadeObject->FadeIn();
		FadeObject->SetFadeSpeed(2.0f);
	}

	std::map<std::string, std::shared_ptr<GameEngineLevel>>& AllLevel = GameEngineCore::GetAllLevel();
	for (const std::pair<std::string, std::shared_ptr<GameEngineLevel>>& Level : AllLevel)
	{
		if (Level.first != PlayLevelName)
		{
			continue;
		}

		Stage_Lothric* TargetLevel = dynamic_cast<Stage_Lothric*>(Level.second.get());
		if (nullptr == TargetLevel)
		{
			MsgBoxAssert("존재하지 않는 레벨입니다.");
			return;
		}

		switch (LoadingFlag)
		{
		case Enum_LevelFlag::None:
			break;
		case Enum_LevelFlag::Loading_Resouce:
		{
			LoadingThread.Work(std::bind(&Stage_Lothric::ResLoading, TargetLevel));
		}
			break;
		case Enum_LevelFlag::Loading_Reset:
		{
			Stage_Lothric::ResetLoadingDone = false;
			LoadingThread.Work(std::bind(&Stage_Lothric::ResetLoading, TargetLevel));
		}
			break;
		case Enum_LevelFlag::Play:
			break;
		default:
			break;
		}

		break;
	}
}

void LoadingLevel::Update_Loading(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != FadeObject)
	{
		bool FadeDone = (false == FadeObject->IsUpdate());
		if (FadeDone)
		{
			switch (LoadingFlag)
			{
			case Enum_LevelFlag::Loading_Resouce:
			{
				if (true == Stage_Lothric::ResLoadingDone)
				{
					LevelState.ChangeState(eLoadingState::Wait);
					return;
				}
			}
				break;
			case Enum_LevelFlag::Loading_Reset:
			{
				if (true == Stage_Lothric::ResetLoadingDone)
				{
					LevelState.ChangeState(eLoadingState::Wait);
					return;
				}
			}
				break;
			default:
				break;
			}
		}
	}
}

void LoadingLevel::Update_Wait(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 2.0f)
	{
		LevelState.ChangeState(eLoadingState::FadeOut);
		return;
	}
}

void LoadingLevel::Start_FadeOut(GameEngineState* _Parent)
{
	if (nullptr != FadeObject)
	{
		FadeObject->FadeOut();
	}
}

void LoadingLevel::Update_FadeOut(float _Delta, GameEngineState* _Parent)
{
	if (nullptr != FadeObject)
	{
		bool FadeDone = (false == FadeObject->IsUpdate());
		if (FadeDone)
		{
			LoadingObject->Off();
			GameEngineCore::ChangeLevel(PlayLevelName);
			return;
		}
	}
}