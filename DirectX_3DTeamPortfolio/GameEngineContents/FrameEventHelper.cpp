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

void FrameEventHelper::Initialze()
{
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
	if (Events.empty())
	{
		Events.resize(FrameCount);
	}

	for (std::shared_ptr<SoundFrameEvent>& SEvent : SoundEvents)
	{
		int Frame = SEvent->StartFrame;
		std::list<FrameEventObject*>& EventList = Events.at(Frame);
		EventList.push_back(SEvent.get());
	}
}

void FrameEventHelper::SaveFile(std::string_view _Path)
{
	GameEngineFile File(_Path.data());
	if (File.IsDirectory())
	{
		MsgBoxAssert("���� ��ο� ���⸦ �� �� �����ϴ�.");
		return;
	}

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
		MsgBoxAssert("���� �������� �ִ� �������� �ʰ��߽��ϴ�.");	
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