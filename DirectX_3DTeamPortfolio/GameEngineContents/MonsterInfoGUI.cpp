#include "PreCompile.h"
#include "MonsterInfoGUI.h"

#include "BaseMonster.h"

MonsterInfoGUI::MonsterInfoGUI() 
{
}

MonsterInfoGUI::~MonsterInfoGUI() 
{
}

void MonsterInfoGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	SelectMonsterList(_Level);
	MonsterInfo();
}

void MonsterInfoGUI::LevelEnd()
{
	LevelActorList.clear();
	CLevelActorList.clear();
	SelectActorIndex = -1;
	pMonster = nullptr;
}

void MonsterInfoGUI::SelectMonsterList(GameEngineLevel* _Level)
{
	if (LevelActorList.empty())
	{
		const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = _Level->GetObjectGroup(Enum_UpdateOrder::Monster);
		if (false == ObjectGroup.empty())
		{
			LevelActorList.reserve(ObjectGroup.size());
			CLevelActorList.reserve(ObjectGroup.size());
			int Cnt = 0;

			for (const std::shared_ptr<GameEngineObject>& Object : ObjectGroup)
			{
				std::string ObjectName = Object->GetName();
				if (false == ObjectName.empty())
				{
					LevelActorList.push_back(ObjectName);
					CLevelActorList.push_back(LevelActorList[Cnt].c_str());
					Cnt++;
				}
			}
		}
	}

	if (false == LevelActorList.empty())
	{
		if (ImGui::Combo("Mosnter List", &SelectActorIndex, &CLevelActorList[0], static_cast<int>(CLevelActorList.size())))
		{
			std::vector<std::shared_ptr<BaseMonster>> MonsterGroup = _Level->GetObjectGroupConvert<BaseMonster>(Enum_UpdateOrder::Monster);

			for (const std::shared_ptr<BaseMonster>& Monster : MonsterGroup)
			{
				std::string ObjName = Monster->GetName();

				if (CLevelActorList[SelectActorIndex] == ObjName)
				{
					pMonster = Monster.get();
				}
			}
		}
	}
}

void MonsterInfoGUI::MonsterInfo()
{
	if (nullptr == pMonster)
	{
		return;
	}

	float4 WPos = pMonster->Transform.GetWorldPosition();

	ImGui::Text(WPos.ToString().c_str());
	ImGui::Spacing();

	if (ImGui::InputFloat3("Set Scale", &MonsterScale.X, "%.f"))
	{
		pMonster->Transform.SetLocalScale(MonsterScale);
	}

	if (ImGui::InputFloat3("Set Pos", &MonsterPos.X, "%.f"))
	{
		pMonster->SetWPosition(MonsterPos);
	}

	ImGui::Separator();

	if (ImGui::Button("Wake Up"))
	{
		pMonster->WakeUp();
	}

	if (ImGui::Checkbox("Zero Pos", &bFixPos))
	{
		bFixPos ? pMonster->GravityOff() : pMonster->GravityOn();
	}

	if (bFixPos)
	{
		pMonster->GetPhysxCapsulePointer()->SetWorldPosition(float4(0.0f));
	}
}