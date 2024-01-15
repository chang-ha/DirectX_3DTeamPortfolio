#include "PreCompile.h"
#include "FrameEventHelper.h"

#include "SoundFrameEvent.h"
#include "CollisionUpdateFrameEvent.h"

std::string FrameEventHelper::ExtName = ".Event";
FrameEventHelper::FrameEventHelper() 
{
}

FrameEventHelper::~FrameEventHelper() 
{
}

std::string FrameEventHelper::GetConvertFileName(std::string_view _AnimationName)
{
	std::string Name = _AnimationName.data();
	size_t DotNum = Name.find_last_of('.', Name.size());
	Name.erase(DotNum, Name.size() - 1);
	Name += ExtName;
	return Name;
}

void FrameEventHelper::Initialze(GameContentsFBXAnimationInfo* _AnimationInfo)
{
	if (false == EventInfo.empty())
	{
		return;
	}

	ParentInfo = _AnimationInfo;
	FrameCount = static_cast<int>(_AnimationInfo->FBXAnimationData->FrameCount + 1);
	EventInfo.resize(FrameCount);
	
	GameEngineFile File(Path);
	File.Open(FileOpenType::Read, FileDataType::Binary);

	GameEngineSerializer Ser;
	File.DataAllRead(Ser);

	int Size;
	
	Ser >> Size;
	if (0 == Size)
	{
		return;
	}

	for (int i = 0; i < Size; i++)
	{
		int TypeNum;
		std::shared_ptr<FrameEventObject> NewEvent;

		Ser >> TypeNum;

		switch (static_cast<Enum_FrameEventType>(TypeNum))
		{
		case None:
			break;
		case Sound:
		{
			NewEvent = std::make_shared<SoundFrameEvent>();
		}
			break;
		case CollisionUpdate:
		{
			NewEvent = std::make_shared<CollisionUpdateFrameEvent>();
		}
			break;
		case Transfrom:
			break;
		default:
			break;
		}

		NewEvent->Read(Ser);
		NewEvent->SetParent(this);
		Events[TypeNum].push_back(NewEvent);
	}

	PushEventData();
}

void FrameEventHelper::PushEventData()
{
	for (std::pair<const int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : Events)
	{
		for (const std::shared_ptr<FrameEventObject>& Object : Pair.second)
		{
			int Frame = Object->GetFrame();
			EventInfo.at(Frame).push_back(Object.get());
		}
	}
}

void FrameEventHelper::SaveFile()
{
	GameEngineFile File(Path);
	if (File.IsDirectory())
	{
		MsgBoxAssert("폴더 경로에 쓰기를 할 수 없습니다.");
		return;
	}

	File.Open(FileOpenType::Write, FileDataType::Binary);

	GameEngineSerializer Ser;

	int Size = GetEventSize();

	Ser << Size;
	if (0 == Size)
	{
		return;
	}

	for (std::pair<const int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : Events)
	{
		for (const std::shared_ptr<FrameEventObject>& Object : Pair.second)
		{
			Object->Write(Ser);
		}
	}

	File.Write(Ser);
}

void FrameEventHelper::PlayEvents(int _Frame)
{
	if (EventInfo.empty())
	{
		return;
	}

	if (FrameCount < _Frame)
	{
		MsgBoxAssert("현재 프레임이 최대 프레임을 초과했습니다.");	
		return;
	}

	std::list<FrameEventObject*>& EventList = EventInfo.at(_Frame);
	if (EventList.empty())
	{
		return;
	}

	for (FrameEventObject* EventObject : EventList)
	{
		EventObject->PlayEvent();
	}
}

int FrameEventHelper::GetEventSize()
{
	size_t EventCnt = 0;
	for (std::pair<const int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : Events)
	{
		EventCnt += Pair.second.size();
	}

	return static_cast<int>(EventCnt);
}

void FrameEventHelper::PushPlayingEvent(FrameEventObject* _Object)
{
	PlayingEvents.push_back(_Object);
}

void FrameEventHelper::UpdateEvent(float _Delta)
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
		if (EVENT_PLAY == pObject->UpdateEvent(_Delta))
		{
			++StartIter;
			continue;
		}

		StartIter = PlayingEvents.erase(StartIter);
	}
}

void FrameEventHelper::SetEvent(std::shared_ptr<FrameEventObject> _EventObject)
{
	_EventObject->SetParent(this);
	Events[_EventObject->GetEventID()].push_back(_EventObject);
	EventInfo.at(_EventObject->GetFrame()).push_back(_EventObject.get());
}

void FrameEventHelper::PopEvent(const std::shared_ptr<FrameEventObject>& _Event)
{
	EventInfo[_Event->GetFrame()].remove(_Event.get());
	Events.at(_Event->GetEventID()).remove(_Event);
}

std::list<std::shared_ptr<FrameEventObject>>& FrameEventHelper::GetEventGroup(int _Type)
{
	return Events[_Type];
}