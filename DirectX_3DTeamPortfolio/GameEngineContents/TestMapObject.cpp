#include "PreCompile.h"
#include "TestMapObjcet.h"
#include "GameContentsFBXRenderer.h"

TestMapObjcet::TestMapObjcet()
{	
}

TestMapObjcet::~TestMapObjcet()
{
}

void TestMapObjcet::Start()
{
	if (nullptr == GameEngineFBXMesh::Find("o000200.fbx"))
	{
		GameEngineFile File;
		File.MoveParentToExistsChild("ContentsResources");
		File.MoveChild("Mesh");
		File.MoveChild("TestMapObject");
		File.MoveChild("MapObj1");
		File.MoveChild("o000200");
		GameEngineFBXMesh::Load(File.GetStringPath());
	}

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetMapFBXMesh("o000200.FBX", "FBXAnimationTexture");
	}

}

void TestMapObjcet::Update(float _Delta)
{

	float4 Pos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

}