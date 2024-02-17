#include "PreCompile.h"
#include "DummyGUI.h"

#include "DummyActor.h"

DummyGUI::DummyGUI() 
{
}

DummyGUI::~DummyGUI() 
{
}


void DummyGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == pActor)
	{
		pActor = _Level->CreateActor<DummyActor>(Enum_UpdateOrder::Monster).get();
	}

	if (nullptr == pActor)
	{
		MsgBoxAssert("액터가 존재하지 않습니다.");
		return;
	}

	if (ImGui::Checkbox("Update Box", &bUpdate))
	{
		if (bUpdate)
		{
			pActor->On();
		}
		else
		{
			pActor->Off();
		}
	}

	if (ImGui::Checkbox("Follow Update", &bCameraControl))
	{
		if (bCameraControl)
		{
			pActor->AttachCamera();
		}
		else
		{
			pActor->DettachCamera();
		}
	}
}

void DummyGUI::LevelEnd()
{
	if (nullptr != pActor)
	{
		pActor->Death();
		pActor->DettachCamera();
		pActor = nullptr;
	}
}