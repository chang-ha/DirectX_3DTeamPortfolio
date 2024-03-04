#include "PreCompile.h"
#include "FrameEventHelper.h"

#include "FrameEventManager.h"
#include "BaseActor.h"

#include "SoundFrameEvent.h"
#include "BoneSoundFrameEvent.h"
#include "CenterBodySoundFrameEvent.h"
#include "DummyPolySoundFrameEvent.h"
#include "CollisionUpdateFrameEvent.h"
#include "TurnSpeedFrameEvent.h"

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

std::shared_ptr<FrameEventHelper> FrameEventHelper::Load(class GameContentsFBXAnimationInfo* _AnimationInfo)
{
	BaseActor* pActor = _AnimationInfo->ParentRenderer->GetParent<BaseActor>();
	if (nullptr == pActor)
	{
		MsgBoxAssert("이상한 값이 존재합니다. 터지면 김태훈에게 반드시 문의");
		return nullptr;
	}

	std::string FBXName = _AnimationInfo->GetAnimationName().data();
	std::string AnimationName = GetConvertFileName(FBXName);
	std::string IDName = pActor->GetIDName();
	if (IDName.empty())
	{
		return nullptr;
	}

	GameEnginePath EventPath;
	EventPath.MoveParentToExistsChild("ContentsResources");
	EventPath.MoveChild("ContentsResources");
	EventPath.MoveChild("Mesh");
	EventPath.AppendPath(IDName);
	if (false == EventPath.IsExits())
	{
		return nullptr;
	}

	EventPath.MoveChild("Animation");
	EventPath.AppendPath(AnimationName);
	if (false == EventPath.IsExits())
	{
		return nullptr;
	}

	std::shared_ptr<FrameEventHelper> Helper = FrameEventHelper::Load(EventPath.GetStringPath());
	if (nullptr == Helper)
	{
		MsgBoxAssert("이미 존재하는 객체를 로드하려고 했습니다.");
		return nullptr;
	}

	return Helper;
}

std::shared_ptr<FrameEventManager> FrameEventHelper::Initialze(GameContentsFBXAnimationInfo* _AnimationInfo)
{
	std::shared_ptr<FrameEventManager> NewManager = FrameEventManager::CreateEventManager();
	NewManager->SetHelper(this);
	NewManager->SetAnimationInfo(_AnimationInfo);

	if (0 == FrameCount)
	{
		FrameCount = static_cast<int>(_AnimationInfo->FBXAnimationData->FrameCount + 1);
	
		GameEngineFile File(Path);
		if (false == File.IsExits())
		{
			return NewManager;
		}

		File.Open(FileOpenType::Read, FileDataType::Binary);

		GameEngineSerializer Ser;
		File.DataAllRead(Ser);

		int Size;
	
		Ser >> Size;
		if (0 != Size)
		{
			for (int i = 0; i < Size; i++)
			{
				int TypeNum;
				std::shared_ptr<FrameEventObject> NewEvent;

				Ser >> TypeNum;

				switch (static_cast<Enum_FrameEventType>(TypeNum))
				{
				case Enum_FrameEventType::Sound:
					// 사용하지 않는 이벤트 유형입니다. 기존의 파일을 삭제합니다.
					break;
				case Enum_FrameEventType::BSound:
				{
					NewEvent = std::make_shared<BoneSoundFrameEvent>();
				}
					break;
				case Enum_FrameEventType::CenterBodySound:
				{
					NewEvent = std::make_shared<CenterBodySoundFrameEvent>();
				}
					break;
				case Enum_FrameEventType::DPSound:
				{
					NewEvent = std::make_shared<DummyPolySoundFrameEvent>();
				}
					break;
				case Enum_FrameEventType::CollisionUpdate:
				{
					NewEvent = std::make_shared<CollisionUpdateFrameEvent>();
				}
					break;
				case Enum_FrameEventType::TurnSpeed:
				{
					NewEvent = std::make_shared<TurnSpeedFrameEvent>();
				}
					break;
				default:
					MsgBoxAssert("처리되지 않은 유형의 이벤트입니다. 김태훈에게 문의하세요.");
					return nullptr;
				}

				NewEvent->Read(Ser);
				Events[TypeNum].push_back(NewEvent);
			}
		}
	}

	NewManager->CopyEvent(Events);
	return NewManager;
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

	for (std::pair<const int, std::list<std::shared_ptr<FrameEventObject>>>& Pair : Events)
	{
		for (const std::shared_ptr<FrameEventObject>& Object : Pair.second)
		{
			Object->Write(Ser);
		}
	}

	File.Write(Ser);
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

bool FrameEventHelper::SetEvent(std::shared_ptr<FrameEventObject> _EventObject)
{
 	int EventID =  _EventObject->EventID;

	if (true == Events.contains(EventID))
	{
		std::list<std::shared_ptr<FrameEventObject>>& EventGroup = Events[EventID];
		for (const std::shared_ptr<FrameEventObject>& EventObject : EventGroup)
		{
			if (EventObject->GetFrame() == _EventObject->GetFrame())
			{
				return false;
			}
		}
	}

	Events[_EventObject->GetEventID()].push_back(_EventObject);
	return true;
}

void FrameEventHelper::PopEvent(const std::shared_ptr<FrameEventObject>& _Event)
{
	int ID = _Event->GetEventID();
	int Frame = _Event->GetFrame();
	if (false == Events.contains(ID))
	{
		return;
	}

	std::map<int, std::list<std::shared_ptr<FrameEventObject>>>::iterator FindIter = Events.find(ID);
	std::list<std::shared_ptr<FrameEventObject>>& TypeEvents = FindIter->second;
	std::list<std::shared_ptr<FrameEventObject>>::iterator StartIter = TypeEvents.begin();
	std::list<std::shared_ptr<FrameEventObject>>::iterator EndIter = TypeEvents.end();
	for (; StartIter != EndIter;)
	{
		std::shared_ptr<FrameEventObject> Object = (*StartIter);
		int EventFrame = Object->GetFrame();
		if (EventFrame != Frame)
		{
			++StartIter;
			continue;
		}

		TypeEvents.erase(StartIter);
		break;
	}
}

std::list<std::shared_ptr<FrameEventObject>>& FrameEventHelper::GetEventGroup(int _Type)
{
	return Events[_Type];
}