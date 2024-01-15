#include "PreCompile.h"
#include "CollisionUpdateFrameEvent.h"

#include "BoneSocketCollision.h"
#include "FrameEventHelper.h"


CollisionUpdateFrameEvent::CollisionUpdateFrameEvent() 
{
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
	ParentHelper->PushPlayingEvent(this);
}