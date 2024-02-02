#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEnginePhysX.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "ContentsControlWindow.h"
#include "TreeWindow.h"

#include "ContentsMouseInput.h"

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "ContentResources.h"
#include "PlayLevel.h"
#include "TestLevel_Boss.h"
#include "TestLevel_Monster.h"
#include "TestLevel_Shader.h"
#include "TestLevel_Map.h"
#include "TestLevel_PhysX.h"

ContentsCore::ContentsCore() 
{
	GameEngineInput::AddInputObject(this);
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	ContentResources::ContentResourcesInit();
	GameEnginePhysX::PhysXInit();

	ContentsGUIWindow = GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	ContentsGUIWindow->On(); 

	TreeGUIWindow = GameEngineGUI::CreateGUIWindow<TreeWindow>("TreeWindow");
	TreeGUIWindow->On();

	CoreGUIWindow = GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	CoreGUIWindow->On();

	ContentsMouseInput::Reset();

	GameEngineFont::Load("OptimusBold");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<TestLevel_Boss>("TestLevel_Boss");
	GameEngineCore::CreateLevel<TestLevel_Monster>("TestLevel_Monster");
	GameEngineCore::CreateLevel<TestLevel_Shader>("TestLevel_Shader"); 
	GameEngineCore::CreateLevel<TestLevel_Map>("TestLevel_Map");
	GameEngineCore::CreateLevel<TestLevel_PhysX>("TestLevel_PhysX");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::ChangeLevel("TestLevel_Map");
}

void ContentsCore::Update(float _Delta)
{
	ContentsMouseInput::InputUpdate();

	if (nullptr != CoreGUIWindow && true == GameEngineInput::IsDown(VK_F7, this))
	{
		CoreGUIWindow->OnOffSwitch();
	}

	if (nullptr != ContentsGUIWindow && true == GameEngineInput::IsDown(VK_F8, this))
	{
		ContentsGUIWindow->OnOffSwitch();
	}
}

void ContentsCore::Release()
{
}