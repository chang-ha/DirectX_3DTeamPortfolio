#include "PreCompile.h"
#include "Object_Ladder4.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder4::Object_Ladder4()
{	
}

Object_Ladder4::~Object_Ladder4()
{
}

void Object_Ladder4::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300713.FBX", "FBX_Static");
		
	}

	Transform.SetWorldPosition({ -8033, -564 , 3313 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();

}

void Object_Ladder4::Update(float _Delta)
{

}
