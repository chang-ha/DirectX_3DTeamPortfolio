#include "PreCompile.h"
#include "TestLevel_Monster.h"
#include <GameEngineCore/GameEngineGUI.h>

#include "Monster_LothricKn.h"
#include "MonsterEditorActor.h"


// _Level == TestLevel_Monster 
void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (bool MonsterCountTestCode = true)
	{
		ShowLothricKnCount(_Level);
	}


	TestLevel_Monster* TestLevel = static_cast<TestLevel_Monster*>(_Level);
	if (nullptr == TestLevel)
	{
		return;
	}

	if (nullptr == TestLevel->EditorActor)
	{
		return;
	}

	if (true == AnimationNames.empty())
	{
		CopyAnimationName(TestLevel);
	}

	if (ImGui::ListBox("Aniamtion Name", &SelectAnimationIndex, &CAnimationNames[0], static_cast<int>(CAnimationNames.size()), 8))
	{
		const char* SelectAnimationName = CAnimationNames.at(SelectAnimationIndex);
		TestLevel->EditorActor->GetRenderer()->ChangeAnimation(SelectAnimationName);
		CurAnimationInfo = TestLevel->EditorActor->GetRenderer()->GetAnimationInfos()[AnimationNames.at(SelectAnimationIndex)];
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

void MonsterGUI::CopyAnimationName(class TestLevel_Monster* _Level)
{
	std::map<std::string, std::shared_ptr<GameEngineFBXAnimationInfo>>& Animations = _Level->EditorActor->GetRenderer()->GetAnimationInfos();
	AnimationNames.reserve(Animations.size());
	CAnimationNames.reserve(Animations.size());

	int CurIndex = 0;
	for (std::pair<const std::string, std::shared_ptr<GameEngineFBXAnimationInfo>>& _Pair : Animations)
	{
		AnimationNames.push_back(_Pair.first);
		CAnimationNames.push_back(AnimationNames[CurIndex].c_str());
		CurIndex++;
	}
}




void MonsterGUI::Release()
{
	CurAnimationInfo = nullptr;
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
	CreateActor<Monster_LothricKn>(Enum_UpdateOrder::Monster);
	EditorActor = CreateActor<MonsterEditorActor>(Enum_UpdateOrder::Monster);
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);

	if (nullptr != EditorActor)
	{
		EditorActor->Death();
		EditorActor = nullptr;
	}

	if (nullptr != MonsterWindow)
	{
		MonsterWindow->Release();
		MonsterWindow->Off();
	}
}