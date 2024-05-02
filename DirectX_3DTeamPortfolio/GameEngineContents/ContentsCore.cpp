#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEnginePhysX.h>
#include <GameEngineCore/GameEngineCoreWindow.h>
#include "ContentsControlWindow.h"
#include "TreeWindow.h"

#include "TitleLevel.h"
#include "PlayLevel.h"
#include "ContentResources.h"
#include "PlayLevel.h"
#include "Stage_Lothric.h"
#include "LoadingLevel.h"
#include "TestLevel_Boss.h"
#include "TestLevel_Monster.h"
#include "TestLevel_Shader.h"
#include "TestLevel_Map.h"
#include "TestLevel_MapObject.h"
#include "TestLevel_ObjectTest.h"

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

	CoreGUIWindow = GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow");
	CoreGUIWindow->On();

	
		
	TreeGUIWindow = GameEngineGUI::CreateGUIWindow<TreeWindow>("TreeWindow");
	TreeGUIWindow->On();


	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<Stage_Lothric>("Stage_Lothric");
	//GameEngineCore::CreateLevel<TestLevel_Boss>("TestLevel_Boss");
	//GameEngineCore::CreateLevel<TestLevel_Monster>("TestLevel_Monster");
	//GameEngineCore::CreateLevel<TestLevel_Shader>("TestLevel_Shader"); 
	//GameEngineCore::CreateLevel<TestLevel_Map>("TestLevel_Map");
	//GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	//GameEngineCore::CreateLevel<TestLevel_MapObject>("TestLevel_MapObject");
	//GameEngineCore::CreateLevel<TestLevel_ObjectTest>("TestLevel_ObjectTest");
	GameEngineCore::CreateLevel<LoadingLevel>("LoadingLevel");
	
	GameEngineCore::ChangeLevel("Stage_Lothric");
	

	GameEnginePhysX::PushSkipCollisionPair(3, Enum_CollisionOrder::Monster, Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Camera);
	GameEnginePhysX::PushSkipCollisionPair(2, Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Camera);
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
	ContentsGUIWindow = nullptr;
	TreeGUIWindow = nullptr;
	ObjectWindow = nullptr;
	CoreGUIWindow = nullptr;
}