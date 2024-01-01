#include "PreCompile.h"
#include "TestMap.h"
#include "ContentsEnum.h"
// #include "GameEngineCore/GameEngineFBXRenderer.h"

TestMap::TestMap() 
{	
}

TestMap::~TestMap() 
{
}

void TestMap::Start()
{
	{
		FBXRenderer = CreateComponent<GameEngineFBXRenderer>();
		FBXRenderer->TestSetFBXMesh("WorldMap.FBX", "FBX_Static");
	}
}

void TestMap::Update(float _Delta)
{

}