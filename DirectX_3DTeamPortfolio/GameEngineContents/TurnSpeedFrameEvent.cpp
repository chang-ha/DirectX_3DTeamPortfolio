#include "PreCompile.h"
#include "TurnSpeedFrameEvent.h"

#include "BaseMonster.h"

TurnSpeedFrameEvent::TurnSpeedFrameEvent()
{
	SetEventID(static_cast<int>(Type));
}

TurnSpeedFrameEvent::~TurnSpeedFrameEvent()
{
}


std::shared_ptr<TurnSpeedFrameEvent> TurnSpeedFrameEvent::CreateEventObject(int _SFrame, int _EFrame, float _TurnSpeed)
{
	std::shared_ptr<TurnSpeedFrameEvent> TsEvent = std::make_shared<TurnSpeedFrameEvent>();
	TsEvent->StartFrame = _SFrame;
	TsEvent->EndFrame = _EFrame;
	TsEvent->pMonster = TsEvent->GetDynamicCastParentActor<BaseMonster>().get();
	return TsEvent;
}

void TurnSpeedFrameEvent::PlayEvent()
{
	if (nullptr == pMonster)
	{
		Init();
	}

	ParentHelper->PushPlayingEvent(this);
}

int TurnSpeedFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		// ½ÇÇà

		return EVENT_DONE;
	}

	return EVENT_PLAY;
}

void TurnSpeedFrameEvent::Init()
{
	pMonster = GetDynamicCastParentActor<BaseMonster>().get();
}