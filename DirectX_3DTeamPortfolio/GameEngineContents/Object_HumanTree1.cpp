#include "PreCompile.h"
#include "Object_HumanTree1.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree1::Object_HumanTree1()
{	
}

Object_HumanTree1::~Object_HumanTree1()
{
}

void Object_HumanTree1::Start()
{
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o302580.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();
}

void Object_HumanTree1::Update(float _Delta)
{

}
