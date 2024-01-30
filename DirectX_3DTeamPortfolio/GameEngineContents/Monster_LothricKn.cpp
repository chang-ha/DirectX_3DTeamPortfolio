#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "BoneSocketCollision.h"


Monster_LothricKn::Monster_LothricKn() 
{
	SetID(Enum_ActorType::LothricKn);
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	BaseMonster::Start();

	GameEngineInput::AddInputObject(this);

	AddBoneIndex(Enum_BoneType::B_01_RightHand, 78);
	AddBoneIndex(Enum_BoneType::B_01_LeftHand, 47);

	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();

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
	MainRenderer->CreateFBXAnimation("RH_SwordDownAttack", "c1280_003010.fbx");
	MainRenderer->CreateFBXAnimation("LH_ShieldAttack", "c1280_003013.fbx");
	MainRenderer->CreateFBXAnimation("RH_CAttack", "c1280_003014.fbx");

	MainRenderer->SetRootMotionComponent(Capsule.get());
	MainRenderer->SetRootMotion("Idle_Standing1");
	MainRenderer->SetRootMotion("Idle_Standing2");
	MainRenderer->SetRootMotion("Idle_Gaurding");
	MainRenderer->SetRootMotion("Idle_Aiming");
	MainRenderer->SetRootMotion("Idle_Sitting");
	MainRenderer->SetRootMotion("RH_ShieldUp");
	MainRenderer->SetRootMotion("RH_ShieldDown");
	MainRenderer->SetRootMotion("DH_Aim");
	MainRenderer->SetRootMotion("DH_UnAim");
	MainRenderer->SetRootMotion("Standup");
	MainRenderer->SetRootMotion("Stare_Forward");
	MainRenderer->SetRootMotion("Stare_Backward");
	MainRenderer->SetRootMotion("Stare_LeftSide");
	MainRenderer->SetRootMotion("Stare_RightSide");
	MainRenderer->SetRootMotion("StareGuard_Forward");
	MainRenderer->SetRootMotion("StareGuard_Backward");
	MainRenderer->SetRootMotion("StareGuard_LeftSide");
	MainRenderer->SetRootMotion("StareGuard_RightSide");
	MainRenderer->SetRootMotion("DH_Stare_Forward");
	MainRenderer->SetRootMotion("DH_Stare_Backward");
	MainRenderer->SetRootMotion("DH_Stare_LeftSide");
	MainRenderer->SetRootMotion("DH_Stare_RightSide");
	MainRenderer->SetRootMotion("Run_Chasing");
	MainRenderer->SetRootMotion("RunGuard_Chasing");
	MainRenderer->SetRootMotion("Scout");
	MainRenderer->SetRootMotion("RH_Attack11");
	MainRenderer->SetRootMotion("RH_Attack12");
	MainRenderer->SetRootMotion("RH_Attack13");
	MainRenderer->SetRootMotion("RH_Attack21");
	MainRenderer->SetRootMotion("RH_Attack22");
	MainRenderer->SetRootMotion("RH_Attack23");
	MainRenderer->SetRootMotion("Shield_Attack");
	MainRenderer->SetRootMotion("DH_Fence");
	MainRenderer->SetRootMotion("DH_Strike");
	MainRenderer->SetRootMotion("Hit_Mid");
	MainRenderer->SetRootMotion("RH_SwordDownAttack");
	MainRenderer->SetRootMotion("LH_ShieldAttack");
	MainRenderer->SetRootMotion("RH_CAttack");

	CreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_RightHand, "B_01_RightHand");

	AggroCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	AggroCollision->Transform.SetWorldScale(float4(500, 500, 500));
	AggroCollision->SetCollisionType(ColType::SPHERE3D);

	CreateFSM();
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);

	float Dir = Capsule->GetDir();

	if (true == wpDummy.expired())
	{
		wpDummy = FindDummyByCollision();
	}
}


void Monster_LothricKn::Release()
{
	BaseMonster::Release();
}

std::shared_ptr<GameEngineActor> Monster_LothricKn::FindDummyByCollision()
{
	if (false == wpDummy.expired())
	{
		return nullptr;
	}

	std::shared_ptr<GameEngineActor> pActor;

	AggroCollision->Collision(Enum_CollisionOrder::Dummy, [&pActor](std::vector<GameEngineCollision*>& _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("충돌체를 가지고 있는 액터가 존재하지 않습니다.");
					return;
				}

				pActor = pCol->GetActor()->GetDynamic_Cast_This<GameEngineActor>();
				break;
			}
		});

	return pActor;
}