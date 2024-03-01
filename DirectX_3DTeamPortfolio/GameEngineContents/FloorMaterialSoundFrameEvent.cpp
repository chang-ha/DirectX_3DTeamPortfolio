#include "PreCompile.h"
#include "FloorMaterialSoundFrameEvent.h"

#include "FrameEventHelper.h"


FloorMaterialSoundFrameEvent::FloorMaterialSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::FloorMaterialSound);
}

FloorMaterialSoundFrameEvent::~FloorMaterialSoundFrameEvent()
{
}


std::shared_ptr<FloorMaterialSoundFrameEvent> FloorMaterialSoundFrameEvent::CreateEventObject(int _Frame, int _iBoneIndex, std::string_view _FileName)
{
	std::shared_ptr<FloorMaterialSoundFrameEvent> SEvent = std::make_shared<FloorMaterialSoundFrameEvent>();
	SEvent->StartFrame = _Frame;
	SEvent->BoneIndex = _iBoneIndex;
	SEvent->SoundName = _FileName;
	return SEvent;
}

void FloorMaterialSoundFrameEvent::PlayEvent()
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

void FloorMaterialSoundFrameEvent::Init()
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