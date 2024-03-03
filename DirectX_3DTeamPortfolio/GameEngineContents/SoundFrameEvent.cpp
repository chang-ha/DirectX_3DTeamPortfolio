#include "PreCompile.h"
#include "SoundFrameEvent.h"

#include "FrameEventHelper.h"


SoundFrameEvent::SoundFrameEvent() 
{
	SetEventID(Type);
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

std::shared_ptr<FrameEventObject> SoundFrameEvent::PlayEvent()
{
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(SoundName);
	return nullptr;
}

