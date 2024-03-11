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
	CollisionBottom->Transform.SetLocalPosition({ 0, 0 , 0.5f });
	CollisionBottom->Transform.SetWorldScale(float4(250, 250, 250));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetLocalPosition({ 0.0f, 7.8f , 0.42f });
	CollisionTop->Transform.SetWorldScale(float4(300, 300, 300));

	CollisionBody = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LabberMiddle);
	CollisionBody->SetCollisionType(ColType::AABBBOX3D);
	CollisionBody->Transform.SetLocalPosition({ 0.0f, 4, 0 });
	CollisionBody->Transform.SetLocalScale(float4(0.2f, 7.2f, 1));

	
	/*CollisionFront = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionFront->SetCollisionType(ColType::AABBBOX3D);
	CollisionFront->Transform.SetLocalPosition({ 0.0f, 8.5f , -0.8f });
	CollisionFront->Transform.SetWorldScale(float4(20, 200, 200));*/


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