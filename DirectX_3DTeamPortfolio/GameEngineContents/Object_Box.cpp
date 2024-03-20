#include "PreCompile.h"
#include "Object_Box.h"
#include "GameContentsFBXRenderer.h"


Object_Box::Object_Box()
{	
}

Object_Box::~Object_Box()
{
}

void Object_Box::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o001080.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		
	}

	Box = CreateComponent<GameEnginePhysXBox>();
	Box->PhysXComponentInit(50, 50, 50);
	Transform.SetWorldScale({ 100, 100 , 100 });
	

	
}

void Object_Box::Update(float _Delta)
{

}
