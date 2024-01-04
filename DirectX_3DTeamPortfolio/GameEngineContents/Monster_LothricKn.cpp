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
	CommonMonster::Start();

	MainRenderer->SetFBXMesh("c1280.fbx", "FBXAnimationTexture");

	MainRenderer->CreateFBXAnimation("DH_Aiming", "c1280_DH_Aiming.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Idle_RH_Guarding", "c1280_Idle_RH_Guarding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Idle_Sit", "c1280_Idle_Sit.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Idle_Standing", "c1280_Idle_Standing.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Idle_Standing2", "c1280_Idle_Standing2.fbx", { 0.05f , true });
	MainRenderer->ChangeAnimation("DH_Aiming");
}

void Monster_LothricKn::Update(float _Delta)
{
}


void Monster_LothricKn::Release()
{
	CommonMonster::Release();
}

void Monster_LothricKn::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}