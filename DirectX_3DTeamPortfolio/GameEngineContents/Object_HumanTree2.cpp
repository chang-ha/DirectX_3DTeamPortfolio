#include "PreCompile.h"
#include "Object_HumanTree2.h"
#include "GameContentsFBXRenderer.h"


Object_HumanTree2::Object_HumanTree2()
{	
}

Object_HumanTree2::~Object_HumanTree2()
{
}

void Object_HumanTree2::Start()
{
	FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
	FBXRenderer->SetFBXMesh("o302581.FBX", "FBX_Static");
	FBXRenderer->Transform.SetWorldScale({ 100, 100 , 100 });
	FBXRenderer->SetStatic();
}

void Object_HumanTree2::Update(float _Delta)
{

}
