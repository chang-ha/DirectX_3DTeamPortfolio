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
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o301337.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		//FBXRenderer->Transform.AddWorldRotation({ 0, -25 , 0 });
		//FBXRenderer->Transform.SetWorldPosition({ -800, -2500 , 2400 });
	}

	if (nullptr == GameEngineGUI::FindGUIWindow<ObjectTest>("ObjectTest"))
	{
		GameEngineGUI::CreateGUIWindow<ObjectTest>("ObjectTest");
	}

	GUI = GameEngineGUI::FindGUIWindow<ObjectTest>("ObjectTest");
	GUI->Object0 = this;
	GUI->On();

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
	CameraPos1 = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

	//float4 Pos = GetLevel()->GetMainCamera()->Transform.GetWorldPosition();

}
void ObjectTest::Start()
{
	
}

void ObjectTest::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	ImGui::SetNextWindowSize(ImVec2(400, 200));
	ImGui::InputFloat("FPos X", &PositionX);
	ImGui::InputFloat("FPos Y", &PositionY);
	ImGui::InputFloat("FPos Z", &PositionZ);

	
	float4 MainCameraPos = Object0->GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	float4 TPos = Object0->Transform.GetWorldPosition();
	ImGui::Text("Current Position: (%.2f, %.2f, %.2f)", MainCameraPos.X, MainCameraPos.Y, MainCameraPos.Z);
	ImGui::Text("Current Position: (%.2f, %.2f, %.2f)", MainCameraPos.X, MainCameraPos.Y, MainCameraPos.Z);
	ImGui::Text("Current Position: (%.2f, %.2f, %.2f)", TPos.X, TPos.Y, TPos.Z);

	if (ImGui::Button("ChangePos"))
	{
		Object0->Transform.SetWorldPosition({ PositionX , PositionY , PositionZ });

	}

	if (ImGui::Button("ChangeCamaraPos"))
	{
		Object0->GetLevel()->GetMainCamera()->Transform.SetWorldPosition({ PositionX , PositionY , PositionZ });

	}
	if (ImGui::Button("ChangeRot"))
	{
		Object0->Transform.SetWorldRotation({ PositionX , PositionY , PositionZ });
	}

	if (ImGui::Button("UPX"))
	{
		Object0->Transform.AddWorldPosition({ 50 , 0 , 0 });
	}

	if (ImGui::Button("UPY"))
	{
		Object0->Transform.AddWorldPosition({ 0 , 50 , 0 });
	}

	if (ImGui::Button("UPZ"))
	{
		Object0->Transform.AddWorldPosition({ 0 , 0 , 50 });
	}

	if (ImGui::Button("DownX"))
	{
		Object0->Transform.AddWorldPosition({ -50 , 0 , 0 });
	}

	if (ImGui::Button("DownY"))
	{
		Object0->Transform.AddWorldPosition({ 0 , -50 , 0 });
	}

	if (ImGui::Button("DownZ"))
	{
		Object0->Transform.AddWorldPosition({ 0 , 0 , -50 });
	}

	

}