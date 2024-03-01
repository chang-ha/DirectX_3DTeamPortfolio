#include "PreCompile.h"
#include "CenterBodySoundFrameEvent.h"

#include "FrameEventHelper.h"


CenterBodySoundFrameEvent::CenterBodySoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::CenterBodySound);
}

CenterBodySoundFrameEvent::~CenterBodySoundFrameEvent()
{
}


std::shared_ptr<CenterBodySoundFrameEvent> CenterBodySoundFrameEvent::CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName)
{
	std::shared_ptr<CenterBodySoundFrameEvent> SEvent = std::make_shared<CenterBodySoundFrameEvent>();
	SEvent->StartFrame = _Frame;
	SEvent->BoneIndex = _iBoneIndex;
	SEvent->SoundName = _FileName;
	return SEvent;
}

void CenterBodySoundFrameEvent::PlayEvent()
{
	if (nullptr == pActor)
	{
		Init();
	}

	float4x4 BoneWMat = BoneMatrix * pActor->Transform.GetWorldMatrix();
	float4 S;
	float4 Q;
	float4 P;
	BoneWMat.Decompose(S, Q, P);
	GameEngineSound::Sound3DPlay(SoundName, P);
}

void CenterBodySoundFrameEvent::Init()
{
	GameContentsFBXAnimationInfo* pInfo = ParentHelper->GetParentInfo();
	if (nullptr == pInfo)
	{
		MsgBoxAssert("FBXAnimation 정보를 받아오지 못했습니다.");
		return;
	}

	std::vector<float4x4>& BoneMats = pInfo->ParentRenderer->GetBoneSockets();
	BoneMatrix = BoneMats.at(BoneIndex);

	pActor = pInfo->ParentRenderer->GetActor();
	if (nullptr == pActor)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return;
	}
}