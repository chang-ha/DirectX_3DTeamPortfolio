#include "PreCompile.h"
#include "WorldMap.h"
#include "ContentsEnum.h"
#include "GameContentsFBXRenderer.h"

WorldMap::WorldMap() 
{	
}

WorldMap::~WorldMap() 
{
}

void WorldMap::Start()
{
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetMapFBXMesh("World1.FBX", "FBX_Static");

		TriMesh = CreateComponent<GameEnginePhysXTriMesh>();
		TriMesh->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
		TriMesh->PhysXComponentInit("World1.FBX0");

		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer2->SetMapFBXMesh("World2.FBX", "FBX_Static");

		TriMesh2 = CreateComponent<GameEnginePhysXTriMesh>();
		TriMesh2->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
		TriMesh2->PhysXComponentInit("World2.FBX0");

		SkyRenderer = CreateComponent<GameContentsFBXRenderer>();
		SkyRenderer->SetFBXMesh("WorldSky.FBX", "FBX_Static_Alpha", RenderPath::Alpha);
		//SkyRenderer->RenderBaseInfoValue.TEXCOORDMult = 1.0f;

		BackGroundRenderer = CreateComponent<GameContentsFBXRenderer>();
		BackGroundRenderer->SetMapFBXMesh("BackGround.FBX", "FBX_Static");

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

void WorldMap::Update(float _Delta)
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