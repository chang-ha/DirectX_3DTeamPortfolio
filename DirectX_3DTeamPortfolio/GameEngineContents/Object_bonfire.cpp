#include "PreCompile.h"
#include "Object_bonfire.h"
#include "GameContentsFBXRenderer.h"


Object_bonfire::Object_bonfire()
{	
}

Object_bonfire ::~Object_bonfire()
{
}

void Object_bonfire::Start()
{

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o000100.FBX", "FBX_Static");
		//FBXRenderer->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		//FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	//{
	//	FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
	//	FBXRenderer1->SetFBXMesh("o000100.FBX", "FBX_Static");
	////	FBXRenderer1->Transform.SetWorldPosition({ -1125, -2489 , 3232 });
	//	FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
	//	//FBXRenderer1->Transform.SetWorldRotation({ 0, 0 , 0 });
	//}
	//{
	//	FBXRenderer2 = CreateComponent<GameContentsFBXRenderer>(0);
	//	FBXRenderer2->SetFBXMesh("o000100.FBX", "FBX_Static");
	//	//FBXRenderer2->Transform.SetWorldPosition({ -16547, 3372 , 2144 });
	//	FBXRenderer2->Transform.SetWorldScale({ 100, 100 , 100 });
	//	//FBXRenderer2->Transform.SetWorldRotation({ 0, 0 , 0 });
	//}
	////Transform.SetWorldPosition({ -6950, -860 , 14530 });
	////Transform.SetWorldScale({ 100, 100 , 100 });
	////Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_bonfire::Update(float _Delta)
{

}
