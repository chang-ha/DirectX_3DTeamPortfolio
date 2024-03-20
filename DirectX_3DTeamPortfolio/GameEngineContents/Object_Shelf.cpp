#include "PreCompile.h"
#include "Object_Shelf.h"
#include "GameContentsFBXRenderer.h"


Object_Shelf::Object_Shelf()
{	
}

Object_Shelf::~Object_Shelf()
{
}

void Object_Shelf::Start()
{

	//11

	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o302514.FBX", "FBX_Static");
		FBXRenderer->SetStatic();
		
	}

	Box = CreateComponent<GameEnginePhysXBox>();
	Box->PhysXComponentInit(80, 100, 300);
	Transform.SetWorldScale({ 100, 100 , 100 });
	

	
}

void Object_Shelf::Update(float _Delta)
{

}
