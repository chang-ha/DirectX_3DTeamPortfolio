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

	EventLoad();

	MainRenderer->SetFBXMesh("c1280.fbx", "FBXAnimationTexture");

	MainRenderer->CreateFBXAnimation("DH_Aiming", "c1280_DH_Aiming.fbx");
	MainRenderer->CreateFBXAnimation("Idle_RH_Guarding", "c1280_Idle_RH_Guarding.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Sit", "c1280_Idle_Sit.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Standing", "c1280_Idle_Standing.fbx");
	MainRenderer->CreateFBXAnimation("RH_UnGaurding", "c1280_RH_UnGaurding.fbx");
	MainRenderer->CreateFBXAnimation("Hit_weakly", "c1280_Hit_weakly.fbx");
	MainRenderer->CreateFBXAnimation("Turn_Right", "c1280_Turn_Right.fbx");
	MainRenderer->CreateFBXAnimation("Turn_Left", "c1280_Turn_Left.fbx");
	MainRenderer->CreateFBXAnimation("Turn_Right_Twice", "c1280_Turn_Right_Twice.fbx");
	MainRenderer->CreateFBXAnimation("Hit_Mid", "c1280_Hit_Mid.fbx");
	MainRenderer->CreateFBXAnimation("RH_SmashStrike", "c1280_RH_SmashStrike.fbx");
	MainRenderer->CreateFBXAnimation("RH_Strike", "c1280_RH_Strike.fbx");
	MainRenderer->CreateFBXAnimation("RH_Shield_Bash", "c1280_RH_Shield_Bash.fbx");
	MainRenderer->CreateFBXAnimation("RH_Forward_Stab", "c1280_RH_Forward_Stab.fbx");
	MainRenderer->CreateFBXAnimation("RH_RVSwing", "c1280_RH_RVSwing.fbx");
	MainRenderer->CreateFBXAnimation("RH_Swing", "c1280_RH_Swing.fbx");
	MainRenderer->CreateFBXAnimation("Scout", "c1280_Scout.fbx");
	MainRenderer->CreateFBXAnimation("Run_Forward_Gaurding", "c1280_Run_Forward_Gaurding.fbx");
	MainRenderer->CreateFBXAnimation("Run_Forward", "c1280_Run_Forward.fbx");
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove_DH_Aiming", "c1280_Walk_RightSideMove_DH_Aiming.fbx");
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove_DH_Aiming", "c1280_Walk_LeftSideMove_DH_Aiming.fbx");
	MainRenderer->CreateFBXAnimation("Walk_Backward_DH_Aiming", "c1280_Walk_Backward_DH_Aiming.fbx");
	MainRenderer->CreateFBXAnimation("Walk_Forward_DH_Aiming", "c1280_Walk_Forward_DH_Aiming.fbx");
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove_Gaurding", "c1280_Walk_RightSideMove_Gaurding.fbx");
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove_Gaurding", "c1280_Walk_LeftSideMove_Gaurding.fbx");
	MainRenderer->CreateFBXAnimation("Walk_Backward_Gaurding", "c1280_Walk_Backward_Gaurding.fbx");
	MainRenderer->CreateFBXAnimation("Walk_Forward_Gaurding", "c1280_Walk_Forward_Gaurding.fbx");
	MainRenderer->CreateFBXAnimation("Walk_RightSideMove", "c1280_Walk_RightSideMove.fbx");
	MainRenderer->CreateFBXAnimation("Walk_LeftSideMove", "c1280_Walk_LeftSideMove.fbx");
	MainRenderer->CreateFBXAnimation("Walk_Backword", "c1280_Walk_Backword.fbx");
	MainRenderer->CreateFBXAnimation("Sit_Rising", "c1280_Sit_Rising.fbx");
	MainRenderer->CreateFBXAnimation("UnAim", "c1280_UnAim.fbx");
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