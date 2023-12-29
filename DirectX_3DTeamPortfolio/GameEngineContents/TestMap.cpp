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
		FBXRenderer->SetFBXMesh("WorldMap.FBX", "FBXTexture");
	}
}

void TestMap::Update(float _Delta)
{

}