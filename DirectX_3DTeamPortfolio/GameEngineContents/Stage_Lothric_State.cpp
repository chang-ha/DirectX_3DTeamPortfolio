#include "PreCompile.h"
#include "Stage_Lothric.h"

#include "AllFadeEffect.h"

#include "Player.h"
#include "Boss_Vordt.h"

#include "MainUIActor.h"
#include "UIAlertMaanger.h"

#include "LoadingLevel.h"

// Object
#include "Object_FogWall.h"
#include "Object_bonfire.h"


void Stage_Lothric::StateInit()
{
	LevelState.CreateState(Enum_LevelState::Play, {                .Start = std::bind(&Stage_Lothric::Start_Play,this, std::placeholders::_1),                .Stay = std::bind(&Stage_Lothric::Update_Play,this, std::placeholders::_1,std::placeholders::_2),           .End = std::bind(&Stage_Lothric::End_Play, this, std::placeholders::_1)           });
	LevelState.CreateState(Enum_LevelState::PlayerDeath, {         .Start = std::bind(&Stage_Lothric::Start_PlayerDeath,this, std::placeholders::_1),         .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath,this, std::placeholders::_1,std::placeholders::_2),    .End = std::bind(&Stage_Lothric::End_PlayerDeath, this, std::placeholders::_1)    });

	PlayerDeathState.CreateState(Enum_PlayerDeathState::Ready, {   .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_Ready,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_Ready,this, std::placeholders::_1,std::placeholders::_2)                                                                                 });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::YouDie, {  .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_YouDie,this, std::placeholders::_1),  .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_YouDie,this, std::placeholders::_1,std::placeholders::_2)                                                                                });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::FadeOut, { .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_FadeOut,this, std::placeholders::_1), .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_FadeOut,this, std::placeholders::_1,std::placeholders::_2)                                                                               });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::Done, {                                                                                                                                                                                                                                                                                             });

	BossStageState.CreateState(Enum_BossStageState::Ready, { .Start = std::bind(&Stage_Lothric::Start_BossStage_Ready,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_BossStage_Ready,this, std::placeholders::_1,std::placeholders::_2) });
	BossStageState.CreateState(Enum_BossStageState::Fight, { .Start = std::bind(&Stage_Lothric::Start_BossStage_Fight,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_BossStage_Fight,this, std::placeholders::_1,std::placeholders::_2) });
	BossStageState.CreateState(Enum_BossStageState::Clear, { .Start = std::bind(&Stage_Lothric::Start_BossStage_Clear,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_BossStage_Clear,this, std::placeholders::_1,std::placeholders::_2) });

	EndingState.CreateState(Enum_EndingState::Ready, {  });
	EndingState.CreateState(Enum_EndingState::FadeOut, { .Start = std::bind(&Stage_Lothric::Start_EndingState_FadeOut,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_EndingState_FadeOut,this, std::placeholders::_1,std::placeholders::_2), .End = std::bind(&Stage_Lothric::End_EndingState_FadeOut,this, std::placeholders::_1) });
}

#pragma region PlayLevel State

// Play State
void Stage_Lothric::Start_Play(GameEngineState* _Parent)
{
	if (FadeObject)
	{
		FadeObject->FadeIn();
		FadeObject->SetFadeSpeed(2.0f);
	}
}

void Stage_Lothric::Update_Play(float _Delta, GameEngineState* _Parent)
{
	PlayUpdate(_Delta);

	ContentsDebug::NUllCheck(Player_Object.get(), "플레이어가 존재하지 않습니다. 값을 확인해주세요.");
	if (true == Player_Object->IsFlag(Enum_ActorFlag::Death))
	{
		_Parent->ChangeState(Enum_LevelState::PlayerDeath);
		return;
	}
}

void Stage_Lothric::End_Play(GameEngineState* _Parent)
{

}

// PlayerDeath State
void Stage_Lothric::Start_PlayerDeath(GameEngineState* _Parent)
{
	PlayerDeathState.ChangeState(Enum_PlayerDeathState::Ready);
}

