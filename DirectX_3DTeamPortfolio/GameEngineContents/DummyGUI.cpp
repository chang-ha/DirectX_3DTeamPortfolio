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

	ImGui::SliderFloat("Set Speed", pActor->GetSpeedPointer(), 100.0f, 1000.0f, "%.f");

	ImGui::Spacing();
	ImGui::Spacing();
	HelpString();
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

void DummyGUI::HelpString()
{
	ImGui::Text("key R & E : Height");
	ImGui::Text("key Arrow : Move");
	ImGui::Text("key LMouse : Shot Bullet");
	ImGui::Text("key MMouse | VK_Ctrl : CloseUp & Down");
	ImGui::Text("key RMouse : Rotate");
}