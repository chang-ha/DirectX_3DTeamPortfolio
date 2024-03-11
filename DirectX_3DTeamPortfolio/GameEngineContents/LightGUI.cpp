#include "PreCompile.h"
#include "LightGUI.h"
#include "ContentsLight.h"
#include "Player.h"

LightGUI::LightGUI() 
{
}

LightGUI::~LightGUI()
{
}


void LightGUI::Start()
{
}

void LightGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ShowLightList(_Level);
	LightEditor(_Level);
}

void LightGUI::LevelEnd()
{
	if (SelectActor != nullptr)
	{
		SelectActor->IsDebugValue = false;
		SelectActor = nullptr;
	}


	ActorNames.clear();
	CObjectNames.clear();
}


void LightGUI::ShowLightList(GameEngineLevel* _Level)
{
	if (true == CObjectNames.empty())
	{
		const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = _Level->GetObjectGroupInt(static_cast<int>(Enum_UpdateOrder::Light));
		if (ObjectGroup.empty())
		{
			return;
		}

		CObjectNames.reserve(ObjectGroup.size());
		ActorNames.reserve(ObjectGroup.size());
		int Cnt = 0;

		for (const std::shared_ptr<GameEngineObject>& Object : ObjectGroup)
		{
			ActorNames.push_back(Object->GetName());
			CObjectNames.push_back(ActorNames[Cnt].c_str());
			Cnt++;
		}
	}

	static int SelectActorIndex = 0;

	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<ContentsLight>>& MonsterGroup = _Level->GetObjectGroupConvert<ContentsLight>(Enum_UpdateOrder::Light);
		for (const std::shared_ptr<ContentsLight>& Light : MonsterGroup)
		{
			if (CObjectNames[SelectActorIndex] == Light->GetName())
			{
				if (SelectActor != nullptr)
				{
					SelectActor->IsDebugValue = false;
				}
				SelectActor = Light.get();
				SelectActor->IsDebugValue = true;
				//ActorChange();
			}
		}
	}
}


void LightGUI::LightEditor(GameEngineLevel* _Level)
{
	if (nullptr == SelectActor)
	{
		return;
	}

	if (ImGui::TreeNode("LightData Editor"))
	{
		if (true == SelectActor->IsDeath())
		{
			SelectActor = nullptr;

			ImGui::TreePop();
			return;
		}

		LightData Data = SelectActor->GetLightData();

		float4 Rot = SelectActor->Transform.GetLocalRotationEuler();
		float4 Pos = SelectActor->Transform.GetLocalPosition();

		float Size = 0.0f;
		//float4 LightColor = Data.LightColor;



		if (ImGui::InputFloat3("Rotation", &Rot.X))
		{
			SelectActor->Transform.SetLocalRotation(Rot);
			_Level->GetMainCamera()->StaticRenderInitValue = true;
			//SelectActor->ChangeShadow = true;
		}

		if (ImGui::InputFloat3("Pos", &Pos.X))
		{
			SelectActor->Transform.SetLocalPosition(Pos);
			_Level->GetMainCamera()->StaticRenderInitValue = true;
			//SelectActor->ChangeShadow = true;
		}

		if (ImGui::InputFloat3("LightColor", &Data.LightColor.X))
		{

		}

		ImGui::SliderFloat3("AmbientLight", &Data.AmbientLight.X, 0.0f, 0.05f,"%.4f");

		if (ImGui::InputFloat("LightPower", &Data.LightPower))
		{
		}

		ImGui::SliderFloat("DifLightPower", &Data.DifLightPower, 0.0f, 5.0f);
		ImGui::SliderFloat("SpcLightPower", &Data.SpcLightPower, 0.0f, 5.0f);
		ImGui::SliderFloat("AmbLightPower", &Data.AmbLightPower, 0.0f, 5.0f);


		ImGui::SliderFloat("SpcPow", &Data.SpcPow, 0.0f, 12.0f);


		ImGui::SliderFloat("ForceLightPower", &Data.ForceLightPower, 0.0f, 2.0f);

		ImGui::SliderFloat("PointLightRange", &Data.PointLightRange, 0.0f, 1000.0f);

		ImGui::InputFloat("constantAttenuation", &Data.constantAttenuation);
		ImGui::InputFloat("linearAttenuation", &Data.linearAttenuation, 0.0f, 0.0f, "%.5f");
		ImGui::InputFloat("quadraticAttenuation", &Data.quadraticAttenuation,0.0f,0.0f,"%.6f");
		


		if (ImGui::Button("Debug"))
		{
			SelectActor->IsDebugValue = !SelectActor->IsDebugValue;
		}
		

		SelectActor->SetLightData(Data);

		std::string CameraPos = "CameraPos: " + _Level->GetMainCamera()->Transform.GetWorldPosition().ToString();
		std::string CameraRot = "CameraRot: " + _Level->GetMainCamera()->Transform.GetWorldRotationEuler().ToString();

		ImGui::Text(CameraPos.c_str());
		ImGui::Text(CameraRot.c_str());

		ImGui::TreePop();
	}
}