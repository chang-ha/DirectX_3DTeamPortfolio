#include "PreCompile.h"
#include "Object_HumanTree.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree::Object_HumanTree()
{	
}

Object_HumanTree::~Object_HumanTree()
{
}

void Object_HumanTree::Start()
{

	//11
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.AddWorldRotation({ 0, 90 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -4208, 4121 , -2223 });
	}

	{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.SetWorldPosition({ -5862, 3373 , -2474 });
	}
	{
		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer2->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer2->Transform.AddWorldRotation({ 0, -50 , 0 });
		FBXRenderer2->Transform.SetWorldPosition({ -7124, 3400 , -2627 });
	}
	{
		FBXRenderer3 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer3->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer3->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer3->Transform.AddWorldRotation({ 0, -50 , 0 });
		FBXRenderer3->Transform.SetWorldPosition({ -10304, 3630 , -4057 });
	}
	{
		FBXRenderer4 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer4->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer4->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer4->Transform.AddWorldRotation({ 0, -30 , 0 });
		FBXRenderer4->Transform.SetWorldPosition({ -9779, 3625 , -3386 });
	}
	{
		FBXRenderer5 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer5->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer5->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer5->Transform.AddWorldRotation({ 0, -75 , 0 });
		FBXRenderer5->Transform.SetWorldPosition({ -11954, 2880 , -3783 });
	}
	{
		FBXRenderer6 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer6->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer6->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer6->Transform.AddWorldRotation({ 0, 0 , 0 });
		FBXRenderer6->Transform.SetWorldPosition({ -15964, 3383 , 2464 });
	}
	{
		FBXRenderer7 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer7->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer7->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer7->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer7->Transform.SetWorldPosition({ -16253, 3392 , 786 });
	}
	{
		FBXRenderer8 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer8->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer8->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer8->Transform.AddWorldRotation({ 0, 30 , 0 });
		FBXRenderer8->Transform.SetWorldPosition({ -15684, 2685 , -228 });
	}
	{
		FBXRenderer9 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer9->SetFBXMesh("o302580.FBX", "FBX_Static");
		FBXRenderer9->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer9->Transform.AddWorldRotation({ 0, -90 , 0 });
		FBXRenderer9->Transform.SetWorldPosition({ -16702, 2760 , -2225 });
	}
	
	//2




	
}

void Object_HumanTree::Update(float _Delta)
{

}
