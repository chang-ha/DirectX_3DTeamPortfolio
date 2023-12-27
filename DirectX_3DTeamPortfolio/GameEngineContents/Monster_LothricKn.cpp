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
	BodyRenderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
	BodyRenderer->SetFBXMesh("c1280.fbx", "FBXTexture");
	BodyRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	BodyRenderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));

	BodyRenderer->CreateFBXAnimation("Idle", "c1280_Idle_RH_Guarding.fbx", {0.1f, true});
	BodyRenderer->ChangeAnimation("Idle");
}

void Monster_LothricKn::Update(float _Delta)
{
}


void Monster_LothricKn::Release()
{
	BodyRenderer = nullptr;
}

void Monster_LothricKn::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}