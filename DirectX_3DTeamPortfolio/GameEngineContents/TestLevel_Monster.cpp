#include "PreCompile.h"
#include "TestLevel_Monster.h"
#include <GameEngineCore/GameEngineGUI.h>

#include "Monster_LothricKn.h"
#include "MonsterEditorActor.h"


// _Level == TestLevel_Monster
void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == _Level)
	{
		return;
	}

	if (bool MonsterCountTestCode = true)
	{
		std::vector<std::shared_ptr<Monster_LothricKn>> Monsters = _Level->GetObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);
		if (true == Monsters.empty())
		{
			return;
		}

		int MonsterCount = static_cast<int>(Monsters.size());
		ImGui::Text(std::string("ObjectCount : " + std::to_string(MonsterCount)).c_str());
	}

	TestLevel_Monster* TestLevel = static_cast<TestLevel_Monster*>(_Level);
	if (nullptr == TestLevel)
	{
		return;
	}


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

	// EditorActor = CreateActor<MonsterEditorActor>(Enum_UpdateOrder::Monster);
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
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster);

	if (nullptr != MonsterWindow)
	{
		MonsterWindow->Off();
	}
}