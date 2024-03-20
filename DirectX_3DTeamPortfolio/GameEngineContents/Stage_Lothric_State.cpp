#include "PreCompile.h"
#include "Stage_Lothric.h"

#include "AllFadeEffect.h"

#include "Player.h"

#include "MainUIActor.h"
#include "UILoading.h"


void NUllCheck(void* _Pointer, std::string_view _MsgBox = "")
{
	if (nullptr == _Pointer)
	{
		if (_MsgBox.empty())
		{
			MsgBoxAssert("포인터가 존재하지 않습니다.");
		}
		else
		{
			MsgBoxAssert(_MsgBox.data());
		}
	}
}

void Stage_Lothric::StateInit()
{
	LevelState.CreateState(Enum_LevelState::LevelStart, {          .Start = std::bind(&Stage_Lothric::Start_LevelStart,this, std::placeholders::_1),          .Stay = std::bind(&Stage_Lothric::Update_LevelStart,this, std::placeholders::_1,std::placeholders::_2),     .End = std::bind(&Stage_Lothric::End_LevelStart, this, std::placeholders::_1)     });
	LevelState.CreateState(Enum_LevelState::ResLoadingDone, {      .Start = std::bind(&Stage_Lothric::Start_ResLoadingDone,this, std::placeholders::_1),      .Stay = std::bind(&Stage_Lothric::Update_ResLoadingDone,this, std::placeholders::_1,std::placeholders::_2), .End = std::bind(&Stage_Lothric::End_ResLoadingDone, this, std::placeholders::_1) });
	LevelState.CreateState(Enum_LevelState::Play, {                .Start = std::bind(&Stage_Lothric::Start_Play,this, std::placeholders::_1),                .Stay = std::bind(&Stage_Lothric::Update_Play,this, std::placeholders::_1,std::placeholders::_2),           .End = std::bind(&Stage_Lothric::End_Play, this, std::placeholders::_1)           });
	LevelState.CreateState(Enum_LevelState::PlayerDeath, {         .Start = std::bind(&Stage_Lothric::Start_PlayerDeath,this, std::placeholders::_1),         .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath,this, std::placeholders::_1,std::placeholders::_2),    .End = std::bind(&Stage_Lothric::End_PlayerDeath, this, std::placeholders::_1)    });
	LevelState.CreateState(Enum_LevelState::ResetLoading, {        .Start = std::bind(&Stage_Lothric::Start_ResetLoading,this, std::placeholders::_1),        .Stay = std::bind(&Stage_Lothric::Update_ResetLoading,this, std::placeholders::_1,std::placeholders::_2),   .End = std::bind(&Stage_Lothric::End_ResetLoading, this, std::placeholders::_1)   });
	LevelState.CreateState(Enum_LevelState::StageClear, {          .Start = std::bind(&Stage_Lothric::Start_StageClear,this, std::placeholders::_1),          .Stay = std::bind(&Stage_Lothric::Update_StageClear,this, std::placeholders::_1,std::placeholders::_2),     .End = std::bind(&Stage_Lothric::End_StageClear, this, std::placeholders::_1)     });

	PlayerDeathState.CreateState(Enum_PlayerDeathState::Ready, {   .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_Ready,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_Ready,this, std::placeholders::_1,std::placeholders::_2)                                                                                 });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::YouDie, {  .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_YouDie,this, std::placeholders::_1),  .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_YouDie,this, std::placeholders::_1,std::placeholders::_2)                                                                                });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::FadeOut, { .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_FadeOut,this, std::placeholders::_1), .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_FadeOut,this, std::placeholders::_1,std::placeholders::_2)                                                                               });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::Done, {                                                                                                                                                                                                                                                                                             });

	ResetState.CreateState(Enum_ResetState::PlayReset, {           .Start = std::bind(&Stage_Lothric::Start_Reset_PlayReset,this, std::placeholders::_1),     .Stay = std::bind(&Stage_Lothric::Update_Reset_PlayReset,this, std::placeholders::_1,std::placeholders::_2)                                                                                   });
	ResetState.CreateState(Enum_ResetState::Wait, {                                                                                                           .Stay = std::bind(&Stage_Lothric::Update_Reset_Wait,this, std::placeholders::_1,std::placeholders::_2)                                                                                        });
	ResetState.CreateState(Enum_ResetState::FadeOut, {             .Start = std::bind(&Stage_Lothric::Start_Reset_FadeOut,this, std::placeholders::_1),       .Stay = std::bind(&Stage_Lothric::Update_Reset_FadeOut,this, std::placeholders::_1,std::placeholders::_2),  .End = std::bind(&Stage_Lothric::End_Reset_FadeOut, this, std::placeholders::_1)  });
	ResetState.CreateState(Enum_ResetState::Done, {                                                                                                                                                                                                                                                                                                         });

	LevelState.ChangeState(Enum_LevelState::LevelStart);
}

