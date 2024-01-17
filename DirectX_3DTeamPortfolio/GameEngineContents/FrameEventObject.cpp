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
	case None:
		break;
	case Sound:
		ReturnValue = "Sound";
		break;
	case CollisionUpdate:
		ReturnValue = "CollisionUpdate";
		break;
	case Transfrom:
		ReturnValue = "Transfrom";
		break;
	default:
		break;
	}

	return ReturnValue;
}

int FrameEventObject::GetCurFrame()
{
	return static_cast<int>(ParentHelper->GetAnimationInfo()->CurFrame);
}