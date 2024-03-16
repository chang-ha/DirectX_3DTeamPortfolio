#include "PreCompile.h"
#include "Monster_LothricKn.h"

#include "DS3DummyData.h"

#include "BoneSocketCollision.h"

static constexpr int LOTHRIC_KNIGHT_HP = 326;

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
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E1001, "c128001001.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E1020, "c128001020.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E1301, "c128001301.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E2001, "c128002001.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E3001, "c128003001.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E3020, "c128003020.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E4001, "c128004001.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E4101, "c128004101.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E4310, "c128004310.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E4320, "c128004320.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E5500, "c128005500.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E6000, "c128006000.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E6003, "c128006003.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E6005, "c128006005.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E6501, "c128006501.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E8000, "c128008000.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E8001, "c128008001.wav");
	BaseActor::PushMaterialSound(Enum_DS3MaterialSound::E8500, "c128008500.wav");

	// Physx Component
	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	Capsule->SetPositioningComponent();

	// Anmation
	MainRenderer->SetFBXMesh("c1280.fbx", "FBX_Animation");
	
	MainRenderer->CreateFBXAnimation("Idle_Standing", "c1280_000000.fbx");
	MainRenderer->CreateFBXAnimation("Idle_Standing1", "c1280_000020.fbx");
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

	MainRenderer->SetBlendTime("Idle_Standing", 7);
	MainRenderer->SetBlendTime("Idle_Standing1", 7);
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
	MainRenderer->SetRootMotion("Idle_Standing");
	MainRenderer->SetRootMotion("Idle_Standing1");
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

	// Default 5000.0f 
	const float RootMoveRatio = W_SCALE * 0.033f;
	MainRenderer->SetAllRootMotionMoveRatio(RootMoveRatio, RootMoveRatio, RootMoveRatio);

	// DummyData
	DS3DummyData::LoadDummyData(static_cast<int>(Enum_ActorType::LothricKn));
	SetCenterBodyDPIndex(220);

	// Mask
	MaskReset();

	// Stat
	Stat.SetHp(LOTHRIC_KNIGHT_HP); // Official Hp
	Stat.SetAtt(1);

	// Collision
	const float PatrolSize = 5.0f * W_SCALE;

	std::shared_ptr<GameEngineCollision> SwordCol = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, eBoneType::Sword, { float4(22,16,140), float4::ZERONULL, float4(0,0, 0.9f) }, "Sword");
	std::shared_ptr<GameEngineCollision> ShieldCol = CreateSocketCollision(Enum_CollisionOrder::Monster_Shield, eBoneType::Shield, { float4(16,123,52), float4::ZERONULL, float4(0.04f, 0.24f, -0.2f) }, "Shield");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::Spine2, { float4(65,65,25) }, "Spine2");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::Pelvis, { float4(26,41,13) }, "Pelvis");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::R_Thight_Twist, { float4(41,20,10), float4::ZERONULL, float4(0.2f)}, "R_Thight_Twist");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::L_Thight_Twist, { float4(41,20,10), float4::ZERONULL, float4(0.2f)}, "L_Thight_Twist");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::R_Calf, { float4(46,13,15), float4::ZERONULL, float4(0.28f)}, "R_Calf");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::L_Calf, { float4(46,13,15), float4::ZERONULL, float4(0.28f)}, "L_Calf");
	CreateSocketCollision(Enum_CollisionOrder::Monster_Body, eBoneType::Head, { float4(21,23,30), float4(0,12,0), float4(0.14f,0.0f,-0.03f)}, "Head");

	for (const std::pair<int, std::shared_ptr<BoneSocketCollision>>& Pair : SocketCollisions)
	{
		std::shared_ptr<GameEngineCollision> Col = Pair.second;
		if (nullptr == Col)
		{
			MsgBoxAssert("존재하지 않는 충돌체를 참조하려 했습니다.");
			return;
		}

		Col->SetCollisionType(ColType::OBBBOX3D);

		const int Order = Col->GetOrder();
		const int BodyOrder = static_cast<int>(Enum_CollisionOrder::Monster_Body);
		if (BodyOrder == Order)
		{
			Col->On();
		}
	}

	Sword.Init(this, SwordCol.get());
	Sword.On();
	Shield.Init(this, ShieldCol.get());
	Shield.On();

	MonsterCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Monster);
	MonsterCollision->SetCollisionType(ColType::SPHERE3D);
	MonsterCollision->SetCollisionColor(float4::GREEN);

	PatrolCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	PatrolCollision->Transform.SetWorldScale(float4(PatrolSize, PatrolSize, PatrolSize));
	PatrolCollision->SetCollisionType(ColType::SPHERE3D);
	PatrolCollision->SetCollisionColor(float4::GREEN);
	PatrolCollision->Off();

	// FSM
	CombatState = eCombatState::Normal;

	CreateFSM();

	Transform.SetLocalScale(float4(1.0f, 1.0f, 1.0f));
}

void Monster_LothricKn::Update(float _Delta)
{
	BaseMonster::Update(_Delta);

	if (bool DebugOn = false)
	{
		Debug.OutPutChangeState(GetCurStateInt());

		static bool s_bDrawValue = false;
		if (GameEngineInput::IsDown('N', this))
		{
			s_bDrawValue = !s_bDrawValue;
		}

		if (s_bDrawValue)
		{
			DrawRange(CLOSE_RANGE * W_SCALE, float4(1.f,0.5f,0.f));
			DrawRange(MELEE_RANGE * W_SCALE, float4(0.5f, 1.f, 0.f));
			DrawRange(MEDIUM_RANGE * W_SCALE, float4(0.5f, 0.f, 1.f));
			DrawRange(LONG_RANGE * W_SCALE, float4(0.5f, 1.f, 0.5f));
		}
	}
}

