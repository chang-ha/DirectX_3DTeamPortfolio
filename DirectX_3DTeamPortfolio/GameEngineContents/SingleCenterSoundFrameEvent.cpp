#include "PreCompile.h"
#include "SingleCenterSoundFrameEvent.h"

#include "FrameEventHelper.h"
#include "DS3DummyData.h"
#include "BaseActor.h"


SingleCenterSoundFrameEvent::SingleCenterSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::SingleCenterSound);
}

SingleCenterSoundFrameEvent::~SingleCenterSoundFrameEvent()
{
} 


std::shared_ptr<SingleCenterSoundFrameEvent> SingleCenterSoundFrameEvent::CreateEventObject(int _Frame)
{
	std::shared_ptr<SingleCenterSoundFrameEvent> CDPSEvent = std::make_shared<SingleCenterSoundFrameEvent>();
	CDPSEvent->StartFrame = _Frame;
	return CDPSEvent;
}

std::shared_ptr<FrameEventObject> SingleCenterSoundFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<SingleCenterSoundFrameEvent> NewObject = SingleCenterSoundFrameEvent::CreateEventObject(StartFrame);
	return NewObject;
}

int SingleCenterSoundFrameEvent::PlayEvent()
{
	return EVENT_ERROR;

	if (nullptr == FbxRenderer || nullptr == pActor)
	{
		Init();
	}

	const float4x4& WorldMatrix = FbxRenderer->Transform.GetWorldMatrix();
	float4 WDPPOS = DPT* (*pBoneMatrix) * WorldMatrix;
	return EVENT_DONE;
}

void SingleCenterSoundFrameEvent::Init()
{
	FbxRenderer = GetParentRenderer();
	if (nullptr == FbxRenderer)
	{
		MsgBoxAssert(GetTypeString() + "존재하지 않는 렌더러를 참조했습니다.");
		return;
	}

	pActor = GetDynamicCastParentActor<BaseActor>().get();
	if (nullptr == pActor)
	{
		MsgBoxAssert(GetTypeString() + "존재하지 않는 부모를 참조하려 했습니다.");
		return;
	}

	const int RefIndex = pActor->GetCenterDPIndex();
	std::string IDName = pActor->GetIDName();
	const std::shared_ptr<DS3DummyData>& pRes = DS3DummyData::Find(IDName);
	if (nullptr == pRes)
	{
		MsgBoxAssert(GetTypeString() + "데이터를 불러오지 못했습니다");
		return;
	}

	const DummyData* pDummyData = pRes->GetDummyData(RefIndex);
	if (nullptr == pDummyData)
	{
		MsgBoxAssert(GetTypeString() + "더미 데이터가 존재하지 않습니다");
		return;
	}

	const int AttachBoneIndex = pDummyData->AttachBoneIndex;
	DPT = pDummyData->Position;

	std::vector<float4x4>& BoneMats = FbxRenderer->GetBoneSockets();
	pBoneMatrix = &BoneMats.at(AttachBoneIndex);
}