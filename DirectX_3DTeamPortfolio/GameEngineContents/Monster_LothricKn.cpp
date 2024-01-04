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
	MainRenderer->CreateFBXAnimation("RH_UnGaurding", "c1280_RH_UnGaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Hit_weakly", "c1280_Hit_weakly.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Turn_Right", "c1280_Turn_Right.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Turn_Left", "c1280_Turn_Left.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Turn_Right_Twice", "c1280_Turn_Right_Twice.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Hit_Mid", "c1280_Hit_Mid.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_SmashStrike", "c1280_RH_SmashStrike.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_Strike", "c1280_RH_Strike.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_Shield_Bash", "c1280_RH_Shield_Bash.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_Forward_Stab", "c1280_RH_Forward_Stab.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_RVSwing", "c1280_RH_RVSwing.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("RH_Swing", "c1280_RH_Swing.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Scout", "c1280_Scout.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Run_Forward_Gaurding", "c1280_Run_Forward_Gaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Run_Forward", "c1280_Run_Forward.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove_DH_Aiming", "c1280_Walk_RightSideMove_DH_Aiming.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove_DH_Aiming", "c1280_Walk_LeftSideMove_DH_Aiming.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_Backward_DH_Aiming", "c1280_Walk_Backward_DH_Aiming.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_Forward_DH_Aiming", "c1280_Walk_Forward_DH_Aiming.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove_Gaurding", "c1280_Walk_RightSideMove_Gaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove_Gaurding", "c1280_Walk_LeftSideMove_Gaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_Backward_Gaurding", "c1280_Walk_Backward_Gaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_Forward_Gaurding", "c1280_Walk_Forward_Gaurding.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove", "c1280_Walk_RightSideMove.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove", "c1280_Walk_LeftSideMove.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Walk_Backword", "c1280_Walk_Backword.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("Sit_Rising", "c1280_Sit_Rising.fbx", { 0.05f , true });
	MainRenderer->CreateFBXAnimation("UnAim", "c1280_UnAim.fbx", { 0.05f , true });
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