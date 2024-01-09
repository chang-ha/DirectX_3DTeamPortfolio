#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineCoreWindow.h>
#include "ContentsControlWindow.h"
#include "PlayLevel.h"
#include "ContentResources.h"
#include "PlayLevel.h"
#include "TestLevel_Boss.h"
#include "TestLevel_Monster.h"
#include "TestLevel_Shader.h"
#include "TestLevel_Map.h"

#include <GameEngineCore\GameEnginePhysX.h>

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

	CoreGUIWindow = GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	CoreGUIWindow->On();


	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TestLevel_Boss>("TestLevel_Boss");
	GameEngineCore::CreateLevel<TestLevel_Monster>("TestLevel_Monster");
	GameEngineCore::CreateLevel<TestLevel_Shader>("TestLevel_Shader");
	GameEngineCore::CreateLevel<TestLevel_Map>("TestLevel_Map");

	GameEngineCore::ChangeLevel("TestLevel_Map");
}

void ContentsCore::Update(float _Delta)
{
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