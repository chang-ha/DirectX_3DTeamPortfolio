#include "PreCompile.h"
#include "CollisionUpdateFrameEvent.h"

#include "GameContentsFBXRenderer.h"
#include "BoneSocketCollision.h"
#include "FrameEventHelper.h"


CollisionUpdateFrameEvent::CollisionUpdateFrameEvent() 
{
	SetEventID(static_cast<int>(Type));
}

CollisionUpdateFrameEvent::~CollisionUpdateFrameEvent()
{ 
}


std::shared_ptr<CollisionUpdateFrameEvent> CollisionUpdateFrameEvent::CreateEventObject(int _SFrame, int _EFrame, std::shared_ptr<BoneSocketCollision> Collision)
{
	std::shared_ptr<CollisionUpdateFrameEvent> CEvent = std::make_shared<CollisionUpdateFrameEvent>();
	CEvent->StartFrame = _SFrame;
	CEvent->EndFrame = _EFrame;
	CEvent->TypeNumber = Collision->GetBoneIndex();
	CEvent->pCollision = Collision.get();
	return CEvent;
}

void CollisionUpdateFrameEvent::PlayEvent()
{
	if (nullptr == pCollision)
	{
		MsgBoxAssert("콜리전이 존재하지 않습니다.");
		return;
	}

	pCollision->On();
	ParentHelper->PushPlayingEvent(this);
}

int CollisionUpdateFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		pCollision->Off();
		return EVENT_DONE;
	}

	return EVENT_PLAY;
}