#pragma region PlayLevel State

// LevelStart State
void Stage_Lothric::Start_LevelStart(GameEngineState* _Parent)
{
	// Effect
	FadeObject->FadeIn();

	LoadingUIOn();

	Stage_Lothric::ResLoadingDone = false;
	LoadingThread.Work(std::bind(&Stage_Lothric::ResLoading, this));
}

void Stage_Lothric::Update_LevelStart(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (true == FadeDone && true == Stage_Lothric::ResLoadingDone)
	{
		_Parent->ChangeState(Enum_LevelState::ResLoadingDone);
		return;
	}
}

void Stage_Lothric::End_LevelStart(GameEngineState* _Parent)
{

}

// ResLoadingDone State
void Stage_Lothric::Start_ResLoadingDone(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	FadeObject->FadeOut();
}

void Stage_Lothric::Update_ResLoadingDone(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		_Parent->ChangeState(Enum_LevelState::Play);
		return;
	}
}

void Stage_Lothric::End_ResLoadingDone(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	FadeObject->FadeIn();
}

// Play State
void Stage_Lothric::Start_Play(GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_Play(float _Delta, GameEngineState* _Parent)
{
	PlayUpdate(_Delta);

	NUllCheck(Player_Object.get(), "플레이어가 존재하지 않습니다. 값을 확인해주세요.");
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

	bool StateDone = (Enum_PlayerDeathState::Done == static_cast<Enum_PlayerDeathState>(PlayerDeathState.GetCurState()));
	if (StateDone)
	{
		_Parent->ChangeState(Enum_LevelState::ResetLoading);
		return;
	}
}

void Stage_Lothric::End_PlayerDeath(GameEngineState* _Parent)
{

}

// ResetLoading State
void Stage_Lothric::Start_ResetLoading(GameEngineState* _Parent)
{
	ResetState.ChangeState(Enum_ResetState::PlayReset);
}

void Stage_Lothric::Update_ResetLoading(float _Delta, GameEngineState* _Parent)
{
	ResetState.Update(_Delta);

	bool StateDone = (Enum_ResetState::Done == static_cast<Enum_ResetState>(ResetState.GetCurState()));
	if (StateDone)
	{
		_Parent->ChangeState(Enum_LevelState::ResetLoading);
		return;
	}
}

void Stage_Lothric::End_ResetLoading(GameEngineState* _Parent)
{
	LoadingUIOff();
}

// StageClear State
void Stage_Lothric::Start_StageClear(GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_StageClear(float _Delta, GameEngineState* _Parent)
{

}

void Stage_Lothric::End_StageClear(GameEngineState* _Parent)
{

}



// Func
void Stage_Lothric::LoadingUIOn()
{
	// const std::shared_ptr<UILoading>& UILoadingPointer = MainUI->GetUILoading();
	// NUllCheck(UILoadingPointer.get());
	// UILoadingPointer->On();
}

void Stage_Lothric::LoadingUIOff()
{
	// const std::shared_ptr<UILoading>& UILoadingPointer = MainUI->GetUILoading();
	// NUllCheck(UILoadingPointer.get());
	// UILoadingPointer->Off();
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
	NUllCheck(MainUI.get());
	// MainUI->Call
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
	NUllCheck(FadeObject.get());
	FadeObject->FadeOut();
}

void Stage_Lothric::Update_PlayerDeath_FadeOut(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		_Parent->ChangeState(Enum_PlayerDeathState::Done);
		return;
	}
}

#pragma endregion

#pragma region Reset State

// PlayReset State
void Stage_Lothric::Start_Reset_PlayReset(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	FadeObject->FadeIn();
	LoadingUIOn();

	Stage_Lothric::ResetLoadingDone = false;

	LoadingThread.Work(std::bind(&Stage_Lothric::ResetLoading, this));
}

void Stage_Lothric::Update_Reset_PlayReset(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (true == FadeDone && true == Stage_Lothric::ResetLoadingDone)
	{
		_Parent->ChangeState(Enum_ResetState::Wait);
		return;
	}
}

// Wait State
void Stage_Lothric::Update_Reset_Wait(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 2.0f)
	{
		_Parent->ChangeState(Enum_ResetState::FadeOut);
		return;
	}
}

// FadeOut State
void Stage_Lothric::Start_Reset_FadeOut(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	FadeObject->FadeOut();
}

void Stage_Lothric::Update_Reset_FadeOut(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get());
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		_Parent->ChangeState(Enum_ResetState::Done);
		return;
	}
}

void Stage_Lothric::End_Reset_FadeOut(GameEngineState* _Parent)
{
	LoadingUIOff();
}

#pragma endregion
