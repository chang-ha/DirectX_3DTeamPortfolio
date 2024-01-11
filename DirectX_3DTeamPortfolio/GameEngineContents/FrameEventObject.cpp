#include "PreCompile.h"
#include "FrameEventObject.h"

FrameEventObject::FrameEventObject() 
{
}

FrameEventObject::~FrameEventObject() 
{
}

std::string FrameEventObject::GetTypeString() const
{
	std::string ReturnValue;
	switch (Type)
	{
	case None:
		break;
	case Sound:
		ReturnValue = "Sound";
		break;
	case Collision:
		ReturnValue = "Collision";
		break;
	case Transfrom:
		ReturnValue = "Transfrom";
		break;
	default:
		break;
	}

	return ReturnValue;
}