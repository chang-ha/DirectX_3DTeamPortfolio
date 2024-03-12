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
		FBXRenderer->SetStatic();
		
	}

	Transform.SetWorldPosition({ -16410, 2440 , -3480 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 4.9f , 0.5f });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));
}

void Object_Ladder3::Update(float _Delta)
{

}
