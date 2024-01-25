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
	return TsEvent;
}

void SwitchFlagFrameEvent::PlayEvent()
{
	if (nullptr == pFlags)
	{
		Init();
	}

	BitMethod::SetFlag(pFlags, iFlag, bOnValue);

	ParentHelper->PushPlayingEvent(this);
}

int SwitchFlagFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		if (nullptr == pFlags)
		{
			MsgBoxAssert("�������� �ʴ� �ּҰ��� �̺�Ʈ�� �����Ϸ� �߽��ϴ�."); 
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