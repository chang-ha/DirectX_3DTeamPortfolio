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
		MsgBoxAssert("���Ͱ� �������� �ʽ��ϴ�.");
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

	ImGui::SliderFloat("Set Speed", pActor->GetSpeedPointer(), 100.0f, 1000.0f, "%.f");
}

void DummyGUI::LevelEnd()
{
	if (nullptr != pActor)
	{
		pActor->Death();
		pActor->DettachCamera();
		pActor = nullptr;
	}

	bUpdate = false;
	bCameraControl = false;
}