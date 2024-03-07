#include "PreCompile.h"
#include "MaterialLoopSoundFrameEvent.h"

#include "FrameEventHelper.h"
#include "DS3DummyData.h"
#include "BaseActor.h"


MaterialLoopSoundFrameEvent::MaterialLoopSoundFrameEvent()
{
	SetEventID(Enum_FrameEventType::MaterialLoopSound);
}

MaterialLoopSoundFrameEvent::~MaterialLoopSoundFrameEvent()
{
}


std::shared_ptr<MaterialLoopSoundFrameEvent> MaterialLoopSoundFrameEvent::CreateEventObject(int _Frame, int _SoundIndex)
{
	std::shared_ptr<MaterialLoopSoundFrameEvent> CDPSEvent = std::make_shared<MaterialLoopSoundFrameEvent>();
	CDPSEvent->StartFrame = _Frame;
	CDPSEvent->SoundIndex = _SoundIndex;
	return CDPSEvent;
}

std::shared_ptr<FrameEventObject> MaterialLoopSoundFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<MaterialLoopSoundFrameEvent> NewObject = MaterialLoopSoundFrameEvent::CreateEventObject(StartFrame, SoundIndex);
	return NewObject;
}

int MaterialLoopSoundFrameEvent::PlayEvent()
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

void MaterialLoopSoundFrameEvent::Init()
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