#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "BoneSocketCollision.h"
#include "ContentsMath.h"

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
	MainRenderer->CreateFBXAnimation("Patrol", "c1280_002300.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack11", "c1280_003000.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack12", "c1280_003001.fbx");
	MainRenderer->CreateFBXAnimation("RH_Attack13", "c1280_003002.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_21", "c1280_003003.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_22", "c1280_003004.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_23", "c1280_003005.fbx");
	MainRenderer->CreateFBXAnimation("Shield_Attack", "c1280_003006.fbx");
	MainRenderer->CreateFBXAnimation("DH_Fence", "c1280_003007.fbx");
	MainRenderer->CreateFBXAnimation("DH_Strike", "c1280_003008.fbx");
	MainRenderer->CreateFBXAnimation("Hit_Mid", "c1280_003009.fbx");
	MainRenderer->CreateFBXAnimation("RH_Att_HitDown", "c1280_003010.fbx");
	MainRenderer->CreateFBXAnimation("LH_ShieldAttack", "c1280_003013.fbx");
	MainRenderer->CreateFBXAnimation("RH_Rear_Att", "c1280_003014.fbx");
	MainRenderer->CreateFBXAnimation("L_FastTurn", "c1280_005000.fbx");
	MainRenderer->CreateFBXAnimation("R_FastTurn", "c1280_005001.fbx");
	MainRenderer->CreateFBXAnimation("L_FastTurnTwice", "c1280_005002.fbx");
	MainRenderer->CreateFBXAnimation("R_FastTurnTwice", "c1280_005003.fbx");
	MainRenderer->CreateFBXAnimation("L_Turn", "c1280_005010.fbx");
	MainRenderer->CreateFBXAnimation("R_Turn", "c1280_005011.fbx");
	MainRenderer->CreateFBXAnimation("L_TurnTwice", "c1280_005012.fbx");
	MainRenderer->CreateFBXAnimation("R_TurnTwice", "c1280_005013.fbx");


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
	MainRenderer->SetRootMotion("Patrol");
	MainRenderer->SetRootMotion("RH_Attack11");
	MainRenderer->SetRootMotion("RH_Attack12");
	MainRenderer->SetRootMotion("RH_Attack13");
	MainRenderer->SetRootMotion("Combo_Att_21");
	MainRenderer->SetRootMotion("Combo_Att_22");
	MainRenderer->SetRootMotion("Combo_Att_23");
	MainRenderer->SetRootMotion("Shield_Attack");
	MainRenderer->SetRootMotion("DH_Fence");
	MainRenderer->SetRootMotion("DH_Strike");
	MainRenderer->SetRootMotion("Hit_Mid");
	MainRenderer->SetRootMotion("RH_Att_HitDown");
	MainRenderer->SetRootMotion("LH_ShieldAttack");
	MainRenderer->SetRootMotion("RH_Rear_Att");
	MainRenderer->SetRootMotion("L_FastTurn");
	MainRenderer->SetRootMotion("R_FastTurn");
	MainRenderer->SetRootMotion("L_FastTurnTwice");
	MainRenderer->SetRootMotion("R_FastTurnTwice");
	MainRenderer->SetRootMotion("L_Turn");
	MainRenderer->SetRootMotion("R_Turn");
	MainRenderer->SetRootMotion("L_TurnTwice");
	MainRenderer->SetRootMotion("R_TurnTwice");

	CreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_RightHand, "B_01_RightHand");

	PatrolCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	PatrolCollision->Transform.SetWorldScale(float4(300, 300, 300));
	PatrolCollision->SetCollisionType(ColType::SPHERE3D);
	PatrolCollision->SetCollisionColor(float4::BLUE);

	CreateFSM();
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);

	float Dir = Capsule->GetDir();
}


void Monster_LothricKn::Release()
{
	PatrolCollision = nullptr;
	BaseMonster::Release();
}

void Monster_LothricKn::FindTarget()
{
	if (true == IsTargeting())
	{
		return;
	}

	if (nullptr == PatrolCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 않고 사용하려고 했습니다.");
		return;
	}

	std::shared_ptr<GameEngineActor> pActor;
	
	PatrolCollision->Collision(Enum_CollisionOrder::Dummy, [&pActor](std::vector<GameEngineCollision*>& _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("충돌체를 가지고 있는 액터가 존재하지 않습니다.");
					return;
				}

				pActor = pCol->GetActor()->GetDynamic_Cast_This<GameEngineActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("다이나믹 캐스팅 변환에 실패했습니다.");
					return;
				}
			}
		});

	bool FindValue = (nullptr == pActor);
	if (FindValue)
	{
		PatrolCollision->Off();
		SetTargeting(pActor.get());
		Debug.SetFlag(Enum_MonsterDebugFlag::PatrolValue, false);
	}
};

void Monster_LothricKn::WakeUp() 
{
	MainState.ChangeState(Enum_LothricKn_State::Patrol);
}