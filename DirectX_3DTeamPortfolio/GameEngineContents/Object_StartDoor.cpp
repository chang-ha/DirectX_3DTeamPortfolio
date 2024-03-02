#include "PreCompile.h"
#include "Object_StartDoor.h"
#include "GameContentsFBXRenderer.h"


Object_StartDoor::Object_StartDoor()
{	
}

Object_StartDoor ::~Object_StartDoor()
{
}

void Object_StartDoor::Start()
{

	

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300370.FBX", "FBX_Static");
		/*FBXRenderer->Transform.SetWorldScale({ 125, 125 , 125 });
		FBXRenderer->Transform.AddWorldRotation({ 0, -25 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -800, -2500 , 2400 });*/
	}

	Transform.SetWorldPosition({ -6950, -860 , 14530 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_StartDoor::Update(float _Delta)
{

}
