#include "PreCompile.h"
#include "Object_Ladder5.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder5::Object_Ladder5()
{	
}

Object_Ladder5::~Object_Ladder5()
{
}

void Object_Ladder5::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300714.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		
	}



	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(1.3f, 1.3f, 1.3f));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 4.86f , -0.45f });
	CollisionTop->Transform.SetWorldScale(float4(2, 2, 2));

	CollisionBody = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LabberMiddle);
	CollisionBody->SetCollisionType(ColType::AABBBOX3D);
	CollisionBody->Transform.SetLocalPosition({ 0.0f, 2.0f, 0 });
	CollisionBody->Transform.SetLocalScale(float4(1.0f, 4, 1));

	Transform.SetWorldPosition({ -17400, 1825 , 2139 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, -100 , 0 });
}

void Object_Ladder5::Update(float _Delta)
{

}

//float4 Object_Ladder5::GetRotation()
//{
//	float4 Result;
//	Transform.GetWorldRotationEuler();
//	return Result;
//}