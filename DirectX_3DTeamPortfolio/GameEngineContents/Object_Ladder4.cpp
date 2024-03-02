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

	Transform.SetWorldPosition({ -13624, 2124, 3254 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 60 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetWorldPosition({ -13624, 2124, 3254 });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetWorldPosition({ -13624, 2550, 3254 });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));

}

void Object_Ladder4::Update(float _Delta)
{

}