void Monster_LothricKn::Release()
{
	MonsterCollision = nullptr;
	PatrolCollision = nullptr;
	Sword.Release();
	Shield.Release();

	BaseMonster::Release();
}

void Monster_LothricKn::WakeUp()
{
	On();
	ChangeIdleState(IdleType);
}

void Monster_LothricKn::Reset()
{
	Off();
	Sword.ResetRecord();
	Shield.ResetRecord();

	Stat.SetHp(LOTHRIC_KNIGHT_HP);
	Stat.SetPoise(MAX_POISE);

	Hit.SetHit(false);
	Hit.SetInvincible(false);

	MaskReset();

	SetFlagNull();
	SetTargeting(nullptr);
}

void Monster_LothricKn::SetIdleType(Enum_Lothric_IdleType _Type)
{
	if (Enum_Lothric_IdleType::None == _Type)
	{
		MsgBoxAssert("해당 타입으로 세팅할 수 없습니다");
		return;
	}

	IdleType = _Type;
}

void Monster_LothricKn::ChangeIdleState(Enum_Lothric_IdleType _Type)
{
	switch (_Type)
	{
	case Enum_Lothric_IdleType::Standing:
		MainState.ChangeState(Enum_LothricKn_State::Idle_Standing);
		break;
	case Enum_Lothric_IdleType::Sit:
		MainState.ChangeState(Enum_LothricKn_State::Idle_Sit);
		break;
	case Enum_Lothric_IdleType::None:
		break;
	default:
		break;
	}
}

void Monster_LothricKn::MaskReset()
{
	SetMeshVisibility(eMeshInfo::Body, true);
	SetMeshVisibility(eMeshInfo::Cloak, true);
	SetMeshVisibility(eMeshInfo::Spear, false);
	SetMeshVisibility(eMeshInfo::Sword, false);
	SetMeshVisibility(eMeshInfo::Shield, false);
	SetMeshVisibility(eMeshInfo::LSword, false);
	SetMeshVisibility(eMeshInfo::Crossbow, false);
	SetMeshVisibility(eMeshInfo::Cloak_cloth, true);
	SetMeshVisibility(eMeshInfo::Close, true);
	SetMeshVisibility(eMeshInfo::Open, false);
	SetMeshVisibility(eMeshInfo::LShield, false);
	SetMeshVisibility(eMeshInfo::Weapon_Cloth, false);
	SetMeshVisibility(eMeshInfo::SwordCover, true);
}

void Monster_LothricKn::HideWeaponMask()
{
	SetMeshVisibility(eMeshInfo::Sword, false);
	SetMeshVisibility(eMeshInfo::Shield, false);
}

void Monster_LothricKn::OnWeaponMask()
{
	SetMeshVisibility(eMeshInfo::Sword, true);
	SetMeshVisibility(eMeshInfo::Shield, true);
}

void Monster_LothricKn::SetPatrolCollision(bool _SwitchValue)
{
	if (PatrolCollision)
	{
		_SwitchValue  ? PatrolCollision->On() : PatrolCollision->Off();
		return;
	}

	MsgBoxAssert("정찰 충돌체를 생성하지 않았습니다");
}

bool Monster_LothricKn::FindAndSetTarget(Enum_CollisionOrder _Order)
{
	if (true == IsTargeting())
	{
		return false;
	}

	if (nullptr == PatrolCollision)
	{
		MsgBoxAssert("충돌체를 생성하지 않고 사용하려고 했습니다.");
		return false;
	}

	PatrolCollision->On();

	std::shared_ptr<GameEngineActor> pActor;
	
	PatrolCollision->Collision(_Order, [&pActor](std::vector<GameEngineCollision*>& _Other)
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

	bool bFindTarget = (nullptr != pActor);
	if (bFindTarget)
	{
		PatrolCollision->Off();
		SetTargeting(pActor.get());

		return true;
	}

	return false;
};

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

void Monster_LothricKn::AttackToPlayer(eAttackType _eBoneType)
{
	switch (_eBoneType)
	{
	case Monster_LothricKn::eAttackType::Sword:
		Sword.On();
		break;
	case Monster_LothricKn::eAttackType::Shield:
		Shield.On();
		break;
	default:
		break;
	}

	AttackToShield(_eBoneType, Enum_CollisionOrder::Player_Shield);
	AttackToBody(_eBoneType, Enum_CollisionOrder::Player_Body);
}

void Monster_LothricKn::AttackToBody(eAttackType _eBoneType, Enum_CollisionOrder _Order)
{
	switch (_eBoneType)
	{
	case Monster_LothricKn::eAttackType::Sword:
		Sword.CollisionToBody(_Order);
		break;
	case Monster_LothricKn::eAttackType::Shield:
		Shield.CollisionToBody(_Order);
		break;
	case Monster_LothricKn::eAttackType::CrossBow:
		break;
	default:
		break;
	}
}

void Monster_LothricKn::AttackToShield(eAttackType _eBoneType, Enum_CollisionOrder _Order)
{
	switch (_eBoneType)
	{
	case Monster_LothricKn::eAttackType::Sword:
		Sword.CollisionToShield(_Order);
		break;
	case Monster_LothricKn::eAttackType::Shield:
		Shield.CollisionToShield(_Order);
		break;
	case Monster_LothricKn::eAttackType::CrossBow:
		break;
	default:
		break;
	}
}

void Monster_LothricKn::AttackDone(eAttackType _eBoneType)
{
	switch (_eBoneType)
	{
	case Monster_LothricKn::eAttackType::Sword:
		Sword.Off();
		break;
	case Monster_LothricKn::eAttackType::Shield:
		Shield.Off();
		break;
	default:
		break;
	}
}