#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineCoreWindow.h>

#include "PlayLevel.h"
#include "ContentResources.h"

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

	GameEngineCore::ChangeLevel("PlayLevel");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}