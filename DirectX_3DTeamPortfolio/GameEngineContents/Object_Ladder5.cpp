#include "PreCompile.h"
#include "Object_Ladder5.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder5::Object_Ladder5()
{	
}

Object_Ladder5::~Object_Ladder5()
{
}

void Object_Ladder5::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300714.FBX", "FBX_Static");
		
	}

	Transform.SetWorldPosition({ -8033, -564 , 3313 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();

}

void Object_Ladder5::Update(float _Delta)
{

}
