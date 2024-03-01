#include "PreCompile.h"
#include "Object_Ladder2.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder2::Object_Ladder2()
{	
}

Object_Ladder2::~Object_Ladder2()
{
}

void Object_Ladder2::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300711.FBX", "FBX_Static");
		
	}

	Transform.SetWorldPosition({ -8033, -564 , 3313 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();

}

void Object_Ladder2::Update(float _Delta)
{

}
