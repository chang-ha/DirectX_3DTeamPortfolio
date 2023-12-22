#include "PreCompile.h"
#include "TestLevel_Monster.h"
#include <GameEngineCore/GameEngineGUI.h>

#include "Monster_LothricKn.h"


void MonsterGUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == _Level)
	{
		return;
	}

	if (bool TestCode = false)
	{
		int MonsterCount = static_cast<int>(_Level->GetObjectGroupConvert<Monster_LothricKn>(Enum_UpdateOrder::Monster).size());
		ImGui::Text(std::string("MonsterCount : " + std::to_string(MonsterCount)).c_str());
	}
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
}

void TestLevel_Monster::LevelEnd(GameEngineLevel* _NextLevel)
{
	AllDeathChildObjects<Monster_LothricKn>(Enum_UpdateOrder::Monster);

	if (nullptr != MonsterWindow)
	{
		MonsterWindow->Off();
	}
}