#include "PreCompile.h"
#include "Object_Ladder1.h"
#include "GameContentsFBXRenderer.h"


Object_Ladder1::Object_Ladder1()
{	
}

Object_Ladder1::~Object_Ladder1()
{
}

void Object_Ladder1::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o300700.FBX", "FBX_Static");
	}

	Transform.SetWorldPosition({ -8930, 2030 , -4427 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, -90 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0 });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0.0f, 8.5f , 0.0f });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));

	
	CollisionFront = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionFront->SetCollisionType(ColType::AABBBOX3D);
	CollisionFront->Transform.SetLocalPosition({ 0.0f, 8.5f , -0.8f });
	CollisionFront->Transform.SetWorldScale(float4(20, 200, 200));


}

void Object_Ladder1::Update(float _Delta)
{

}

void Object_Ladder1::CollisionOn()
{
	CollisionFront->On();
}

void Object_Ladder1::CollisionOff()
{
	CollisionFront->Off();
}