#include "PreCompile.h"
#include "Object_Ladder1.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder1::Object_Ladder1()
{	
}

Object_Ladder1::~Object_Ladder1()
{
}

void Object_Ladder1::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300700.FBX", "FBX_Static");
		
	}

	Transform.SetWorldPosition({ -8880, 2030 , -4427 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, -90 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();

}

void Object_Ladder1::Update(float _Delta)
{

}
