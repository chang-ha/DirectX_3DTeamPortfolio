#include "PreCompile.h"
#include "Object_CandleHuman2.h"
#include "GameContentsFBXRenderer.h"
#include "ContentsFireRenderer.h"
#include "ContentsLight.h"


Object_CandleHuman2::Object_CandleHuman2()
{	
}

Object_CandleHuman2::~Object_CandleHuman2()
{
}

void Object_CandleHuman2::Start()
{
	{
		FBXRenderer = CreateComponent<GameContentsFBXRenderer>(0);
		FBXRenderer->SetFBXMesh("o302566.FBX", "FBX_Static");
		FBXRenderer->Transform.SetWorldScale({ 100,100,100 });
		FBXRenderer->SetStatic();
	}
}

void Object_CandleHuman2::Update(float _Delta)
{

}
