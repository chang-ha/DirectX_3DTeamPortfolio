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
		FBXRenderer->SetStatic();
		
	}

	Transform.SetWorldPosition({ -8033, -564 , 3313 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 14.8f, 0.5f });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));

}

void Object_Ladder2::Update(float _Delta)
{

}
