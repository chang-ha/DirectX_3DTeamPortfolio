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
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o301337.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();

	//Transform.SetWorldPosition({ -6950, -860 , 14530 });
	//Transform.SetWorldScale({ 100, 100 , 100 });
	//Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_Skeleton1::Update(float _Delta)
{

}
