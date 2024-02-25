#include "PreCompile.h"
#include "Object_Desk.h"
#include "GameContentsFBXRenderer.h"


Object_Desk::Object_Desk()
{	
}

Object_Desk::~Object_Desk()
{
}

void Object_Desk::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o101010.FBX", "FBX_Static");
		/*FBXRenderer->Transform.SetWorldScale({ 125, 125 , 125 });
		FBXRenderer->Transform.AddWorldRotation({ 0, -25 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -800, -2500 , 2400 });*/
	}

	Transform.SetWorldPosition({ -9011, 2030 , -3678 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 110 , 0 });

}

void Object_Desk::Update(float _Delta)
{

}
