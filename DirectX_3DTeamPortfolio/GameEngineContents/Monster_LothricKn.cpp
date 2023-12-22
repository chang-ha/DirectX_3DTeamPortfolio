#include "PreCompile.h"
#include "Monster_LothricKn.h"

Monster_LothricKn::Monster_LothricKn() 
{
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	BodyRenderer = CreateComponent<GameEngineFBXRenderer>();
	BodyRenderer->SetFBXMesh("c1240.fbx", "FBXColor");
	BodyRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
}

void Monster_LothricKn::Release()
{
	BodyRenderer = nullptr;
}

void Monster_LothricKn::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}