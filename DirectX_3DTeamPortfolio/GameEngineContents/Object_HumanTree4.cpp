#include "PreCompile.h"
#include "Object_HumanTree4.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree4::Object_HumanTree4()
{	
}

Object_HumanTree4::~Object_HumanTree4()
{
}

void Object_HumanTree4::Start()
{
	
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o302583.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	
}

void Object_HumanTree4::Update(float _Delta)
{

}
