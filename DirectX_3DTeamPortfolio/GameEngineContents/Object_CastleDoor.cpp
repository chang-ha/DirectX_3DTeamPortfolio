#include "PreCompile.h"
#include "Object_CastleDoor .h"
#include "GameContentsFBXRenderer.h"


Object_CastleDoor::Object_CastleDoor()
{	
}

Object_CastleDoor ::~Object_CastleDoor()
{
}

void Object_CastleDoor::Start()
{

	

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300370.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		/*FBXRenderer->Transform.SetWorldScale({ 125, 125 , 125 });
		FBXRenderer->Transform.AddWorldRotation({ 0, -25 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -800, -2500 , 2400 });*/
	}

	Transform.SetWorldPosition({ -6950, -860 , 14530 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 153 , 0 });

}

void Object_CastleDoor::Update(float _Delta)
{

}
