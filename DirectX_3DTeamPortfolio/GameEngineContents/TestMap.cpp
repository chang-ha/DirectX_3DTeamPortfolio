#include "PreCompile.h"
#include "TestMap.h"
#include "ContentsEnum.h"
#include "GameContentsFBXRenderer.h"

TestMap::TestMap() 
{	
}

TestMap::~TestMap() 
{
}

void TestMap::Start()
{
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetMapFBXMesh("WorldMap.FBX", "FBX_Static");

		//MapMesh = FBXRenderer->GetFBXMesh("WorldMap.FBX0");

		//MapDatas = MapMesh->GetMapDatas();
	}

	//Transdate.resize(MapDatas.size());

	//for (size_t i = 0; i < MapDatas.size(); i++)
	//{
	//	Transdate[i].SetLocalScale(MapDatas[i].Scale);
	//	Transdate[i].SetLocalPosition(MapDatas[i].Center);
	//	Transdate[i].SetLocalRotation(float4::ZERO);
	//}


}

void TestMap::Update(float _Delta)
{
	// ���ҷε� ����
	/*for (size_t i = 0; i < MapDatas.size(); i++)
	{
		if (true == MapDatas[i].IsLoad)
		{
			continue;
		}

		if (GetLevel()->GetMainCamera()->InCamera(Transdate[i]))
		{
			MapMesh->BigFBXLoad(i, MapDatas[i].Name);
			FBXRenderer->SetBigFBXMesh("WorldMap.FBX0", "FBX_Static", static_cast<int>(i), 0);
			MapDatas[i].IsLoad = true;
		}
	}*/

}