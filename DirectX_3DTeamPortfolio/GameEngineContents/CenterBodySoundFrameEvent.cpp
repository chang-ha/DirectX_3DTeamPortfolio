#include "PreCompile.h"
#include "CenterBodySoundFrameEvent.h"

#include "FrameEventHelper.h"
#include "DS3DummyData.h"
#include "BaseActor.h"


CenterBodySoundFrameEvent::CenterBodySoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::CenterBodySound);
}

CenterBodySoundFrameEvent::~CenterBodySoundFrameEvent()
{
}


std::shared_ptr<CenterBodySoundFrameEvent> CenterBodySoundFrameEvent::CreateEventObject(int _Frame)
{
	std::shared_ptr<CenterBodySoundFrameEvent> CDPSEvent = std::make_shared<CenterBodySoundFrameEvent>();
	CDPSEvent->StartFrame = _Frame;
	return CDPSEvent;
}

std::shared_ptr<FrameEventObject> CenterBodySoundFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<CenterBodySoundFrameEvent> NewObject = CenterBodySoundFrameEvent::CreateEventObject(StartFrame);
	return NewObject;
}

void CenterBodySoundFrameEvent::PlayEvent()
{
	if (nullptr == FbxRenderer || nullptr == pActor)
	{
		Init();
	}

	std::string_view SoundName = pActor->GetFloorMaterialName();
	if (SoundName.empty())
	{
		return;
	}

	const float4x4& WorldMatrix = FbxRenderer->Transform.GetWorldMatrix();
	float4 WDPPOS = DPT* (*pBoneMatrix) * WorldMatrix;
	GameEngineSound::Sound3DPlay(SoundName, WDPPOS);
}

void CenterBodySoundFrameEvent::Init()
{
	FbxRenderer = GetParentRenderer();
	if (nullptr == FbxRenderer)
	{
		MsgBoxAssert(GetTypeString() + "�������� �ʴ� �������� �����߽��ϴ�.");
		return;
	}

	pActor = GetDynamicCastParentActor<BaseActor>().get();
	if (nullptr == pActor)
	{
		MsgBoxAssert(GetTypeString() + "�������� �ʴ� �θ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	const int RefIndex = pActor->GetCenterDPIndex();
	std::string IDName = pActor->GetIDName();
	const std::shared_ptr<DS3DummyData>& pRes = DS3DummyData::Find(IDName);
	if (nullptr == pRes)
	{
		MsgBoxAssert(GetTypeString() + "�����͸� �ҷ����� ���߽��ϴ�");
		return;
	}

	const DummyData* pDummyData = pRes->GetDummyData(RefIndex);
	if (nullptr == pDummyData)
	{
		MsgBoxAssert(GetTypeString() + "���� �����Ͱ� �������� �ʽ��ϴ�");
		return;
	}

	const int AttachBoneIndex = pDummyData->AttachBoneIndex;
	DPT = pDummyData->Position;

	std::vector<float4x4>& BoneMats = FbxRenderer->GetBoneSockets();
	pBoneMatrix = &BoneMats.at(AttachBoneIndex);
}