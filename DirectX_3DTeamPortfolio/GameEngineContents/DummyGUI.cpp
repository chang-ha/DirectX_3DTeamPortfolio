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
	ActorCheck(_Level);

	if (nullptr != pDummy)
	{
		if (ImGui::Checkbox("Update Box", &IsActive))
		{
			pDummy->OnOffSwitch();
		}

		ImGui::InputFloat("Dummy Move Speed", pDummy->GetSpeedPointer(), 1.0f, 100.0f, "%.f");
		ImGui::Spacing();
		ImGui::Separator();
		ImGui::Spacing();

		if (ImGui::Checkbox("Camera Chase", &IsCameraFocus))
		{
			if (IsCameraFocus)
			{
				pDummy->AttachCamera();
			}
			else
			{
				pDummy->DettachCamera();
			}
		}
	}
}

void DummyGUI::LevelEnd()
{
	if (nullptr != pDummy)
	{
		pDummy->Death();
		pDummy = nullptr;
	}
}

void DummyGUI::ActorCheck(GameEngineLevel* _Level)
{
	if (nullptr == pDummy)
	{
		if (nullptr == _Level)
		{
			MsgBoxAssert("레벨이 존재하지 않습니다.");
			return;
		}

		pDummy = _Level->CreateActor<DummyActor>(Enum_UpdateOrder::Monster);
	}
}