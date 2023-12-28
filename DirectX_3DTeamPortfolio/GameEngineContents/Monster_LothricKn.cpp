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


	BodyRenderer->CreateFBXAnimation("DH_Aiming", "c1280_DH_Aiming.fbx", { 0.05f , true });
	BodyRenderer->CreateFBXAnimation("Idle_RH_Guarding", "c1280_Idle_RH_Guarding.fbx", { 0.05f , true });
	BodyRenderer->CreateFBXAnimation("Idle_Sit", "c1280_Idle_Sit.fbx", { 0.05f , true });
	BodyRenderer->CreateFBXAnimation("Idle_Standing", "c1280_Idle_Standing.fbx", { 0.05f , true });
	BodyRenderer->CreateFBXAnimation("Idle_Standing2", "c1280_Idle_Standing2.fbx", { 0.05f , true });
	BodyRenderer->ChangeAnimation("DH_Aiming");
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