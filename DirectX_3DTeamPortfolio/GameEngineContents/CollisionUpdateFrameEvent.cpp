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


std::shared_ptr<CollisionUpdateFrameEvent> CollisionUpdateFrameEvent::CreateEventObject(int _SFrame, int _EFrame, int _ColNumber)
{
	std::shared_ptr<CollisionUpdateFrameEvent> CEvent = std::make_shared<CollisionUpdateFrameEvent>();
	CEvent->StartFrame = _SFrame;
	CEvent->EndFrame = _EFrame;
	CEvent->ColNumber = _ColNumber;
	return CEvent;
}

std::shared_ptr<FrameEventObject> CollisionUpdateFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<CollisionUpdateFrameEvent> NewObject = CollisionUpdateFrameEvent::CreateEventObject(StartFrame, EndFrame, ColNumber);
	return NewObject;
}

void CollisionUpdateFrameEvent::PlayEvent()
{
	if (nullptr == pCollision)
	{
		Init();
	}
	pCollision->On();

	FrameEventManager* pManager = GetEventManger();
	if (nullptr == pManager)
	{
		MsgBoxAssert("매니저를 모르고 사용할 수 없는 기능입니다. 김태훈에게 문의하세요");
		return;
	}

	pManager->PushEvent(this);
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

void CollisionUpdateFrameEvent::Reset()
{
	pCollision->Off();
}

void CollisionUpdateFrameEvent::Init()
{
	std::shared_ptr<BaseMonster> ParentActor = GetDynamicCastParentActor<BaseMonster>();
	pCollision = ParentActor->GetSocketCollision(ColNumber).get();
}