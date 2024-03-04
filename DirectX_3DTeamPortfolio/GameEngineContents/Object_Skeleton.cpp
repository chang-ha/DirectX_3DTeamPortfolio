#include "PreCompile.h"
#include "Object_Skeleton.h"
#include "GameContentsFBXRenderer.h"


Object_Skeleton::Object_Skeleton()
{	
}

Object_Skeleton ::~Object_Skeleton()
{
}

void Object_Skeleton::Start()
{

	

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o301336.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldPosition({ -1337, 4950 , -4634 });
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o301336.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldPosition({ -1187, 4950 , -4534 });
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer2->SetFBXMesh("o301336.FBX", "FBX_Static");
		FBXRenderer2->Transform.SetWorldPosition({ -845, 4950 , -5299 });
		FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer2->Transform.SetWorldRotation({ 0, 90 , 0 });
	}

	{
		FBXRenderer3 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer3->SetFBXMesh("o301336.FBX", "FBX_Static");
		FBXRenderer3->Transform.SetWorldPosition({ -845, 4950 , -5149 });
		FBXRenderer3->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer3->Transform.SetWorldRotation({ 0, 120 , 0 });
	}
	

	//Transform.SetWorldPosition({ -6950, -860 , 14530 });
	//Transform.SetWorldScale({ 100, 100 , 100 });
	//Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_Skeleton::Update(float _Delta)
{

}
