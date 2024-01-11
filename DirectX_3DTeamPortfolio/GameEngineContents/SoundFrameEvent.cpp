#include "PreCompile.h"
#include "SoundFrameEvent.h"

#include "FrameEventHelper.h"

SoundFrameEvent::SoundFrameEvent() 
{
}

SoundFrameEvent::~SoundFrameEvent() 
{
}

void SoundFrameEvent::PlayEvent()
{
	GameEngineSoundPlayer SoundPlayer = GameEngineSound::SoundPlay(SoundName);
}

