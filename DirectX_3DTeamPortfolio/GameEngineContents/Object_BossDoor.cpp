#include "PreCompile.h"
#include "Object_BossDoor.h"
#include "GameContentsFBXRenderer.h"


Object_BossDoor::Object_BossDoor()
{	
}

Object_BossDoor::~Object_BossDoor()
{
}

void Object_BossDoor::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300390.FBX", "FBX_Static");
		/*FBXRenderer->Transform.SetWorldScale({ 125, 125 , 125 });
		FBXRenderer->Transform.AddWorldRotation({ 0, -25 , 0 });
		FBXRenderer->Transform.SetWorldPosition({ -800, -2500 , 2400 });*/
	}

	Transform.SetWorldPosition({ -730, -2500 , 2190 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 152 , 0 });

}

void Object_BossDoor::Update(float _Delta)
{

}
