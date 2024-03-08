#include "PreCompile.h"
#include "SwitchFlagFrameEvent.h"

#include "BaseActor.h"
#include "ContentsMath.h"

SwitchFlagFrameEvent::SwitchFlagFrameEvent()
{
	SetEventID(Enum_FrameEventType::SwitchFlag);
}

SwitchFlagFrameEvent::~SwitchFlagFrameEvent()
{
}


std::shared_ptr<SwitchFlagFrameEvent> SwitchFlagFrameEvent::CreateEventObject(int _SFrame, int _EFrame, int _iFlag, bool _OnValue)
{
	std::shared_ptr<SwitchFlagFrameEvent> TsEvent = std::make_shared<SwitchFlagFrameEvent>();
	TsEvent->StartFrame = _SFrame;
	TsEvent->EndFrame = _EFrame;
	TsEvent->iFlag = _iFlag;
	TsEvent->bOnValue = _OnValue;
	return TsEvent;
}

std::shared_ptr<FrameEventObject> SwitchFlagFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<SwitchFlagFrameEvent> NewObject = SwitchFlagFrameEvent::CreateEventObject(StartFrame, EndFrame, iFlag, bOnValue);
	return NewObject;
}

int SwitchFlagFrameEvent::PlayEvent()
{
	if (nullptr == pFlags)
	{
		Init();
	}

	BitMethod::SetFlag(pFlags, iFlag, bOnValue);

	FrameEventManager* pManager = GetEventManger();
	if (nullptr == pManager)
	{
		MsgBoxAssert("매니저를 모르고 사용할 수 없는 기능입니다. 김태훈에게 문의하세요");
		return EVENT_DONE;
	}

	pManager->PushEvent(this);
	return EVENT_DONE;
}

int SwitchFlagFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		if (nullptr == pFlags)
		{
			MsgBoxAssert("존재하지 않는 주소값에 이벤트를 실행하려 했습니다."); 
			return EVENT_ERROR;
		}

		BitMethod::SetFlag(pFlags, iFlag, !bOnValue);

		return EVENT_DONE;
	}

	return EVENT_PLAY;
}

void SwitchFlagFrameEvent::Reset()
{
	BitMethod::SetFlag(pFlags, iFlag, !bOnValue);
}

void SwitchFlagFrameEvent::Init()
{
	pFlags = GetDynamicCastParentActor<BaseActor>().get()->GetFlagPointer();
}