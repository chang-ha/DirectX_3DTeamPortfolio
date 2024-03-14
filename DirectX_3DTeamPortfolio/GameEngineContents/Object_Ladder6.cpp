#include "PreCompile.h"
#include "Object_Ladder6.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder6::Object_Ladder6()
{	
}

Object_Ladder6::~Object_Ladder6()
{
}

void Object_Ladder6::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300715.FBX", "FBX_Static");
		FBXRenderer->SetStatic();

	}

	Transform.SetWorldPosition({ -9600, 984 , 4594 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 150 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(2, 2, 2));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0, 6.44f , -0.45f });
	CollisionTop->Transform.SetWorldScale(float4(2, 2, 2));

	CollisionBody = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LabberMiddle);
	CollisionBody->SetCollisionType(ColType::AABBBOX3D);
	CollisionBody->Transform.SetLocalPosition({ 0.0f, 3, 0 });
	CollisionBody->Transform.SetLocalScale(float4(1.0f, 6, 1));


}

void Object_Ladder6::Update(float _Delta)
{

}
