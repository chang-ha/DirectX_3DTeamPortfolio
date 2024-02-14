#include "PreCompile.h"
#include "BoneSoundFrameEvent.h"

#include "FrameEventHelper.h"


BoneSoundFrameEvent::BoneSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::BSound);
}

BoneSoundFrameEvent::~BoneSoundFrameEvent()
{
}


std::shared_ptr<BoneSoundFrameEvent> BoneSoundFrameEvent::CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName)
{
	std::shared_ptr<BoneSoundFrameEvent> SEvent = std::make_shared<BoneSoundFrameEvent>();
	SEvent->StartFrame = _Frame;
	SEvent->BoneIndex = _iBoneIndex;
	SEvent->SoundName = _FileName;
	return SEvent;
}

void BoneSoundFrameEvent::PlayEvent()
{
	if (nullptr == pActor)
	{
		Init();
	}

	float4 wBonePos = pActor->Transform.GetWorldPosition() * (*pBoneData).Pos;
	GameEngineSound::Sound3DPlay(SoundName, wBonePos);
}

void BoneSoundFrameEvent::Init()
{
	GameContentsFBXAnimationInfo* pInfo = ParentHelper->GetParentInfo();
	if (nullptr == pInfo)
	{
		MsgBoxAssert("FBXAnimation 정보를 받아오지 못했습니다.");
		return;
	}

	const std::vector<AnimationBoneData>& BoneDatas = pInfo->ParentRenderer->GetBoneDatas();
	pBoneData = &BoneDatas.at(BoneIndex);

	pActor = pInfo->ParentRenderer->GetActor();
	if (nullptr == pActor)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return;
	}
}