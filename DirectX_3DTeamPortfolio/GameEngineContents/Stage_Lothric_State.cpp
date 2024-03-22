#include "PreCompile.h"
#include "Stage_Lothric.h"

#include "AllFadeEffect.h"

#include "Player.h"
#include "Boss_Vordt.h"

#include "MainUIActor.h"
#include "UIAlertMaanger.h"

#include "LoadingLevel.h"


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
	LevelState.CreateState(Enum_LevelState::Play, {                .Start = std::bind(&Stage_Lothric::Start_Play,this, std::placeholders::_1),                .Stay = std::bind(&Stage_Lothric::Update_Play,this, std::placeholders::_1,std::placeholders::_2),           .End = std::bind(&Stage_Lothric::End_Play, this, std::placeholders::_1)           });
	LevelState.CreateState(Enum_LevelState::PlayerDeath, {         .Start = std::bind(&Stage_Lothric::Start_PlayerDeath,this, std::placeholders::_1),         .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath,this, std::placeholders::_1,std::placeholders::_2),    .End = std::bind(&Stage_Lothric::End_PlayerDeath, this, std::placeholders::_1)    });
	LevelState.CreateState(Enum_LevelState::BossDeath, {         .Start = std::bind(&Stage_Lothric::Start_BossDeath,this, std::placeholders::_1),         .Stay = std::bind(&Stage_Lothric::Update_BossDeath,this, std::placeholders::_1,std::placeholders::_2),    .End = std::bind(&Stage_Lothric::End_BossDeath, this, std::placeholders::_1)    });
	LevelState.CreateState(Enum_LevelState::StageClear, {          .Start = std::bind(&Stage_Lothric::Start_StageClear,this, std::placeholders::_1),          .Stay = std::bind(&Stage_Lothric::Update_StageClear,this, std::placeholders::_1,std::placeholders::_2),     .End = std::bind(&Stage_Lothric::End_StageClear, this, std::placeholders::_1)     });

	PlayerDeathState.CreateState(Enum_PlayerDeathState::Ready, {   .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_Ready,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_Ready,this, std::placeholders::_1,std::placeholders::_2)                                                                                 });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::YouDie, {  .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_YouDie,this, std::placeholders::_1),  .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_YouDie,this, std::placeholders::_1,std::placeholders::_2)                                                                                });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::FadeOut, { .Start = std::bind(&Stage_Lothric::Start_PlayerDeath_FadeOut,this, std::placeholders::_1), .Stay = std::bind(&Stage_Lothric::Update_PlayerDeath_FadeOut,this, std::placeholders::_1,std::placeholders::_2)                                                                               });
	PlayerDeathState.CreateState(Enum_PlayerDeathState::Done, {                                                                                                                                                                                                                                                                                             });

	BossDeathState.CreateState(Enum_BossDeathState::Ready, {   .Start = std::bind(&Stage_Lothric::Start_BossDeath_Ready,this, std::placeholders::_1),   .Stay = std::bind(&Stage_Lothric::Update_BossDeath_Ready,this, std::placeholders::_1,std::placeholders::_2)                                                                                 });
	BossDeathState.CreateState(Enum_BossDeathState::Alert, { .Start = std::bind(&Stage_Lothric::Start_BossDeath_Alert,this, std::placeholders::_1),  .Stay = std::bind(&Stage_Lothric::Update_BossDeath_Alert,this, std::placeholders::_1,std::placeholders::_2) });
	BossDeathState.CreateState(Enum_BossDeathState::Done, {                                                                                                                                                                                                                                                                                             });
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

	NUllCheck(Player_Object.get(), "플레이어가 존재하지 않습니다. 값을 확인해주세요.");
	if (true == Player_Object->IsFlag(Enum_ActorFlag::Death))
	{
		_Parent->ChangeState(Enum_LevelState::PlayerDeath);
		return;
	}

	NUllCheck(Boss_Object.get(), "보스가 존재하지 않습니다. 값을 확인해주세요.");
	if (true == Boss_Object->IsFlag(Enum_ActorFlag::Death))
	{
		_Parent->ChangeState(Enum_LevelState::BossDeath);
		return;
	}
}

void Stage_Lothric::End_Play(GameEngineState* _Parent)
{
	//Player_Object->SetFlag(Enum_ActorFlag::Wake, true);
	Player_Object->Reset();

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
		LoadingLevel::LoadingFlag = Enum_LevelFlag::Loading_Reset;
		GameEngineCore::ChangeLevel("LoadingLevel");
		return;
	}
}

void Stage_Lothric::End_PlayerDeath(GameEngineState* _Parent)
{

}

// BossDeath State
void Stage_Lothric::Start_BossDeath(GameEngineState* _Parent)
{
	BossDeathState.ChangeState(Enum_PlayerDeathState::Ready);
}

void Stage_Lothric::Update_BossDeath(float _Delta, GameEngineState* _Parent)
{
	BossDeathState.Update(_Delta);

	bool BossDeathStateDone = (Enum_BossDeathState::Done == static_cast<Enum_BossDeathState>(BossDeathState.GetCurState()));
	if (BossDeathStateDone)
	{
		_Parent->ChangeState(Enum_LevelState::StageClear);
		return;
	}
}

void Stage_Lothric::End_BossDeath(GameEngineState* _Parent)
{

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

#pragma region Boss Death State

void Stage_Lothric::Start_BossDeath_Ready(GameEngineState* _Parent)
{
	GameEngineSoundPlayer SPlayer = GameEngineSound::SoundPlay("Destroyed_Sound_Effect.wav");
	SPlayer.SetVolume(0.7f);
}

void Stage_Lothric::Update_BossDeath_Ready(float _Delta, GameEngineState* _Parent)
{
	if (_Parent->GetStateTime() > 5.0f)
	{
		_Parent->ChangeState(Enum_BossDeathState::Alert);
		return;
	}
}


void Stage_Lothric::Start_BossDeath_Alert(GameEngineState* _Parent)
{
	UIAlertMaanger::CallAlert(Enum_AlertType::Destroy);
	UIAlertMaanger::CallAlert(Enum_AlertType::BoneFire);

	IsAlert = false;
}

void Stage_Lothric::Update_BossDeath_Alert(float _Delta, GameEngineState* _Parent)
{
	if (false == UIAlertMaanger::Alerting && true == IsAlert)
	{
		_Parent->ChangeState(Enum_BossDeathState::Done);
		return;
	}

	IsAlert = true;
}

#pragma endregion
