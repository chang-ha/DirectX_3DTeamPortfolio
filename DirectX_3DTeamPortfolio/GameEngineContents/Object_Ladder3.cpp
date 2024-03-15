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



	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(1.3f, 1.3f, 1.3f));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 4.9f , -0.33f });
	CollisionTop->Transform.SetWorldScale(float4(3, 3, 3));

	CollisionBody = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LabberMiddle);
	CollisionBody->SetCollisionType(ColType::AABBBOX3D);
	CollisionBody->Transform.SetLocalPosition({ 0.0f, 2.0f, 0 });
	CollisionBody->Transform.SetLocalScale(float4(1.0f, 4.5f, 1));

	Transform.SetWorldPosition({ -16410, 2440 , -3480 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });
}

void Object_Ladder3::Update(float _Delta)
{

}
