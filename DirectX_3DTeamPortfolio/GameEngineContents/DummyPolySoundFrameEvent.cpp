#include "PreCompile.h"
#include "DummyPolySoundFrameEvent.h"

#include "FrameEventHelper.h"
#include "BaseActor.h"
#include "DS3DummyData.h"


DummyPolySoundFrameEvent::DummyPolySoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::DPSound);
}

DummyPolySoundFrameEvent::~DummyPolySoundFrameEvent()
{
	SoundName.clear();
}

 
std::shared_ptr<DummyPolySoundFrameEvent> DummyPolySoundFrameEvent::CreateEventObject(int _Frame, std::string_view _SoundName, int _RefID, int _AttachBoneIndex)
{
	std::shared_ptr<DummyPolySoundFrameEvent> DPSEvent = std::make_shared<DummyPolySoundFrameEvent>();
	DPSEvent->StartFrame = _Frame;
	DPSEvent->SoundName = _SoundName;
	DPSEvent->RefID = _RefID;
	DPSEvent->AttachBoneIndex = _AttachBoneIndex;
	return DPSEvent;
}

std::shared_ptr<FrameEventObject> DummyPolySoundFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<DummyPolySoundFrameEvent> NewObject = DummyPolySoundFrameEvent::CreateEventObject(StartFrame, SoundName, RefID, AttachBoneIndex);
	return NewObject;
}

void DummyPolySoundFrameEvent::PlayEvent()
{
	if (nullptr == FbxRenderer)
	{
		Init();
	}

	const float4x4& WorldMatrix = FbxRenderer->Transform.GetWorldMatrix();
	float4 WDPPOS = DPT * (*pBoneMatrix) * WorldMatrix;
	GameEngineSound::Sound3DPlay(SoundName, WDPPOS, 1.f, 0, 50.f, 8000.f);
}

void DummyPolySoundFrameEvent::Init()
{
	FbxRenderer = GetParentRenderer();
	if (nullptr == FbxRenderer)
	{
		MsgBoxAssert(GetTypeString() + "�������� �ʴ� �������� �����߽��ϴ�.");
		return;
	}

	const std::shared_ptr<BaseActor>& pActor = GetDynamicCastParentActor<BaseActor>();
	if (nullptr == pActor)
	{
		MsgBoxAssert(GetTypeString() + "�������� �ʴ� �θ� �����Ϸ� �߽��ϴ�.");
		return;
	}

	std::string IDName = pActor->GetIDName();
	const std::shared_ptr<DS3DummyData>& pRes = DS3DummyData::Find(IDName);
	if (nullptr == pRes)
	{
		MsgBoxAssert(GetTypeString() + "�����͸� �ҷ����� ���߽��ϴ�");
		return;
	}

	bool ISOK = (FE_NOINDEX != RefID);
	if (false == ISOK)
	{
		MsgBoxAssert(GetTypeString() + "�κ�Ʈ �������� �ʱ�ȭ���� �ʾҽ��ϴ�.");
		return;
	}

	const DummyData* pDummyData = pRes->GetDummyData(RefID, AttachBoneIndex);
	if (nullptr == pDummyData)
	{
		MsgBoxAssert(GetTypeString() + "���� �����Ͱ� �������� �ʽ��ϴ�.");
		return;
	}

	const int ParentBIndex = pDummyData->ParentBoneIndex;
	DPT = pDummyData->Position;

	std::vector<float4x4>& BoneMats = FbxRenderer->GetBoneSockets();
	pBoneMatrix = &BoneMats.at(ParentBIndex);
}