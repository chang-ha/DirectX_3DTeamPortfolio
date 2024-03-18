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

	

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(1.3f, 1.3f, 1.3f));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 14.8f, -0.33f });
	CollisionTop->Transform.SetWorldScale(float4(3, 3, 3));

	CollisionBody = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LabberMiddle);
	CollisionBody->SetCollisionType(ColType::AABBBOX3D);
	//CollisionBody->Transform.SetLocalPosition({ 0.0f, 7.2f, 0 });
	CollisionBody->Transform.SetLocalPosition({ 0.0f, 6.8f, 0 });
	CollisionBody->Transform.SetLocalScale(float4(1.0f, 14.5, 1));

	Transform.SetWorldPosition({ -8033, -564 , 3313 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 180 , 0 });
}

void Object_Ladder2::Update(float _Delta)
{

}

//float4 Object_Ladder2::GetRotation()
//{
//	float4 Result;
//	Transform.GetWorldRotationEuler();
//
//	return Result;
//}
