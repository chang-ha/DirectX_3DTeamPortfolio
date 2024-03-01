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

	////1น่
	//{
	//	FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("o000200.FBX", "FBXAnimationTexture");
	//	//FBXRenderer->Transform.SetLocalScale({ 10, 10 , 10 });
	//	FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
	//}


	//{
	//	FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("o000200.FBX", "FBXAnimationTexture");
	//	//FBXRenderer->Transform.SetLocalScale({ 10, 10 , 10 });
	//	FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
	//	FBXRenderer->Transform.AddLocalPosition({ 0, 0 , 2 });

	//}

	//10น่SS
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetFBXMesh("o309400.FBX", "FBXAnimationTexture");
		FBXRenderer->Transform.SetLocalScale({ 100, 100 , 100 });
		FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
	}

	
	/*{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
		FBXRenderer->SetFBXMesh("o000371.FBX", "FBXAnimationTexture");
		FBXRenderer->Transform.SetLocalScale({ 10, 10 , 10 });
		FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
		FBXRenderer->Transform.AddLocalPosition({ 0, 0 , 10 });
	}*/

	////100น่
	//{
	//	FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("o000200.FBX", "FBXAnimationTexture");
	//	FBXRenderer->Transform.SetLocalScale({ 100, 100 , 100 });
	//	FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
	//}

	//{
	//	FBXRenderer = CreateComponent<GameContentsFBXRenderer>();
	//	FBXRenderer->SetFBXMesh("o000200.FBX", "FBXAnimationTexture");
	//	FBXRenderer->Transform.SetLocalScale({ 100, 100 , 100 });
	//	FBXRenderer->Transform.AddLocalRotation({ 0, 180 , 0 });
	//	FBXRenderer->Transform.AddLocalPosition({ 0, 0 , 100 });
	//}
}

void TestMapObjcet::Update(float _Delta)
{

	//float4 Pos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

}