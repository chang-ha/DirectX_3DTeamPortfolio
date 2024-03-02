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


std::shared_ptr<CenterBodySoundFrameEvent> CenterBodySoundFrameEvent::CreateEventObject(int _Frame, int _RefID, int _AttachBoneIndex)
{
	std::shared_ptr<CenterBodySoundFrameEvent> CDPSEvent = std::make_shared<CenterBodySoundFrameEvent>();
	CDPSEvent->StartFrame = _Frame;
	CDPSEvent->RefID = _RefID;
	CDPSEvent->AttachBoneIndex = _AttachBoneIndex;
	return CDPSEvent;
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

	std::string IDName = pActor->GetIDName();
	const std::shared_ptr<DS3DummyData>& pRes = DS3DummyData::Find(IDName);
	if (nullptr == pRes)
	{
		MsgBoxAssert(GetTypeString() + "�����͸� �ҷ����� ���߽��ϴ�");
		return;
	}

	bool ISOK = (FE_NOINDEX != RefID && FE_NOINDEX != AttachBoneIndex);
	if (false == ISOK)
	{
		MsgBoxAssert(GetTypeString() + "�κ�Ʈ �������� �ʱ�ȭ���� �ʾҽ��ϴ�.");
		return;
	}

	const DummyData& pDummyData = pRes->GetDummyData(RefID, AttachBoneIndex);
	const int ParentBIndex = pDummyData.ParentBoneIndex;
	DPT = pDummyData.Position;

	std::vector<float4x4>& BoneMats = FbxRenderer->GetBoneSockets();
	pBoneMatrix = &BoneMats.at(ParentBIndex);
}