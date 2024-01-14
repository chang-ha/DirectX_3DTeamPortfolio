#include "PreCompile.h"
#include "SoundFrameEvent.h"

#include "FrameEventHelper.h"

SoundFrameEvent::SoundFrameEvent() 
{
	Type = Enum_FrameEventType::Sound;
}

SoundFrameEvent::~SoundFrameEvent() 
{
}


std::shared_ptr<SoundFrameEvent> SoundFrameEvent::CreateEventObject(int _Frame, std::string_view _FileName)
{
	std::shared_ptr<SoundFrameEvent> SEvent = std::make_shared<SoundFrameEvent>();
	SEvent->StartFrame = _Frame;
	SEvent->SoundName = _FileName;
	return SEvent;
}

void SoundFrameEvent::PlayEvent()
{
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(SoundName);
}

