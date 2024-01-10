#include "PreCompile.h"
#include "TestObject.h"


TestObject::TestObject()
{

}

TestObject::~TestObject()
{

}

void TestObject::LevelStart(GameEngineLevel* _PrevLevel)
{
	//if (nullptr == GameEngineFBXMesh::Find("WorldMap.fbx"))
	//{
	//	GameEngineFile File;
	//	File.MoveParentToExistsChild("ContentsResources");
	//	File.MoveChild("ContentsResources\\Mesh\\MapResource\\WorldMap.fbx");
	//	GameEngineFBXMesh::Load(File.GetStringPath());
	//}

	FBXRenderer->SetFBXMesh("SmallMap.fbx", "FBXStaticColor");
	TriMesh->Transform.SetLocalPosition({0.f, -1000.f, 0.f});
	TriMesh->PhysXComponentInit("SmallMap.fbx");
}

void TestObject::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void TestObject::Start()
{
	if (nullptr == FBXRenderer)
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	}

	if (nullptr == TriMesh)
	{
		TriMesh = CreateComponent<GameEnginePhysXTriMesh>();	
	}
}

void TestObject::Update(float _Delta)
{
	
}

void TestObject::Release()
{
	if (nullptr != FBXRenderer)
	{
		FBXRenderer->Death();
		FBXRenderer = nullptr;
	}

	if (nullptr != TriMesh)
	{
		TriMesh->Death();
		TriMesh = nullptr;
	}
}