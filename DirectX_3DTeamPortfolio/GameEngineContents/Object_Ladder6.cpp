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

	}

	Transform.SetWorldPosition({ -9600, 984 , 4594 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 150 , 0 });

	CollisionBottom = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderBot);
	CollisionBottom->SetCollisionType(ColType::SPHERE3D);
	CollisionBottom->Transform.SetWorldPosition({ -9600, 984 , 4594 });
	CollisionBottom->Transform.SetWorldScale(float4(200, 200, 200));

	CollisionTop = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::LadderTop);
	CollisionTop->SetCollisionType(ColType::SPHERE3D);
	CollisionTop->Transform.SetWorldPosition({ -9600, 1630 , 4594 });
	CollisionTop->Transform.SetWorldScale(float4(200, 200, 200));


}

void Object_Ladder6::Update(float _Delta)
{

}
