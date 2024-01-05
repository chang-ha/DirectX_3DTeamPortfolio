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
		FBXRenderer->TestSetBigFBXMesh("WorldMap.FBX", "FBX_Static");

		MapMesh = FBXRenderer->GetFBXMesh("WorldMap.FBX0");

		MapDatas = MapMesh->GetMapDatas();
	}
}

void TestMap::Update(float _Delta)
{
	for (size_t i = 0; i < MapDatas.size(); i++)
	{
		if (true == MapDatas[i].IsLoad)
		{
			continue;
		}

		if (GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z <= MapDatas[i].Pos.Z)
		{
			MapMesh->BigFBXLoad(i, MapDatas[i].Name);
			FBXRenderer->SetBigFBXMesh("WorldMap.FBX0", "FBX_Static", i, 0);
			MapDatas[i].IsLoad = true;
		}
	}

}