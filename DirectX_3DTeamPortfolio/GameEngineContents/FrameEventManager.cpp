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

std::shared_ptr<FrameEventManager> FrameEventManager::CreateEventManager()
{
	std::shared_ptr<FrameEventManager> NewManager = std::make_shared<FrameEventManager>();
	return NewManager;
}

void FrameEventManager::CopyEvent(const std::map<int, std::list<std::shared_ptr<FrameEventObject>>>& _Events)
{
	for (const std::pair<int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : _Events)
	{
		const std::list<std::shared_ptr<FrameEventObject>>& TypeEvents = Pair.second;
		for (const std::shared_ptr<FrameEventObject>& EventObject : TypeEvents)
		{
			int Frame = EventObject->GetFrame();

			std::shared_ptr<FrameEventObject> CopyObject = EventObject->CreatePlayingEvent();
			CopyObject->SetParentManger(this);

			EventInfos.insert(std::make_pair(Frame, CopyObject));
		}
	}
}

void FrameEventManager::SetEvent(std::shared_ptr<FrameEventObject> _EventObject)
{
	if (nullptr == pHelper)
	{
		MsgBoxAssert("존재하지 않는 리소스에 이벤트를 저장하려했습니다");
		return;
	}

	bool SuccessPush = pHelper->SetEvent(_EventObject);
	if (SuccessPush)
	{
		_EventObject->SetParentManger(this);
		int Frame = _EventObject->GetFrame();
		EventInfos.insert(std::make_pair(Frame, _EventObject));
	}
}

void FrameEventManager::PopEvent(const std::shared_ptr<FrameEventObject>& _Event)
{
	int PopFrame = _Event->GetFrame();
	int PopID = _Event->GetEventID();

	std::multimap<int, std::shared_ptr<FrameEventObject>>::iterator LowerIter = EventInfos.lower_bound(PopFrame);
	std::multimap<int, std::shared_ptr<FrameEventObject>>::iterator UpperIter = EventInfos.upper_bound(PopFrame);
	for (; LowerIter != UpperIter;)
	{
		const std::shared_ptr<FrameEventObject>& EventObject = LowerIter->second;
		int ID = EventObject->GetEventID();
		if (PopID != ID)
		{
			++LowerIter;
			continue;
		}

		GetHelper()->PopEvent(EventObject);
		PlayingEvents.remove(EventObject.get());
		EventInfos.erase(LowerIter);
		break;
	}
}

void FrameEventManager::PushEvent(FrameEventObject* _Object)
{
	PlayingEvents.push_back(_Object);
}

void FrameEventManager::PlayEvents(int _CurFrame)
{
	if (EventInfos.empty())
	{
		return;
	}

	int FrameCount = pHelper->GetFrameCount();
	if (FrameCount < _CurFrame)
	{
		MsgBoxAssert("현재 프레임이 최대 프레임을 초과했습니다.");
		return;
	}

	if (false == EventInfos.contains(_CurFrame))
	{
		return;
	}

	std::multimap<int, std::shared_ptr<FrameEventObject>>::iterator LowerIter = EventInfos.lower_bound(_CurFrame);
	std::multimap<int, std::shared_ptr<FrameEventObject>>::iterator UpperIter = EventInfos.upper_bound(_CurFrame);
	for (; LowerIter != UpperIter; ++LowerIter)
	{
		const std::shared_ptr<FrameEventObject>& EventObject = LowerIter->second;
		EventObject->PlayEvent();
	}
}

void FrameEventManager::UpdateEvent(float _Delta)
{
	if (PlayingEvents.empty())
	{
		return;
	}

	std::list<FrameEventObject*>::iterator StartIter = PlayingEvents.begin();
	std::list<FrameEventObject*>::iterator EndIter = PlayingEvents.end();
	for (; StartIter != EndIter;)
	{
		FrameEventObject* pObject = (*StartIter);
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
	for (FrameEventObject* pObject : PlayingEvents)
	{
		pObject->Reset();
	}

	PlayingEvents.clear();
}

void FrameEventManager::EventRelease()
{
	PlayingEvents.clear();
	EventInfos.clear();
}