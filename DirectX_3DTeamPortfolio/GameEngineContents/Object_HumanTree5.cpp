#include "PreCompile.h"
#include "Object_HumanTree5.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree5::Object_HumanTree5()
{	
}

Object_HumanTree5::~Object_HumanTree5()
{
}

void Object_HumanTree5::Start()
{
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o302583.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();
}

void Object_HumanTree5::Update(float _Delta)
{

}
