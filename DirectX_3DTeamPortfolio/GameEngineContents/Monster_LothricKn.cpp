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
	AddBoneIndex(Enum_BoneType::B_01_Spine, 21);

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

	MainRenderer->CreateFBXAnimation("F_Hit_W", "c1280_008000.fbx");
	MainRenderer->CreateFBXAnimation("B_Hit_W", "c1280_008001.fbx");
	MainRenderer->CreateFBXAnimation("R_Hit_W", "c1280_008002.fbx");
	MainRenderer->CreateFBXAnimation("L_Hit_W", "c1280_008003.fbx");
	MainRenderer->CreateFBXAnimation("F_Hit", "c1280_008010.fbx");
	MainRenderer->CreateFBXAnimation("B_Hit", "c1280_008011.fbx");
	MainRenderer->CreateFBXAnimation("R_Hit", "c1280_008012.fbx");
	MainRenderer->CreateFBXAnimation("L_Hit", "c1280_008013.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Hit_W", "c1280_008200.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Hit_W_PushBack", "c1280_008201.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Hit", "c1280_008210.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Hit_PushBack", "c1280_008220.fbx");
	MainRenderer->CreateFBXAnimation("G_F_Hit_S_PushBack", "c1280_008221.fbx");
	MainRenderer->CreateFBXAnimation("Block_Shield", "c1280_008300.fbx");
	MainRenderer->CreateFBXAnimation("G_Break", "c1280_008410.fbx");
	MainRenderer->CreateFBXAnimation("Break_Posture", "c1280_008500.fbx");
	MainRenderer->CreateFBXAnimation("Res_F_Hit_W", "c1280_009000.fbx");
	MainRenderer->CreateFBXAnimation("Res_B_Hit_W", "c1280_009001.fbx");
	MainRenderer->CreateFBXAnimation("Res_R_Hit_W", "c1280_009002.fbx");
	MainRenderer->CreateFBXAnimation("Res_L_Hit_W", "c1280_009003.fbx");
	MainRenderer->CreateFBXAnimation("F_Death", "c1280_010000.fbx");
	MainRenderer->CreateFBXAnimation("F_Death_End", "c1280_010001.fbx");
	MainRenderer->CreateFBXAnimation("F_Death_B", "c1280_010030.fbx");
	MainRenderer->CreateFBXAnimation("F_Death_B_End", "c1280_010031.fbx");
	MainRenderer->CreateFBXAnimation("B_Stab", "c1280_011000.fbx");
	MainRenderer->CreateFBXAnimation("B_Stab_Death", "c1280_011001.fbx");
	MainRenderer->CreateFBXAnimation("B_Stab_Death_End", "c1280_011002.fbx");
	MainRenderer->CreateFBXAnimation("F_Stab", "c1280_011010.fbx");
	MainRenderer->CreateFBXAnimation("F_Stab_Death", "c1280_011011.fbx");
	MainRenderer->CreateFBXAnimation("F_Stab_Death_End", "c1280_011012.fbx");

	MainRenderer->SetBlendTime("Idle_Standing1", 7);
	MainRenderer->SetBlendTime("Idle_Standing2", 7);
	MainRenderer->SetBlendTime("Idle_Gaurding", 7);
	MainRenderer->SetBlendTime("Idle_Aiming", 7);
	MainRenderer->SetBlendTime("Idle_Sit", 7);
	MainRenderer->SetBlendTime("G_Up", 7);
	MainRenderer->SetBlendTime("G_Down", 7);
	MainRenderer->SetBlendTime("DH_Hold", 7);
	MainRenderer->SetBlendTime("DH_UnHold", 7);
	MainRenderer->SetBlendTime("SitUp", 4);
	MainRenderer->SetBlendTime("F_Step", 10);
	MainRenderer->SetBlendTime("B_Step", 10);
	MainRenderer->SetBlendTime("L_Side_Step", 10);
	MainRenderer->SetBlendTime("R_Side_Step", 10);
	MainRenderer->SetBlendTime("G_F_Step", 10);
	MainRenderer->SetBlendTime("G_B_Step", 10);
	MainRenderer->SetBlendTime("G_L_Side_Step", 10);
	MainRenderer->SetBlendTime("G_R_Side_Step", 10);
	MainRenderer->SetBlendTime("DH_F_Step", 7);
	MainRenderer->SetBlendTime("DH_B_Step", 7);
	MainRenderer->SetBlendTime("DH_L_Side_Step", 7);
	MainRenderer->SetBlendTime("DH_R_Side_Step", 7);
	MainRenderer->SetBlendTime("Run", 10);
	MainRenderer->SetBlendTime("G_Run", 10);
	MainRenderer->SetBlendTime("Patrol", 10);
	MainRenderer->SetBlendTime("Combo_Att_11", 7);
	MainRenderer->SetBlendTime("Combo_Att_12", 5);
	MainRenderer->SetBlendTime("Combo_Att_13", 5);
	MainRenderer->SetBlendTime("Combo_Att_21", 7);
	MainRenderer->SetBlendTime("Combo_Att_22", 5);
	MainRenderer->SetBlendTime("Combo_Att_23", 7);
	MainRenderer->SetBlendTime("G_Att_Bash", 7);
	MainRenderer->SetBlendTime("DH_Stab_Att", 7);
	MainRenderer->SetBlendTime("DH_Swing_Att", 7);
	MainRenderer->SetBlendTime("Hit_Mid", 7);
	MainRenderer->SetBlendTime("RH_Att_HitDown", 7);
	MainRenderer->SetBlendTime("LH_ShieldAttack", 7);
	MainRenderer->SetBlendTime("RH_Rear_Att", 7);
	MainRenderer->SetBlendTime("L_FastTurn", 5);
	MainRenderer->SetBlendTime("R_FastTurn", 5);
	MainRenderer->SetBlendTime("L_FastTurnTwice", 5);
	MainRenderer->SetBlendTime("R_FastTurnTwice", 5);
	MainRenderer->SetBlendTime("L_Turn", 5);
	MainRenderer->SetBlendTime("R_Turn", 5);
	MainRenderer->SetBlendTime("L_TurnTwice", 5);
	MainRenderer->SetBlendTime("R_TurnTwice", 5);
	MainRenderer->SetBlendTime("G_L_Turn", 5);
	MainRenderer->SetBlendTime("G_R_Turn", 5);
	MainRenderer->SetBlendTime("G_L_TurnTwice", 5);
	MainRenderer->SetBlendTime("G_R_TurnTwice",5);

	MainRenderer->SetBlendTime("F_Hit_W", 2);
	MainRenderer->SetBlendTime("B_Hit_W", 2);
	MainRenderer->SetBlendTime("R_Hit_W", 2);
	MainRenderer->SetBlendTime("L_Hit_W", 2);
	MainRenderer->SetBlendTime("F_Hit", 2);
	MainRenderer->SetBlendTime("B_Hit", 2);
	MainRenderer->SetBlendTime("R_Hit", 2);
	MainRenderer->SetBlendTime("L_Hit", 2);
	MainRenderer->SetBlendTime("G_F_Hit_W", 2);
	MainRenderer->SetBlendTime("G_F_Hit_W_PushBack", 2);
	MainRenderer->SetBlendTime("G_F_Hit", 2);
	MainRenderer->SetBlendTime("G_F_Hit_PushBack", 2);
	MainRenderer->SetBlendTime("G_F_Hit_S_PushBack", 2);
	MainRenderer->SetBlendTime("Block_Shield", 3);
	MainRenderer->SetBlendTime("G_Break", 3);
	MainRenderer->SetBlendTime("Break_Posture", 3);
	MainRenderer->SetBlendTime("F_Death", 5);
	MainRenderer->SetBlendTime("F_Death_End", 1);
	MainRenderer->SetBlendTime("F_Death_B", 3);
	MainRenderer->SetBlendTime("F_Death_B_End", 1);
	MainRenderer->SetBlendTime("B_Stab", 7);
	MainRenderer->SetBlendTime("B_Stab_Death", 7);
	MainRenderer->SetBlendTime("B_Stab_Death_End", 1);
	MainRenderer->SetBlendTime("F_Stab", 7);
	MainRenderer->SetBlendTime("F_Stab_Death", 7);
	MainRenderer->SetBlendTime("F_Stab_Death_End", 1);


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
	MainRenderer->SetRootMotion("G_F_Hit");
	MainRenderer->SetRootMotion("G_F_Hit_PushBack");
	MainRenderer->SetRootMotion("G_F_Hit_S_PushBack");
	MainRenderer->SetRootMotion("F_Death");
	MainRenderer->SetRootMotion("F_Death_B");
	MainRenderer->SetRootMotion("B_Stab");
	MainRenderer->SetRootMotion("B_Stab_Death");
	MainRenderer->SetRootMotion("F_Stab");
	MainRenderer->SetRootMotion("F_Stab_Death");


	SetMeshVisibility(eMeshInfo::Spear, false);
	SetMeshVisibility(eMeshInfo::LSword, false);
	SetMeshVisibility(eMeshInfo::Crossbow, false);
	SetMeshVisibility(eMeshInfo::Open, false);
	SetMeshVisibility(eMeshInfo::LShield, false);
	SetMeshVisibility(eMeshInfo::Weapon_Cloth, false);

	// Collision
	std::shared_ptr<BoneSocketCollision> AttackCol = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_BoneType::B_01_RightHand, "B_01_RightHand");
	std::vector<GameEngineCollision*> Para;
	Para.push_back(AttackCol.get());
	Sword.Init(Para);

	std::shared_ptr<BoneSocketCollision> BodyCol = CreateSocketCollision(Enum_CollisionOrder::Monster, Enum_BoneType::B_01_Spine, "B_01_Spine");
	BodyCol->On();

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

				break;
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

