#include "PreCompile.h"
#include "Object_Skeleton1.h"
#include "GameContentsFBXRenderer.h"


Object_Skeleton1::Object_Skeleton1()
{	
}

Object_Skeleton1 ::~Object_Skeleton1()
{
}

void Object_Skeleton1::Start()
{

	

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o301337.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldPosition({ -1037, 4950 , -4634 });
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}

	{
		FBXRenderer1 = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer1->SetFBXMesh("o301337.FBX", "FBX_Static");
		FBXRenderer1->Transform.SetWorldPosition({ -937, 4950 , -4734 });
		FBXRenderer1->Transform.SetWorldScale({ 100, 100 , 100 });
		FBXRenderer1->Transform.SetWorldRotation({ 0, 90 , 0 });
	}

	//Transform.SetWorldPosition({ -6950, -860 , 14530 });
	//Transform.SetWorldScale({ 100, 100 , 100 });
	//Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_Skeleton1::Update(float _Delta)
{

}
