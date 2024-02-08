#include "PreCompile.h"
#include "BoneSoundFrameEvent.h"

#include "FrameEventHelper.h"


BoneSoundFrameEvent::BoneSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::BSound);
}

BoneSoundFrameEvent::~BoneSoundFrameEvent()
{
}


std::shared_ptr<BoneSoundFrameEvent> BoneSoundFrameEvent::CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName)
{
	std::shared_ptr<BoneSoundFrameEvent> SEvent = std::make_shared<BoneSoundFrameEvent>();
	SEvent->StartFrame = _Frame;
	SEvent->BoneIndex = _iBoneIndex;
	SEvent->SoundName = _FileName;
	return SEvent;
}

void BoneSoundFrameEvent::PlayEvent()
{
	// 수정 필요
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(SoundName);
}

