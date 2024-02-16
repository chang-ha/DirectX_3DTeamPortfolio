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
		FBXRenderer->SetMapFBXMesh("TestGround.FBX", "FBX_Static");

		TriMesh = CreateComponent<GameEnginePhysXTriMesh>();
		TriMesh->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
		TriMesh->PhysXComponentInit("TestGround.FBX0");

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

	//for (size_t i = 3026; i < 3027; i++)
	//{
	//	std::shared_ptr<GameEngineRenderer> NewRenderer = CreateComponent<GameEngineRenderer>();

	//	NewRenderer->SetMesh("Box");
	//	NewRenderer->SetMaterial("FBXStaticColor");
	//	NewRenderer->Transform.SetLocalScale(MapDatas[i].Scale);
	//	NewRenderer->Transform.SetLocalPosition(MapDatas[i].Center);
	//	NewRenderer->RenderBaseInfoValue.BaseColor = float4::RED;

	//}


}

void TestMap::Update(float _Delta)
{

	float4 Pos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	//// 분할로드 보류
	//for (size_t i = 3026; i < 3027/*MapDatas.size()*/; i++)
	//{
	//	if (true == MapDatas[i].IsLoad)
	//	{
	//		continue;
	//	}

	//	if (GetLevel()->GetMainCamera()->InCamera(Transdate[i]))
	//	{
	//		MapMesh->BigFBXLoad(i, MapDatas[i].Name);
	//		FBXRenderer->SetMapFBXMesh("WorldMap.FBX0", "FBX_Static", static_cast<int>(i), 0);
	//		MapDatas[i].IsLoad = true;
	//	}
	//}

}