void Monster_LothricKn::AttackTo(eAttackType _eBoneType, Enum_CollisionOrder _Order)
{
	std::function ToShieldColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("결과값이 잘못되어 있습니다.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				pActor->GetHitToShield({ this });
			}
		};

	std::function ToBodyColEvent = [=](std::vector<GameEngineCollision*> _Other)
		{
			for (GameEngineCollision* pCol : _Other)
			{
				if (nullptr == pCol)
				{
					MsgBoxAssert("결과값이 잘못되어 있습니다.");
					return;
				}

				std::shared_ptr<BaseActor> pActor = pCol->GetActor()->GetDynamic_Cast_This<BaseActor>();
				if (nullptr == pActor)
				{
					MsgBoxAssert("형변환에 실패했습니다.");
					return;
				}

				pActor->GetHit({ this });
			}
		};

	switch (_eBoneType)
	{
	case Monster_LothricKn::eAttackType::None:
		break;
	case Monster_LothricKn::eAttackType::Sword:
		Sword.Collision(_Order, ToBodyColEvent);
		break;
	case Monster_LothricKn::eAttackType::Shield:
		break;
	case Monster_LothricKn::eAttackType::CrossBow:
		break;
	default:
		break;
	}
}

void Monster_LothricKn::AttackToPlayerInFrame(eAttackType _eBoneType, int _iStart, int _iEnd /*= -1*/)
{
	if (IsFrame(_iStart, _iEnd))
	{
		AttackTo(_eBoneType, Enum_CollisionOrder::Player);
		// AttackTo(_eBoneType, _Order);
	}
}