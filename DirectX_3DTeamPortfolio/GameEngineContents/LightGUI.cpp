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
	LightEditor();
}

void LightGUI::LevelEnd()
{
	SelectActor = nullptr;

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
				//Light->
				SelectActor = Light.get();
				//ActorChange();
			}
		}
	}
}


void LightGUI::LightEditor()
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
		}

		if (ImGui::InputFloat3("Pos", &Pos.X))
		{
			SelectActor->Transform.SetLocalPosition(Pos);
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
		



		if (ImGui::InputFloat("LightFar", &Data.LightFar))
		{
		}

		SelectActor->SetLightData(Data);

		/*ImGui::Text("PBR");

		RenderBaseInfo Info = Player::Main_Player->GetFBXRenderer()->RenderBaseInfoValue;

		ImGui::SliderFloat("Metalic", &Info.Metalic, 0.0f, 1.0f);
		ImGui::SliderFloat("Roughness", &Info.Roughness, 0.0f, 1.0f);

		Player::Main_Player->GetFBXRenderer()->RenderBaseInfoValue = Info;*/

		ImGui::TreePop();
	}
}