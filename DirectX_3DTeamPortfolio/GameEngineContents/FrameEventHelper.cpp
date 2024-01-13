#include "PreCompile.h"
#include "FrameEventHelper.h"

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

void FrameEventHelper::Initialze(int _Frame)
{
	if (false == Events.empty())
	{
		return;
	}

	FrameCount = _Frame;
	Events.resize(FrameCount);
	
	GameEngineFile File(Path);
	File.Open(FileOpenType::Read, FileDataType::Binary);

	GameEngineSerializer Ser;
	File.DataAllRead(Ser);

	int SoundEvnetCnt = 0;
	
	Ser >> SoundEvnetCnt;
	if (0 != SoundEvnetCnt)
	{
		for (int i = 0; i < SoundEvnetCnt; i++)
		{
			std::shared_ptr<SoundFrameEvent> NewEvent = std::make_shared<SoundFrameEvent>();
			NewEvent->Read(Ser);
			SoundEvents.push_back(NewEvent);
		}
	}

	PushEventData();
}

void FrameEventHelper::PushEventData()
{
	for (std::shared_ptr<SoundFrameEvent>& SEvent : SoundEvents)
	{
		int Frame = SEvent->StartFrame;
		std::list<FrameEventObject*>& EventList = Events.at(Frame);
		EventList.push_back(SEvent.get());
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

	int SoundEvnetCnt = static_cast<int>(SoundEvents.size());

	Ser << SoundEvnetCnt;
	if (0 != SoundEvnetCnt)
	{
		for (const std::shared_ptr<SoundFrameEvent>& SEvent : SoundEvents)
		{
			SEvent->Write(Ser);
		}
	}

	File.Write(Ser);
}

void FrameEventHelper::PlayEvents(int _Frame)
{
	if (Events.empty())
	{
		return;
	}

	if (FrameCount < _Frame)
	{
		MsgBoxAssert("현재 프레임이 최대 프레임을 초과했습니다.");	
		return;
	}

	std::list<FrameEventObject*>& EventList = Events.at(_Frame);
	if (EventList.empty())
	{
		return;
	}

	for (FrameEventObject* EventObject : EventList)
	{
		EventObject->PlayEvent();
	}
}

int FrameEventHelper::GetEventCount()
{
	int SEventCnt = static_cast<int>(SoundEvents.size());
	return SEventCnt;
}

void FrameEventHelper::CreateSoundEvent(int _StartFrame, std::string_view _SoundName)
{
	for (std::shared_ptr<SoundFrameEvent> SEvent : SoundEvents)
	{
		bool FrameSame = SEvent->StartFrame == _StartFrame;
		bool SoundSame = SEvent->SoundName == _SoundName.data();
		if (FrameSame && SoundSame)
		{
			return;
		}
	}
	std::shared_ptr<SoundFrameEvent> SEvent = std::make_shared<SoundFrameEvent>();
	SEvent->StartFrame = _StartFrame;
	SEvent->SoundName = _SoundName;
	SoundEvents.push_back(SEvent);

	if (Events.empty())
	{
		MsgBoxAssert("Events의 컨테이너가 존재하지 않습니다.");
		return;
	}

	Events.at(_StartFrame).push_back(SEvent.get());
}

void FrameEventHelper::PopEvent(const std::shared_ptr<SoundFrameEvent>& _Event)
{
	Events[_Event->StartFrame].remove(_Event.get());
	Enum_FrameEventType Type = _Event->GetType();
	switch (Type)
	{
	case None:
		break;
	case Sound:
		SoundEvents.remove(_Event);
		break;
	case Collision: 
		break;
	case Transfrom:
		break;
	default:
		break;
	}
}