void Stage_Lothric::Update_PlayerDeath(float _Delta, GameEngineState* _Parent)
{
	PlayerDeathState.Update(_Delta);

	bool PlayerDeathStateDone = (Enum_PlayerDeathState::Done == static_cast<Enum_PlayerDeathState>(PlayerDeathState.GetCurState()));
	if (PlayerDeathStateDone)
	{
		CreateBlackScreen();
		LoadingLevel::LoadingFlag = Enum_LevelFlag::Loading_Reset;
		GameEngineCore::ChangeLevel("LoadingLevel");
		return;
	}
}

void Stage_Lothric::End_PlayerDeath(GameEngineState* _Parent)
{

}

#pragma endregion

#pragma region PlayerDeath State

// Ready State
void Stage_Lothric::Start_PlayerDeath_Ready(GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_PlayerDeath_Ready(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 0.2f)
	{
		_Parent->ChangeState(Enum_PlayerDeathState::YouDie);
		return;
	}
}

// YouDie State
void Stage_Lothric::Start_PlayerDeath_YouDie(GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(MainUI.get());
	UIAlertMaanger::CallAlert(Enum_AlertType::YouDie);
}

void Stage_Lothric::Update_PlayerDeath_YouDie(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 5.f)
	{
		_Parent->ChangeState(Enum_PlayerDeathState::FadeOut);
		return;
	}
}

// FadeOut State
void Stage_Lothric::Start_PlayerDeath_FadeOut(GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(FadeObject.get());
	FadeObject->FadeOut();
}

void Stage_Lothric::Update_PlayerDeath_FadeOut(float _Delta, GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		_Parent->ChangeState(Enum_PlayerDeathState::Done);
		return;
	}
}

#pragma endregion

#pragma region Boss Stage State

// Ready State
void Stage_Lothric::Start_BossStage_Ready(GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_BossStage_Ready(float _Delta, GameEngineState* _Parent)
{

}


// Fight State
void Stage_Lothric::Start_BossStage_Fight(GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_BossStage_Fight(float _Delta, GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(Boss_Object.get(), "플레이어가 존재하지 않습니다. 값을 확인해주세요.");
	if (true == Boss_Object->IsFlag(Enum_ActorFlag::Death))
	{
		_Parent->ChangeState(Enum_BossStageState::Clear);
		return;
	}
}

// Clear State
void Stage_Lothric::Start_BossStage_Clear(GameEngineState* _Parent)
{
	MainUIActor::SoundPlay("Destroyed_Sound_Effect.wav");

	if (nullptr != BossRoom_bonfire && false == BossRoom_bonfire->IsUpdate())
	{
		BossRoom_bonfire->On();
	}

	if (nullptr != FogWall)
	{
		FogWall->Death();
		FogWall = nullptr;
	}
}

void Stage_Lothric::Update_BossStage_Clear(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 3.0f)
	{
		UIAlertMaanger::CallAlert(Enum_AlertType::Destroy);
		UIAlertMaanger::CallAlert(Enum_AlertType::BoneFire);
		_Parent->ChangeState(Enum_BossStageState::Ready);
		return;
	}
}


#pragma endregion

#pragma region Ending State

void Stage_Lothric::Start_EndingState_FadeOut(GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(FadeObject.get());
	FadeObject->FadeOut();
}

void Stage_Lothric::Update_EndingState_FadeOut(float _Delta, GameEngineState* _Parent)
{
	ContentsDebug::NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		CreateBlackScreen();
		GameEngineCore::ChangeLevel("TitleLevel");
		return;
	}
}

void Stage_Lothric::End_EndingState_FadeOut(GameEngineState* _Parent)
{
	EndingState.ChangeState(Enum_EndingState::Ready);
}

#pragma endregion




void Stage_Lothric::CreateBlackScreen()
{
	if (nullptr != BlackScreen)
	{
		BlackScreen->Death();
	}

	BlackScreen = CreateActor<GameEngineActor>(Enum_UpdateOrder::UI);
	std::shared_ptr<GameEngineUIRenderer> Renderer = BlackScreen->CreateComponent<GameEngineUIRenderer>(Enum_RenderOrder::UI_Loading);;
	Renderer->GetColorData().MulColor = float4::ZERO;
	Renderer->SetImageScale(GlobalValue::GetWinScale());
}