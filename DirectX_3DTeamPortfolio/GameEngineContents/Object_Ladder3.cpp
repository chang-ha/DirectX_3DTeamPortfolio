#include "PreCompile.h"
#include "Object_Ladder3.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder3::Object_Ladder3()
{	
}

Object_Ladder3::~Object_Ladder3()
{
}

void Object_Ladder3::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300712.FBX", "FBX_Static");
		
	}

	Transform.SetWorldPosition({ -16460, 2240 , -3430 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();

}

void Object_Ladder3::Update(float _Delta)
{

}
