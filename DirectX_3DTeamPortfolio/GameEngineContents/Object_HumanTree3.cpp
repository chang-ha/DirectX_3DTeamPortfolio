#include "PreCompile.h"
#include "Object_HumanTree3.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree3::Object_HumanTree3()
{	
}

Object_HumanTree3::~Object_HumanTree3()
{
}

void Object_HumanTree3::Start()
{
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o302582.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();
}

void Object_HumanTree3::Update(float _Delta)
{

}
