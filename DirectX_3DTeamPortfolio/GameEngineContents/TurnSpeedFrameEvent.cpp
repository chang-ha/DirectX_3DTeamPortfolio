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
	if (nullptr == pComponent)
	{
		Init();
	}

	ParentHelper->PushPlayingEvent(this);
}

int TurnSpeedFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		return EVENT_DONE;
	}

	pComponent->AddWorldRotation(float4(0.0f, TurnSpeed * _Delta));

	return EVENT_PLAY;
}

void TurnSpeedFrameEvent::Init()
{

	const std::shared_ptr<BaseActor>& pParentActor = GetDynamicCastParentActor<BaseActor>();
	if (nullptr == pParentActor)
	{
		MsgBoxAssert("부모 액터가 존재하지 않습니다.");
		return;
	}

	pComponent = pParentActor->GetPhysxCapsulePointer();
}