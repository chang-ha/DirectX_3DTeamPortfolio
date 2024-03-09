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

	Transform.SetWorldPosition({ -13574, 2124, 3254 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 60 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0, 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 4.25f, 0.5f });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));

}

void Object_Ladder4::Update(float _Delta)
{

}
