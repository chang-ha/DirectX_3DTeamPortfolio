#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "BoneSocketCollision.h"
#include "ContentsMath.h"

Monster_LothricKn::Monster_LothricKn() 
{
	SetID(Enum_ActorType::LothricKn);
	GameEngineInput::AddInputObject(this);
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	BaseMonster::Start();

	// Outer Res
	LoadRes3DSound("c128001001.wav");

	// Actor Res
	AddBoneIndex(Enum_BoneType::B_01_RightHand, 78);
	AddBoneIndex(Enum_BoneType::B_01_LeftHand, 47);

	// Physx Component
	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();

	// Anmation
	MainRenderer->SetFBXMesh("c1280.fbx", "FBXAnimationTexture");

	MainRenderer->CreateFBXAnimation("Idle_Standing1", "c1280_000000.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Standing2", "c1280_000020.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Gaurding", "c1280_000030.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Aiming", "c1280_000040.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Sit", "c1280_000700.fbx");
	MainRenderer->CreateFBXAnimation("G_Up", "c1280_001100.fbx");
	MainRenderer->CreateFBXAnimation("G_Down", "c1280_001101.fbx");
	MainRenderer->CreateFBXAnimation("DH_Hold", "c1280_001200.fbx");
	MainRenderer->CreateFBXAnimation("DH_UnHold", "c1280_001210.fbx");
	MainRenderer->CreateFBXAnimation("SitUp", "c1280_001700.fbx");
	MainRenderer->CreateFBXAnimation("F_Step", "c1280_002000.fbx");
	MainRenderer->CreateFBXAnimation("B_Step", "c1280_002001.fbx");
	MainRenderer->CreateFBXAnimation("L_Side_Step", "c1280_002002.fbx");
	MainRenderer->CreateFBXAnimation("R_Side_Step", "c1280_002003.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Step", "c1280_002030.fbx");
	MainRenderer->CreateFBXAnimation("G_B_Step", "c1280_002031.fbx");
	MainRenderer->CreateFBXAnimation("G_L_Side_Step", "c1280_002032.fbx");
	MainRenderer->CreateFBXAnimation("G_R_Side_Step", "c1280_002033.fbx");
	MainRenderer->CreateFBXAnimation("DH_F_Step", "c1280_002040.fbx");
	MainRenderer->CreateFBXAnimation("DH_B_Step", "c1280_002041.fbx");
	MainRenderer->CreateFBXAnimation("DH_L_Side_Step", "c1280_002042.fbx");
	MainRenderer->CreateFBXAnimation("DH_R_Side_Step", "c1280_002043.fbx");
	MainRenderer->CreateFBXAnimation("Run", "c1280_002100.fbx");
	MainRenderer->CreateFBXAnimation("G_Run", "c1280_002130.fbx");
	MainRenderer->CreateFBXAnimation("Patrol", "c1280_002300.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_11", "c1280_003000.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_12", "c1280_003001.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_13", "c1280_003002.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_21", "c1280_003003.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_22", "c1280_003004.fbx");
	MainRenderer->CreateFBXAnimation("Combo_Att_23", "c1280_003005.fbx");
	MainRenderer->CreateFBXAnimation("G_Att_Bash", "c1280_003006.fbx");
	MainRenderer->CreateFBXAnimation("DH_Stab_Att", "c1280_003007.fbx");
	MainRenderer->CreateFBXAnimation("DH_Swing_Att", "c1280_003008.fbx");
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
	MainRenderer->CreateFBXAnimation("G_L_Turn", "c1280_005020.fbx");
	MainRenderer->CreateFBXAnimation("G_R_Turn", "c1280_005021.fbx");
	MainRenderer->CreateFBXAnimation("G_L_TurnTwice", "c1280_005022.fbx");
	MainRenderer->CreateFBXAnimation("G_R_TurnTwice", "c1280_005023.fbx");


	MainRenderer->SetRootMotionComponent(Capsule.get());
	MainRenderer->SetRootMotion("Idle_Standing1");
	MainRenderer->SetRootMotion("Idle_Standing2");
	MainRenderer->SetRootMotion("Idle_Gaurding");
	MainRenderer->SetRootMotion("Idle_Aiming");
	MainRenderer->SetRootMotion("Idle_Sit");
	MainRenderer->SetRootMotion("G_Up");
	MainRenderer->SetRootMotion("G_Down");
	MainRenderer->SetRootMotion("DH_Hold");
	MainRenderer->SetRootMotion("DH_UnHold");
	MainRenderer->SetRootMotion("SitUp");
	MainRenderer->SetRootMotion("F_Step");
	MainRenderer->SetRootMotion("B_Step");
	MainRenderer->SetRootMotion("L_Side_Step");
	MainRenderer->SetRootMotion("R_Side_Step");
	MainRenderer->SetRootMotion("G_F_Step");
	MainRenderer->SetRootMotion("G_B_Step");
	MainRenderer->SetRootMotion("G_L_Side_Step");
	MainRenderer->SetRootMotion("G_R_Side_Step");
	MainRenderer->SetRootMotion("DH_F_Step");
	MainRenderer->SetRootMotion("DH_B_Step");
	MainRenderer->SetRootMotion("DH_L_Side_Step");
	MainRenderer->SetRootMotion("DH_R_Side_Step");
	MainRenderer->SetRootMotion("Run");
	MainRenderer->SetRootMotion("G_Run");
	MainRenderer->SetRootMotion("Patrol");
	MainRenderer->SetRootMotion("Combo_Att_11");
	MainRenderer->SetRootMotion("Combo_Att_12");
	MainRenderer->SetRootMotion("Combo_Att_13");
	MainRenderer->SetRootMotion("Combo_Att_21");
	MainRenderer->SetRootMotion("Combo_Att_22");
	MainRenderer->SetRootMotion("Combo_Att_23");
	MainRenderer->SetRootMotion("G_Att_Bash");
	MainRenderer->SetRootMotion("DH_Stab_Att");
	MainRenderer->SetRootMotion("DH_Swing_Att");
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
	MainRenderer->SetRootMotion("G_L_Turn");
	MainRenderer->SetRootMotion("G_R_Turn");
	MainRenderer->SetRootMotion("G_L_TurnTwice");
	MainRenderer->SetRootMotion("G_R_TurnTwice");

	SetMeshVisibility(eMeshInfo::Spear, false);
	SetMeshVisibility(eMeshInfo::LSword, false);
	SetMeshVisibility(eMeshInfo::Crossbow, false);
	SetMeshVisibility(eMeshInfo::Open, false);
	SetMeshVisibility(eMeshInfo::LShield, false);
	SetMeshVisibility(eMeshInfo::Weapon_Cloth, false);

	// Collision
	CreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_RightHand, "B_01_RightHand");

	PatrolCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	PatrolCollision->Transform.SetWorldScale(float4(300, 300, 300));
	PatrolCollision->SetCollisionType(ColType::SPHERE3D);
	PatrolCollision->SetCollisionColor(float4::BLUE);

	// FSM
	CombatState = Enum_Combat_State::Normal;

	CreateFSM();
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);

	static bool s_bDrawValue = false;
	if (GameEngineInput::IsDown('N', this))
	{
		s_bDrawValue = !s_bDrawValue;
	}

	if (s_bDrawValue)
	{
		DrawRange(CLOSE_RANGE * W_SCALE);
		DrawRange(MELEE_RANGE * W_SCALE, float4::WHITE);
		DrawRange(MEDIUM_RANGE * W_SCALE, float4::BLACK);
	}

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

	bool FindValue = (nullptr != pActor);
	if (FindValue)
	{
		PatrolCollision->Off();
		SetTargeting(pActor.get());
	}
};

void Monster_LothricKn::WakeUp() 
{
	MainState.ChangeState(Enum_LothricKn_State::Patrol);
}

float Monster_LothricKn::ConvertDistance_eTof(Enum_TargetDist _eTDist) const
{
	switch (_eTDist)
	{
	case BaseMonster::Enum_TargetDist::Close:
		return CLOSE_RANGE;
	case BaseMonster::Enum_TargetDist::Melee:
		return MELEE_RANGE;
	case BaseMonster::Enum_TargetDist::Medium:
		return MEDIUM_RANGE;
	case BaseMonster::Enum_TargetDist::Long:
		return LONG_RANGE;
	case BaseMonster::Enum_TargetDist::None:
	default:
		break;
	}

	MsgBoxAssert("해당 타입은 존재하지 않습니다.");
	return 0.0f;
}