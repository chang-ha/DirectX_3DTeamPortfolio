#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "BoneSocketCollision.h"


Monster_LothricKn::Monster_LothricKn() 
{
	SetID(Type);
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	BaseMonster::Start();

	GameEngineInput::AddInputObject(this);

	SetBoneIndex(Enum_BoneType::B_01_RightHand, 78);
	SetBoneIndex(Enum_BoneType::B_01_LeftHand, 47);


	MainRenderer->SetFBXMesh("c1280.fbx", "FBXAnimationTexture");

	MainRenderer->CreateFBXAnimation("Idle_Standing1", "c1280_000000.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Standing2", "c1280_000020.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Gaurding", "c1280_000030.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Aiming", "c1280_000040.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Sitting", "c1280_000700.fbx");
	MainRenderer->CreateFBXAnimation("RH_ShieldUp", "c1280_001100.fbx");
	MainRenderer->CreateFBXAnimation("RH_ShieldDown", "c1280_001101.fbx");
	MainRenderer->CreateFBXAnimation("DH_Aim", "c1280_001200.fbx");
	MainRenderer->CreateFBXAnimation("DH_UnAim", "c1280_001210.fbx");
	MainRenderer->CreateFBXAnimation("DontKnow1", "c1280_001300.fbx");
	MainRenderer->CreateFBXAnimation("Standup", "c1280_001700.fbx");
	MainRenderer->CreateFBXAnimation("Stare_Forward", "c1280_002000.fbx");
	MainRenderer->CreateFBXAnimation("Stare_Backward", "c1280_002001.fbx");
	MainRenderer->CreateFBXAnimation("Stare_LeftSide", "c1280_002002.fbx");
	MainRenderer->CreateFBXAnimation("Stare_RightSide", "c1280_002003.fbx");
	MainRenderer->CreateFBXAnimation("StareGuard_Forward", "c1280_002030.fbx");
	MainRenderer->CreateFBXAnimation("StareGuard_Backward", "c1280_002031.fbx");
	MainRenderer->CreateFBXAnimation("StareGuard_LeftSide", "c1280_002032.fbx");
	MainRenderer->CreateFBXAnimation("StareGuard_RightSide", "c1280_002033.fbx");
	MainRenderer->CreateFBXAnimation("DH_Stare_Forward", "c1280_002040.fbx");
	MainRenderer->CreateFBXAnimation("DH_Stare_Backward", "c1280_002041.fbx");
	MainRenderer->CreateFBXAnimation("DH_Stare_LeftSide", "c1280_002042.fbx");
	MainRenderer->CreateFBXAnimation("DH_Stare_RightSide", "c1280_002043.fbx");
	MainRenderer->CreateFBXAnimation("Run_Chasing", "c1280_002100.fbx");
	MainRenderer->CreateFBXAnimation("RunGuard_Chasing", "c1280_002130.fbx");
	MainRenderer->CreateFBXAnimation("Scout", "c1280_002300.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack11", "c1280_003000.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack12", "c1280_003001.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack13", "c1280_003002.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack21", "c1280_003003.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack22", "c1280_003004.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack23", "c1280_003005.fbx");
	MainRenderer->CreateFBXAnimation("Shield_Attack", "c1280_003006.fbx");
	MainRenderer->CreateFBXAnimation("DH_Fence", "c1280_003007.fbx");
	MainRenderer->CreateFBXAnimation("DH_Strike", "c1280_003008.fbx");
	MainRenderer->CreateFBXAnimation("Hit_Mid", "c1280_003009.fbx");

	CreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_RightHand, "B_01_RightHand");
	CreateFSM();
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);
}


void Monster_LothricKn::Release()
{
	BaseMonster::Release();
}