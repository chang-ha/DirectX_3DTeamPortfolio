#include "PreCompile.h"
#include "Stage_Lothric.h"

#include "AllFadeEffect.h"

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

// State Start 
void Stage_Lothric::Start_LevelStart(GameEngineState* _Parent)
{
	ResLoading();
	LoadingUIOn();
}

void Stage_Lothric::Start_ResLoadingDone(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	FadeObject->FadeOut();
}

void Stage_Lothric::Start_PlayStart(GameEngineState* _Parent)
{

}

void Stage_Lothric::Start_PlayerDeath(GameEngineState* _Parent)
{

}

void Stage_Lothric::Start_Loading(GameEngineState* _Parent)
{

}

void Stage_Lothric::Start_BossStage(GameEngineState* _Parent)
{

}

void Stage_Lothric::Start_End(GameEngineState* _Parent)
{

}

// State Update
void Stage_Lothric::Update_LevelStart(float _Delta, GameEngineState* _Parent)
{
	if (true == Stage_Lothric::ResLoadingDone)
	{
		_Parent->ChangeState(Enum_LevelState::ResLoadingDone);
		return;
	}
}

void Stage_Lothric::Update_ResLoadingDone(float _Delta, GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	bool FadeDone = (false == FadeObject->IsUpdate());
	if (FadeDone)
	{
		_Parent->ChangeState(Enum_LevelState::PlayStart);
		return;
	}
}

void Stage_Lothric::Update_PlayStart(float _Delta, GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_PlayerDeath(float _Delta, GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_Loading(float _Delta, GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_BossStage(float _Delta, GameEngineState* _Parent)
{

}

void Stage_Lothric::Update_End(float _Delta, GameEngineState* _Parent)
{

}

// State End
void Stage_Lothric::End_LevelStart(GameEngineState* _Parent)
{

}

void Stage_Lothric::End_ResLoadingDone(GameEngineState* _Parent)
{
	NUllCheck(FadeObject.get(), "FadeObject가 존재하지 않습니다.");
	FadeObject->FadeOut();
}

void Stage_Lothric::End_PlayStart(GameEngineState* _Parent)
{

}

void Stage_Lothric::End_PlayerDeath(GameEngineState* _Parent)
{

}

void Stage_Lothric::End_Loading(GameEngineState* _Parent)
{

}

void Stage_Lothric::End_BossStage(GameEngineState* _Parent)
{

}

void Stage_Lothric::End_End(GameEngineState* _Parent)
{

}

// Func
void Stage_Lothric::LoadingUIOn()
{
	const std::shared_ptr<UILoading>& UILoadingPointer = MainUI->GetUILoading();
	NUllCheck(UILoadingPointer.get());
	UILoadingPointer->On();
}

void Stage_Lothric::LoadingUIOff()
{
	const std::shared_ptr<UILoading>& UILoadingPointer = MainUI->GetUILoading();
	NUllCheck(UILoadingPointer.get());
	UILoadingPointer->Off();
}
