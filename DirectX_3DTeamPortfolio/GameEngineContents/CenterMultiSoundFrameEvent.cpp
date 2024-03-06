#include "PreCompile.h"
#include "CenterMultiSoundFrameEvent.h"

#include "FrameEventHelper.h"
#include "DS3DummyData.h"
#include "BaseActor.h"


CenterMultiSoundFrameEvent::CenterMultiSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::CenterMultiSound);
}

CenterMultiSoundFrameEvent::~CenterMultiSoundFrameEvent()
{
}


std::shared_ptr<CenterMultiSoundFrameEvent> CenterMultiSoundFrameEvent::CreateEventObject(int _Frame)
{
	std::shared_ptr<CenterMultiSoundFrameEvent> CDPSEvent = std::make_shared<CenterMultiSoundFrameEvent>();
	CDPSEvent->StartFrame = _Frame;
	return CDPSEvent;
}

std::shared_ptr<FrameEventObject> CenterMultiSoundFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<CenterMultiSoundFrameEvent> NewObject = CenterMultiSoundFrameEvent::CreateEventObject(StartFrame);
	return NewObject;
}

int CenterMultiSoundFrameEvent::PlayEvent()
{
	if (nullptr == FbxRenderer || nullptr == pActor)
	{
		Init();
	}

	std::string_view SoundName = pActor->GetMaterialSoundName(SoundIndex);
	if (SoundName.empty())
	{
		return EVENT_ERROR;
	}

	const float4x4& WorldMatrix = FbxRenderer->Transform.GetWorldMatrix();
	float4 WDPPOS = DPT * (*pBoneMatrix) * WorldMatrix;
	GameEngineSound::Sound3DPlay(SoundName, WDPPOS);

	return EVENT_DONE;
}

void CenterMultiSoundFrameEvent::Init()
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