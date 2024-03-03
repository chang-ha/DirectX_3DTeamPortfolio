#include "PreCompile.h"
#include "CollisionUpdateFrameEvent.h"

#include "GameContentsFBXRenderer.h"
#include "BoneSocketCollision.h"
#include "FrameEventHelper.h"
#include "BaseMonster.h"


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
	CEvent->ColNumber = Collision->GetBoneIndex();
	CEvent->pCollision = Collision.get();
	return CEvent;
}

std::shared_ptr<FrameEventObject> CollisionUpdateFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<CollisionUpdateFrameEvent> NewObject = std::make_shared<CollisionUpdateFrameEvent>();
	memcpy(NewObject.get(), this, sizeof(CollisionUpdateFrameEvent));
	return NewObject;
}

std::shared_ptr<FrameEventObject> CollisionUpdateFrameEvent::PlayEvent()
{
	if (nullptr == pCollision)
	{
		Init();
	}
	std::string ActorName = ParentManager->GetAnimationInfo()->ParentRenderer->GetActor()->GetName();
	pCollision->On();
	return CreatePlayingEvent();
}

int CollisionUpdateFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		std::string ActorName = ParentManager->GetAnimationInfo()->ParentRenderer->GetActor()->GetName();
		pCollision->Off();
		return EVENT_DONE;
	}

	return EVENT_PLAY;
}

void CollisionUpdateFrameEvent::Reset()
{
	pCollision->Off();
}

void CollisionUpdateFrameEvent::Init()
{
	std::shared_ptr<BaseMonster> ParentActor = GetDynamicCastParentActor<BaseMonster>();
	pCollision = ParentActor->GetSocketCollision(ColNumber).get();
	std::string Name = ParentActor->GetName();
	int a = 0;
}