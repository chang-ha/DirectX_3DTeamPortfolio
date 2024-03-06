#include "PreCompile.h"
#include "FrameEventObject.h"

#include "FrameEventHelper.h"
#include "FrameEventManager.h"

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
	case Enum_FrameEventType::SingleCenterSound:
		ReturnValue = "SingleCenterSound";
		break;
	case Enum_FrameEventType::DPSound:
		ReturnValue = "DPSound";
		break;
	case Enum_FrameEventType::CenterMultiSound:
		ReturnValue = "CenterMultiSound";
		break;
	case Enum_FrameEventType::CollisionUpdate:
		ReturnValue = "CollisionUpdate";
		break;
	case Enum_FrameEventType::SwitchFlag:
		ReturnValue = "SwitchFlag";
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
	int CurFrame = static_cast<int>(ParentManager->GetAnimationInfo()->CurFrame);
	return CurFrame;
}

GameContentsFBXRenderer* FrameEventObject::GetParentRenderer() const
{
	if (nullptr == ParentManager)
	{
		MsgBoxAssert("관리자를 모르고 캐스팅을 할 수 없습니다.");
		return nullptr;
	}

	GameContentsFBXAnimationInfo* pInfo = ParentManager->GetAnimationInfo();
	if (nullptr == pInfo)
	{
		MsgBoxAssert("FBXAnimation 정보를 받아오지 못했습니다.");
		return nullptr;
	}

	GameContentsFBXRenderer* FBXRenderer = pInfo->ParentRenderer;
	if (nullptr == FBXRenderer)
	{
		MsgBoxAssert("렌더러가 존재하지 않습니다.");
		return nullptr;
	}

	return FBXRenderer;
}