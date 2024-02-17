#include "PreCompile.h"
#include "FrameEventObject.h"

#include "FrameEventHelper.h"

FrameEventObject::FrameEventObject() 
{
}

FrameEventObject::~FrameEventObject() 
{
}

std::string FrameEventObject::GetTypeString() const
{
	std::string ReturnValue;
	switch (static_cast<Enum_FrameEventType>(EventID))
	{
	case Enum_FrameEventType::None:
		break;
	case Enum_FrameEventType::Sound:
		ReturnValue = "Sound";
		break;
	case Enum_FrameEventType::BSound:
		ReturnValue = "BSound";
		break;
	case Enum_FrameEventType::CollisionUpdate:
		ReturnValue = "CollisionUpdate";
		break;
	case Enum_FrameEventType::Transfrom:
		ReturnValue = "Transfrom";
		break;
	case Enum_FrameEventType::TurnSpeed:
		ReturnValue = "TurnSpeed";
		break;
	default:
		break;
	}

	return ReturnValue;
}

int FrameEventObject::GetCurFrame()
{
	int CurFrame = static_cast<int>(ParentHelper->GetAnimationInfo()->CurFrame);
	return CurFrame;
}