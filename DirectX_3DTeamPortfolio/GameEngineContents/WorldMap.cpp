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


	//// Sound
	{
		GameEngineDirectory Dir;
		Dir.SetCurrentPath();
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound\\m30");
		std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

		for (int i = 0; i < AllFile.size(); i++)
		{
			GameEngineSound::Sound3DLoad(AllFile[i].GetStringPath());
			GameEngineSound::SoundLoad(AllFile[i].GetStringPath());
		}
	}

	{
		physx::PxFilterData FilterData;

		FilterData.word0 = static_cast<int>(Enum_CollisionOrder::Map);
		FilterData.word0 = static_cast<int>(Enum_CollisionOrder::Player);
		FilterData.word0 = static_cast<int>(Enum_CollisionOrder::Camera);		
		FilterData.word0 = static_cast<int>(Enum_CollisionOrder::Big_Camera);
		


		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetMapFBXMesh("World1.FBX", "FBX_Static");
		FBXRenderer->RenderBaseInfoValue.Roughness = 0.0f;
		FBXRenderer->SetStatic();

		TriMesh = CreateComponent<GameEnginePhysXTriMesh>();
		TriMesh->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
		TriMesh->PhysXComponentInit("World1.FBX0", &FilterData);

		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer2->SetMapFBXMesh("World2.FBX", "FBX_Static");
		FBXRenderer2->RenderBaseInfoValue.Roughness = 0.0f;
		FBXRenderer2->SetStatic();

		TriMesh2 = CreateComponent<GameEnginePhysXTriMesh>();
		TriMesh2->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.0f });
		TriMesh2->PhysXComponentInit("World2.FBX0" , &FilterData);

		SkyRenderer = CreateComponent<GameContentsFBXRenderer>(-1);
		SkyRenderer->SetFBXMesh("WorldSky.FBX", "FBX_Static_Alpha", RenderPath::Alpha);
		//SkyRenderer->RenderBaseInfoValue.TEXCOORDMult = 1.0f;

		BackGroundRenderer = CreateComponent<GameContentsFBXRenderer>();
		BackGroundRenderer->SetMapFBXMesh("BackGround.FBX", "FBX_Static");
		BackGroundRenderer->RenderBaseInfoValue.Roughness = 0.0f;
		BackGroundRenderer->SetStatic();
		//MapMesh = FBXRenderer->GetFBXMesh("WorldMap.FBX0");

		//MapDatas = MapMesh->GetMapDatas();
	}

	//// BGM
	//MapBGM = GameEngineSound::SoundPlay("fdp_m30#148 (s960099990).wav", 100);

	//{
	//	// WindSound 0备开
	//	SetSoundCol(float4{ -6715.0f, 4840.0f, 572.0f }, float4{ 50.0f,4000.0f });
	//	WindSound0 = GameEngineSound::Sound3DPlay("fdp_m30#145 (s300220000).wav", SoundCol->Transform.GetWorldPosition(), 1.0f, 100, 50.0f, 4000.0f);
	//}

	//{
	//	// WindSound 1备开
	//	SetSoundCol(float4{ -11643.0f, 5000.0f, 505.0f }, float4{ 50.0f,4000.0f });
	//	WindSound1 = GameEngineSound::Sound3DPlay("fdp_m30#146 (s300220000b).wav", SoundCol->Transform.GetWorldPosition(), 1.0f, 100, 50.0f, 4000.0f);
	//}

	//{
	//	// WindSound 2备开
	//	SetSoundCol(float4{ -8460.0f, 500.0f, 1639.0f }, float4{ 50.0f,2000.0f });
	//	WindSound2 = GameEngineSound::Sound3DPlay("fdp_m30#146 (s300220000b).wav", SoundCol->Transform.GetWorldPosition(), 1.0f, 100, 50.0f, 2000.0f);
	//}

	//{
	//	// WindSound 3备开
	//	SetSoundCol(float4{ -7272.0f, 3610.0f, 8713.0f }, float4{ 50.0f,4000.0f });
	//	WindSound3 = GameEngineSound::Sound3DPlay("fdp_m30#145 (s300220000).wav", SoundCol->Transform.GetWorldPosition(), 1.0f, 100, 50.0f, 4000.0f);
	//}
	
	//GameEngineSound::Sound3DPlay("1-06 Vordt Of The Boreal Valley.mp3", float4::ZERO, 1.0f, 10);



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

	//// 盒且肺靛 焊幅
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

void WorldMap::SetSoundCol(const float4& _Pos, const float4& _Scale)
{
	SoundCol = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Sound);
	SoundCol->Transform.SetWorldPosition(_Pos);
	SoundCol->Transform.SetLocalScale(_Scale);
}

void WorldMap::LevelEnd(class GameEngineLevel* _NextLevel)
{
	MapBGM.Stop();
	WindSound0.Stop();
	WindSound1.Stop();
	WindSound2.Stop();
	WindSound3.Stop();
}
