#include "PreCompile.h"
#include "TestLevel_Monster.h"
#include <GameEngineCore/GameEngineGUI.h>

#include "Monster_LothricKn.h"
#include "Monster_HollowSoldier.h"


// _Level == TestLevel_Monster 
void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (bool MonsterCountTestCode = true)
	{
		ShowLothricKnCount(_Level);
	}

	if (nullptr == CurLevel)
	{
		CurLevel = static_cast<TestLevel_Monster*>(_Level);
	}

	if (true == CObjectNames.empty())
	{
		CopyObjectName();
	}

	ShowObjectNameList();

	if (nullptr == SelectActor)
	{
		return;
	}

	if (true == SelectActor->IsDeath())
	{
		SelectActor = nullptr;
		AnimationNames.clear();
		return;
	}

	SetTransform();

	if (true == AnimationNames.empty())
	{
		CopyAnimationName();
	}

	if (ImGui::ListBox("Aniamtion Name", &SelectAnimationIndex, &CAnimationNames[0], static_cast<int>(CAnimationNames.size())))
	{
		const char* SelectAnimationName = CAnimationNames.at(SelectAnimationIndex);
		SelectActor->GetFBXRenderer()->ChangeAnimation(SelectAnimationName);
		CurAnimationInfo = SelectActor->GetFBXRenderer()->GetAnimationInfos()[AnimationNames.at(SelectAnimationIndex)];
	}

	std::vector<std::vector<std::shared_ptr<GameEngineRenderUnit>>>& RenderUnits = SelectActor->GetFBXRenderer()->RenderUnits;
	const int IndexCount = static_cast<int>(RenderUnits.size());
	for (int i = 0; i < IndexCount; i++)
	{
		if (ImGui::Button(std::to_string(i).c_str()))
		{
			RenderUnits[i][0]->OnOffSwitch();
		}
	}

	 
	
	if (bool TestCode = false)
	{
		if (ImGui::TreeNode("Mesh Editor"))
		{
			if (ImGui::TreeNode("Animation Tree"))
			{

				ImGui::TreePop();
			}

			ImGui::TreePop();
		}

		if (ImGui::BeginTabBar("Eidtor"))
		{
			if (ImGui::BeginTabItem("Setting"))
			{
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Help"))
			{
				ImGui::EndTabItem();
			}
		}
		ImGui::EndTabBar();
	}
}

void MonsterGUI::SetTransform()
{
	Size = SelectActor->Transform.GetLocalScale().X;
	Rot = SelectActor->Transform.GetLocalRotationEuler();
	Pos = SelectActor->Transform.GetLocalPosition();

	if (ImGui::InputFloat("Set Scale", &Size))
	{
		SelectActor->Transform.SetLocalScale(float4(Size, Size, Size));
	}

	if (ImGui::InputFloat3("Set Rotation", &Rot.X))
	{
		SelectActor->Transform.SetLocalRotation(Rot);
	}

	if (ImGui::InputFloat3("Set Pos", &Pos.X))
	{
		SelectActor->Transform.SetLocalPosition(Pos);
	}
}

void MonsterGUI::ShowLothricKnCount(GameEngineLevel* _Level)
{
	std::vector<std::shared_ptr<Monster_LothricKn>> Monsters = _Level->GetObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	if (true == Monsters.empty())
	{
		return;
	}

	int MonsterCount = static_cast<int>(Monsters.size());
	ImGui::Text(std::string("ObjectCount : " + std::to_string(MonsterCount)).c_str());
}

void MonsterGUI::ShowObjectNameList()
{
	if (ImGui::ListBox("ActorList", &SelectActorIndex, &CObjectNames[0], static_cast<int>(CObjectNames.size())))
	{
		std::string ActorName = CObjectNames[SelectActorIndex];
		if (true == ActorName.empty())
		{
			return;
		}

		const std::vector<std::shared_ptr<CommonMonster>>& MonsterGroup = CurLevel->GetObjectGroupConvert<CommonMonster>(Enum_UpdateOrder::Monster);
		for (const std::shared_ptr<CommonMonster>& Monster : MonsterGroup)
		{
			if (CObjectNames[SelectActorIndex] == Monster->GetName())
			{
				SelectActor = Monster.get();
				AnimationNames.clear();
				CAnimationNames.clear();
				CurAnimationInfo = nullptr;
			}
		}
	}
}

void MonsterGUI::CopyObjectName()
{
	const std::list<std::shared_ptr<GameEngineObject>>& ObjectGroup = CurLevel->GetObjectGroupInt(static_cast<int>(Enum_UpdateOrder::Monster));

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


void MonsterGUI::CopyAnimationName()
{
	std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& Animations = SelectActor->GetFBXRenderer()->GetAnimationInfos();
	AnimationNames.reserve(Animations.size());
	CAnimationNames.reserve(Animations.size());

	int CurIndex = 0;
	for (std::pair<const std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& _Pair : Animations)
	{
		AnimationNames.push_back(_Pair.first);
		CAnimationNames.push_back(AnimationNames[CurIndex].c_str());
		CurIndex++;
	}
}


void MonsterGUI::Release()
{
	CurAnimationInfo = nullptr;
	SelectActor = nullptr;
	ActorNames.clear();
	CObjectNames.clear();
	AnimationNames.clear();
	CAnimationNames.clear();
}





TestLevel_Monster::TestLevel_Monster() 
{
	GameEngineInput::AddInputObject(this);
}

TestLevel_Monster::~TestLevel_Monster() 
{
}

void TestLevel_Monster::Start()
{
	GetMainCamera()->GetCameraAllRenderTarget()->SetClearColor(float4::BLUE);

	MonsterWindow = GameEngineGUI::CreateGUIWindow<MonsterGUI>("MonsterGUI");
	MonsterWindow->Off();
}

void TestLevel_Monster::Update(float _Delta)
{
	if (nullptr != MonsterWindow && true == GameEngineInput::IsDown('=', this))
	{
		MonsterWindow->OnOffSwitch();
	}
}

void TestLevel_Monster::LevelStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<Monster_LothricKn>(static_cast<int>(Enum_UpdateOrder::Monster), "LothricKn");
	CreateActor<Monster_HollowSoldier>(static_cast<int>(Enum_UpdateOrder::Monster), "HollowSoldier");
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	AllDeathObjectGroupConvert<Monster_HollowSoldier>(Enum_UpdateOrder::Monster);

	if (nullptr != MonsterWindow)
	{
		MonsterWindow->Release();
		MonsterWindow->Off();
	}
}