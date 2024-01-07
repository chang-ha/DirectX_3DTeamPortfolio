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

	Transdate.resize(MapDatas.size());

	for (size_t i = 0; i < MapDatas.size(); i++)
	{
		Transdate[i].SetLocalPosition(MapDatas[i].Center);
		Transdate[i].SetLocalScale(MapDatas[i].Scale);
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

		if (GetLevel()->GetMainCamera()->InCamera(Transdate[i]))
		{
			MapMesh->BigFBXLoad(i, MapDatas[i].Name);
			FBXRenderer->SetBigFBXMesh("WorldMap.FBX0", "FBX_Static", i, 0);
			MapDatas[i].IsLoad = true;
		}
	}

}