#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "ContentResources.h"
#include "PlayLevel.h"
#include "TestLevel_Boss.h"
#include "TestLevel_Monster.h"

ContentsCore::ContentsCore() 
{
}

ContentsCore::~ContentsCore() 
{
}

void ContentsCore::Start()
{
	ContentResources::ContentResourcesInit();

	GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TestLevel_Boss>("TestLevel_Boss");
	GameEngineCore::CreateLevel<TestLevel_Monster>("TestLevel_Monster");

	GameEngineCore::ChangeLevel("TestLevel_Monster");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}