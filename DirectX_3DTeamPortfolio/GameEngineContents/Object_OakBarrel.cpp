#include "PreCompile.h"
#include "Object_OakBarrel.h"
#include "GameContentsFBXRenderer.h"


Object_OakBarrel::Object_OakBarrel()
{	
}

Object_OakBarrel::~Object_OakBarrel()
{
}

void Object_OakBarrel::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o001090.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		
	}

	Box = CreateComponent<GameEnginePhysXBox>();
	Box->PhysXComponentInit(50, 50, 50);
	Transform.SetWorldScale({ 100, 100 , 100 });
	

	
}

void Object_OakBarrel::Update(float _Delta)
{

}
