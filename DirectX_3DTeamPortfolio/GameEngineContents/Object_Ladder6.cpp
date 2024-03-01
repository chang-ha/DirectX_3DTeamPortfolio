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

	Transform.SetWorldPosition({ -9666, 984 , 4594 });
	Transform.SetWorldScale({ 100, 100 , 100 });
	Transform.SetWorldRotation({ 0, 150 , 0 });

	CollisionTop = CreateComponent<GameEngineCollision>();
	CollisionBottom = CreateComponent<GameEngineCollision>();


}

void Object_Ladder6::Update(float _Delta)
{

}
