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
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o301336.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();
	//Transform.SetWorldPosition({ -6950, -860 , 14530 });
	//Transform.SetWorldScale({ 100, 100 , 100 });
	//Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_Skeleton::Update(float _Delta)
{

}
