#include "PreCompile.h"
#include "TurnSpeedFrameEvent.h"

#include "BaseActor.h"

TurnSpeedFrameEvent::TurnSpeedFrameEvent()
{
	SetEventID(Enum_FrameEventType::TurnSpeed);
}

TurnSpeedFrameEvent::~TurnSpeedFrameEvent()
{
}


std::shared_ptr<TurnSpeedFrameEvent> TurnSpeedFrameEvent::CreateEventObject(int _SFrame, int _EFrame, float _TurnSpeed)
{
	std::shared_ptr<TurnSpeedFrameEvent> TsEvent = std::make_shared<TurnSpeedFrameEvent>();
	TsEvent->StartFrame = _SFrame;
	TsEvent->EndFrame = _EFrame;
	TsEvent->TurnAngle = _TurnSpeed;
	return TsEvent;
}

std::shared_ptr<FrameEventObject> TurnSpeedFrameEvent::CreatePlayingEvent()
{
	std::shared_ptr<TurnSpeedFrameEvent> NewObject = TurnSpeedFrameEvent::CreateEventObject(StartFrame, EndFrame, TurnAngle);
	return NewObject;
}

int TurnSpeedFrameEvent::PlayEvent()
{
	if (nullptr == pParentActor)
	{
		Init();
	}

	FrameEventManager* pManager = GetEventManger();
	if (nullptr == pManager)
	{
		MsgBoxAssert("매니저를 모르고 사용할 수 없는 기능입니다. 김태훈에게 문의하세요");
		return EVENT_DONE;
	}

	pManager->PushEvent(this);
	return EVENT_DONE;
}

void TurnSpeedFrameEvent::Init()
{
	std::shared_ptr<BaseActor> pObject = GetDynamicCastParentActor<BaseActor>();
	if (nullptr == pObject)
	{
		MsgBoxAssert("다이나믹 캐스팅에 실패했습니다,.");
		return;
	}

	pParentActor = pObject.get();

	if (nullptr != ParentManager)
	{
		const float Inter = ParentManager->GetAnimationInfo()->Inter;
		const float EventTime = static_cast<float>(EndFrame - StartFrame) * Inter;
		TurnSpeed = TurnAngle / EventTime * 0.25f;
	}
}

int TurnSpeedFrameEvent::UpdateEvent(float _Delta)
{
	if (GetCurFrame() >= EndFrame)
	{
		return EVENT_DONE;
	}

	if (nullptr == pParentActor)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return EVENT_ERROR;
	}

	GameEngineActor* pTarget = pParentActor->GetTargetPointer();
	if (nullptr == pTarget)
	{
		return EVENT_PLAY;
	}

	if (bFixSpeed)
	{
		GameEnginePhysXCapsule* pComponent = pParentActor->GetPhysxCapsulePointer();
		if (nullptr == pComponent)
		{
			MsgBoxAssert("피직스 컴포넌트가 존재하지 않습니다.");
			return EVENT_ERROR;
		}

		float RotMinAngle = pParentActor->GetRotMinAngle();
		float TargetAngle = pParentActor->GetTargetAngle();
		float RotDir = pParentActor->GetRotDir_f();

		if (std::fabs(RotMinAngle) < std::fabs(TargetAngle))
		{
			pComponent->AddWorldRotation(float4(0.0f, TurnSpeed * RotDir * _Delta));
		}
	}
	else
	{
		pParentActor->RotToTarget(_Delta, 50.0f, TurnSpeed, 45.0f);
	}

	return EVENT_PLAY;
}