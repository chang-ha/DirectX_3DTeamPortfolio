#include "PreCompile.h"
#include "Object_Torchlight.h"
#include "GameContentsFBXRenderer.h"


Object_Torchlight::Object_Torchlight()
{	
}

Object_Torchlight ::~Object_Torchlight()
{
}

void Object_Torchlight::Start()
{
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o004660.FBX", "FBX_Static");
		//FBXRenderer->Transform.SetWorldPosition({ -3925, 4120 , -1961 });
		FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
		//FBXRenderer->Transform.SetWorldRotation({ 0, 0 , 0 });
	}
}

void Object_Torchlight::Update(float _Delta)
{

}
