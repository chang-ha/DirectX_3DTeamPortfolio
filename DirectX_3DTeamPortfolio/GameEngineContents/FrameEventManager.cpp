#include "PreCompile.h"
#include "FrameEventManager.h"

#include "FrameEventHelper.h"
#include "FrameEventObject.h"

FrameEventManager::FrameEventManager() 
{
}

FrameEventManager::~FrameEventManager()
{
}

std::unique_ptr<FrameEventManager> FrameEventManager::CreateEventManager()
{
	std::unique_ptr<FrameEventManager> NewManager = std::make_unique<FrameEventManager>();
	return NewManager;
}

void FrameEventManager::SetEvent(std::shared_ptr<FrameEventObject> _EventObject)
{
	pHelper->SetEvent(_EventObject);
	_EventObject->SetParentManger(this);
}

void FrameEventManager::PopEvent(const std::shared_ptr<FrameEventObject>& _Event)
{
	int PopFrame = _Event->GetFrame();
	int PopID = _Event->GetEventID();

	if (false == PlayingEvents.empty())
	{
		std::list<std::shared_ptr<FrameEventObject>>::iterator StartIter = PlayingEvents.begin();
		std::list<std::shared_ptr<FrameEventObject>>::iterator EndIter = PlayingEvents.end();
		for (; StartIter != EndIter;)
		{
			int Frame = (*StartIter)->GetFrame();
			int ID = (*StartIter)->GetEventID();
			if ((Frame != PopFrame) || (ID != PopID))
			{
				++StartIter;
				continue;
			}

			PlayingEvents.erase(StartIter);
			break;
		}
	}
}

void FrameEventManager::PushEvent(std::shared_ptr<FrameEventObject> _Object)
{
	PlayingEvents.push_back(_Object);
}

void FrameEventManager::PlayEvents(int _CurFrame)
{
	if (nullptr == pHelper)
	{
		MsgBoxAssert("자료가 존재하지 않습니다");
		return;
	}

	const std::vector<std::list<FrameEventObject*>>& pEventList = pHelper->GetEventInfo();
	if (pEventList.empty())
	{
		return;
	}

	int FrameCount = pHelper->GetFrameCount();
	if (FrameCount < _CurFrame)
	{
		MsgBoxAssert("현재 프레임이 최대 프레임을 초과했습니다.");
		return;
	}

	const std::list<FrameEventObject*>& EventList = pEventList.at(_CurFrame);
	if (EventList.empty())
	{
		return;
	}

	for (FrameEventObject* EventObject : EventList)
	{
		std::shared_ptr<FrameEventObject> PlayingObject = EventObject->PlayEvent();
		if (nullptr != PlayingObject)
		{
			PushEvent(PlayingObject);
		}
	}
}

void FrameEventManager::UpdateEvent(float _Delta)
{
	if (PlayingEvents.empty())
	{
		return;
	}

	std::list<std::shared_ptr<FrameEventObject>>::iterator StartIter = PlayingEvents.begin();
	std::list<std::shared_ptr<FrameEventObject>>::iterator EndIter = PlayingEvents.end();
	for (; StartIter != EndIter;)
	{
		std::shared_ptr<FrameEventObject> pObject = (*StartIter);
		int Result = pObject->UpdateEvent(_Delta);
		if (EVENT_PLAY == Result)
		{
			++StartIter;
			continue;
		}

		StartIter = PlayingEvents.erase(StartIter);
	}
}


void FrameEventManager::EventReset()
{
	for (std::shared_ptr<FrameEventObject> pObject : PlayingEvents)
	{
		pObject->Reset();
	}

	PlayingEvents.clear();
}