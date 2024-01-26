#include "PreCompile.h"
#include "TurnSpeedFrameEvent.h"

#include "BaseActor.h"

TurnSpeedFrameEvent::TurnSpeedFrameEvent()
{
	SetEventID(Enum_FrameEventType::TurnSpeed);
}

TurnSpeedFrameEvent::~TurnSpeedFrameEvent()
{
}


std::shared_ptr<TurnSpeedFrameEvent> TurnSpeedFrameEvent::CreateEventObject(int _SFrame, int _EFrame, float _TurnSpeed)
{
	std::shared_ptr<TurnSpeedFrameEvent> TsEvent = std::make_shared<TurnSpeedFrameEvent>();
	TsEvent->StartFrame = _SFrame;
	TsEvent->EndFrame = _EFrame;
	TsEvent->TurnSpeed = _TurnSpeed;
	return TsEvent;
}

void TurnSpeedFrameEvent::PlayEvent()
{
	if (nullptr == pParentActor)
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
		int a = 0;
		return EVENT_DONE;
	}

	return EVENT_PLAY;
}

void TurnSpeedFrameEvent::Init()
{
	pParentActor = GetDynamicCastParentActor<BaseActor>().get();
}