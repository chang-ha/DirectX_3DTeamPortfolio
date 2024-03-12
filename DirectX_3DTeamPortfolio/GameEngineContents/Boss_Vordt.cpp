#include "PreCompile.h"
#include "Boss_Vordt.h"
#include "BoneSocketCollision.h"
#include "DS3DummyData.h"

#define BOSS_HP 1328

void Boss_State_GUI::Start()
{

}

void Boss_State_GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == Linked_Boss)
	{
		return;
	}
		
	int Index = 0;

	if (0 == StateNames.size())
	{
		const std::map<int, State>* AllStates = Linked_Boss->MainState.GetAllStates();

		if (0 == StateNames.capacity())
		{
			StateNames.reserve(AllStates->size());
			StateIndex.reserve(AllStates->size());
		}

		std::map<int, State>::const_iterator StartIter = AllStates->begin();
		std::map<int, State>::const_iterator EndIter = AllStates->end();
		for (; StartIter != EndIter; ++StartIter)
		{
			StateNames.push_back(StartIter->second.Name.c_str());
			StateIndex.push_back(StartIter->first);
		}
	}

	{
		if (ImGui::ListBox("State", &Index, &StateNames[0], static_cast<int>(StateNames.size())))
		{
			Linked_Boss->MainState.ChangeState(StateIndex[Index]);
		}
	}

	ImGui::NewLine();

	{
		int Frame = Linked_Boss->MainRenderer->GetCurAnimationFrame();
		std::string String = "AniFrame\n";
		String += std::to_string(Frame);
		ImGui::Text(String.c_str());
	}

	ImGui::NewLine();

	bool IsRootMotion = Linked_Boss->MainRenderer->GetCurAnimation()->IsRootMotion();
	if (true == ImGui::Checkbox("RootMotion", &IsRootMotion))
	{
		Linked_Boss->MainRenderer->GetCurAnimation()->SwitchRootMotion();
	}

	ImGui::NewLine();

	bool IsRotation = Linked_Boss->MainRenderer->GetCurAnimation()->IsRootMotionRot();
	if (true == ImGui::Checkbox("RootMotionRot", &IsRotation))
	{
		Linked_Boss->MainRenderer->GetCurAnimation()->SwitchRootMotionRot();
	}

	ImGui::NewLine();

	{
		physx::PxVec3 Vec = Linked_Boss->Capsule->GetLinearVelocity();

		Vec.x = floor(Vec.x * 100) / 100;
		Vec.y = floor(Vec.y * 100) / 100;
		if (Vec.y < 0.001f)
		{
			Vec.y = 0.00f;
		}
		Vec.z = floor(Vec.z * 100) / 100;

		std::string Speed = "Speed\n";
		Speed += "X : " + std::to_string(Vec.x) + "\n";
		Speed += "Y : " + std::to_string(Vec.y) + "\n";
		Speed += "Z : " + std::to_string(Vec.z) + "\n";
		ImGui::Text(Speed.c_str());
	}

	ImGui::NewLine();

	{
		physx::PxVec3 Vec = Linked_Boss->Capsule->GetWorldPosition();

		Vec.x = floor(Vec.x * 100) / 100;
		Vec.y = floor(Vec.y * 100) / 100;
		Vec.z = floor(Vec.z * 100) / 100;

		std::string Pos = "Pos\n";
		Pos += "X : " + std::to_string(Vec.x) + "\n";
		Pos += "Y : " + std::to_string(Vec.y) + "\n";
		Pos += "Z : " + std::to_string(Vec.z) + "\n";
		ImGui::Text(Pos.c_str());
	}

	ImGui::NewLine();

	{
		std::string String = "Z Dir\n";
		ImGui::Text(String.c_str());
		ImGui::DragFloat("Z Dir", Linked_Boss->Capsule->GetDirPtr(), 0.1f, -180.f, 180.f);
	}

	ImGui::NewLine();

	{
		std::string String = "Z Rotation\n";
		ImGui::Text(String.c_str());
		float4 Rot = Linked_Boss->Transform.GetWorldRotationEuler();
		if (true == ImGui::DragFloat("Z Rot", &Rot.Y, 0.1f, -180.f, 180.f))
		{
			Linked_Boss->Capsule->SetWorldRotation(Rot);
		}
	}

	ImGui::NewLine();

	{
		bool Result = Linked_Boss->Capsule->IsGravity();
		std::string Gravity = "IsGravity\n";
		switch (Result)
		{
		case 0:
			Gravity += " False";
			break;
		default:
			Gravity += " True";
			break;
		}
		ImGui::Text(Gravity.c_str());
	}

	ImGui::NewLine();

	{
		float Angle = Linked_Boss->Capsule->GetDir();
		std::string cAngle = "My Angle : ";
		cAngle += std::to_string(Angle);
		ImGui::Text(cAngle.c_str());
	}

	ImGui::NewLine();

	if (true == Linked_Boss->IsTargeting())
	{
		float Angle = Linked_Boss->GetTargetAngle();
		std::string cAngle = "Target Angle : ";
		cAngle += std::to_string(Angle);
		cAngle += "(";

		std::string eAngle = "";
		switch (Linked_Boss->mTargetState.mTargetDeg)
		{
		case Enum_TargetDeg::Deg_Null:
			eAngle += "Null";
			break;
		case Enum_TargetDeg::Deg_Front:
			eAngle += "Front";
			break;
		case Enum_TargetDeg::Deg_Side:
			eAngle += "Side";
			break;
		case Enum_TargetDeg::Deg_Back:
			eAngle += "Back";
			break;
		default:
			break;
		}

		cAngle += eAngle + ")";

		ImGui::Text(cAngle.c_str());

		Enum_RotDir Dir = Linked_Boss->GetRotDir_e();
		std::string cDir = "Rotation Dir : ";

		switch (Dir)
		{
		case Enum_RotDir::Not_Rot:
			cDir += "Not_Rot";
			break;
		case Enum_RotDir::Left:
			cDir += "Left";
			break;
		case Enum_RotDir::Right:
			cDir += "Right";
			break;
		default:
			MsgBoxAssert("존재하지 않는 회전방향입니다.");
			break;
		}

		ImGui::Text(cDir.c_str());
	}

	ImGui::NewLine();

	if (true == Linked_Boss->IsTargeting())
	{
		float Dis = Linked_Boss->GetTargetDistance();
		std::string cDistance = "Target Distance : ";
		cDistance += std::to_string(Dis);
		cDistance += "(";

		std::string eDistance = "";
		switch (Linked_Boss->mTargetState.mTargetDis)
		{
		case Enum_TargetDis::Dis_Null:
			eDistance += "Null";
			break;
		case Enum_TargetDis::Dis_Attach:
			eDistance += "Attach";
			break;
		case Enum_TargetDis::Dis_Close:
			eDistance += "Close";
			break;
		case Enum_TargetDis::Dis_Middle:
			eDistance += "Middle";
			break;
		case Enum_TargetDis::Dis_Long:
			eDistance += "Long";
			break;
		case Enum_TargetDis::Dis_Far:
			eDistance += "Far";
			break;
		default:
			break;
		}

		cDistance += eDistance +")";

		ImGui::Text(cDistance.c_str());
	}

	ImGui::NewLine();

	{
		if (true == ImGui::Button("SetWorldOrigin", ImVec2(250, 30)))
		{
			Linked_Boss->Capsule->SetWorldPosition({0.f, 0.f, 0.f});
			Linked_Boss->Capsule->SetWorldRotation({0.f, 180.f, 0.f});
			Linked_Boss->MainState.ChangeState(Enum_BossState::Idle);
		}
	}
}

void Boss_State_GUI::Reset()
{
	StateNames.clear();
	Linked_Boss = nullptr;
}

void AI_State::Update(float _Delta)
{
	CurCoolDown -= _Delta;
}

Boss_Vordt::Boss_Vordt()
{

}

Boss_Vordt::~Boss_Vordt()
{

}

void Boss_Vordt::LevelStart(GameEngineLevel* _PrevLevel)
{
	// Boss Mesh
	{
		if (nullptr == GameEngineFBXMesh::Find("c2240.fbx"))
		{
			GameEngineFile File;
			File.MoveParentToExistsChild("ContentsResources");
			File.MoveChild("ContentsResources\\Mesh\\Boss\\c2240.fbx");
			GameEngineFBXMesh::Load(File.GetStringPath());
		}

		MainRenderer->SetFBXMesh("c2240.FBX", "FBX_Animation"); // Bone 136
	}

	// Boss Animation
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Mesh\\c2240\\Animation");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXAnimation::Load(Files[i].GetStringPath());
		}

		// Animation
		MainRenderer->CreateFBXAnimation("Howling", "Howling.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Idle", "Idle.FBX", { ONE_FRAME_DTIME, true });
		MainRenderer->CreateFBXAnimation("Walk_Front", "Walk_Front.FBX", { ONE_FRAME_DTIME, true });
		MainRenderer->CreateFBXAnimation("Walk_Left", "Walk_Left.FBX", { ONE_FRAME_DTIME, true });
		MainRenderer->CreateFBXAnimation("Walk_Right", "Walk_Right.FBX", { ONE_FRAME_DTIME, true });
		MainRenderer->CreateFBXAnimation("Jump_Back", "Jump_Back.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Jump_Left", "Jump_Left.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Jump_Right", "Jump_Right.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Breath", "Breath.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Combo1_Step1", "Combo1_Step1.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Combo1_Step2", "Combo1_Step2.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Combo1_Step3", "Combo1_Step3.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Combo2_Step1", "Combo2_Step1.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Combo2_Step2", "Combo2_Step2.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Death", "Death.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Death_Groggy", "Death_Groggy.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Sweep&Sweep_Left", "Sweep&Sweep_Left.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Sweep&Sweep_Right", "Sweep&Sweep_Right.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_001", "Hit_001.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_002", "Hit_002.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_003_Left", "Hit_003_Left.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_003_Right", "Hit_003_Right.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_004_Groggy", "Hit_004_Groggy.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Groggy", "Hit_Groggy.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Front", "Hit_Down_001_Front.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Right", "Hit_Down_001_Right.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Left", "Hit_Down_001_Left.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_004", "Hit_Down_004.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_005", "Hit_Down_005.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Hit_Down_006", "Hit_Down_006.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush&Hit&Turn&Rush", "Rush&Hit&Turn&Rush.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush&Hit&Turn", "Rush&Hit&Turn.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush&Turn", "Rush&Turn.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush_Attack", "Rush_Attack.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush_Attack_002", "Rush_Attack_002.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Rush_Front", "Rush_Front.FBX", { ONE_FRAME_DTIME / 1.5f, true });
		MainRenderer->CreateFBXAnimation("Sweep_001", "Sweep_001.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Sweep_002", "Sweep_002.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Thrust", "Thrust.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Turn_Left", "Turn_Left.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Turn_Left_Twice", "Turn_Left_Twice.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Turn_Right", "Turn_Right.FBX", { ONE_FRAME_DTIME, false });
		MainRenderer->CreateFBXAnimation("Turn_Right_Twice", "Turn_Right_Twice.FBX", { ONE_FRAME_DTIME, false });

		FrameEventInit();

		// Root Motion
		// Rotate to StartDir
		MainRenderer->SetRootMotionComponent(Capsule.get());
		MainRenderer->SetRootMotion("Breath");
		MainRenderer->SetRootMotion("Death");
		MainRenderer->SetRootMotion("Death_Groggy");
		MainRenderer->SetRootMotion("Hit_001");
		MainRenderer->SetRootMotion("Hit_002");
		MainRenderer->SetRootMotion("Hit_003_Left");
		MainRenderer->SetRootMotion("Hit_003_Right");
		MainRenderer->SetRootMotion("Hit_004_Groggy");
		MainRenderer->SetRootMotion("Hit_Groggy");
		MainRenderer->SetRootMotion("Howling");
		MainRenderer->SetRootMotion("Rush_Front");
		MainRenderer->SetRootMotion("Turn_Left");
		MainRenderer->SetRootMotion("Turn_Left_Twice");
		MainRenderer->SetRootMotion("Turn_Right");
		MainRenderer->SetRootMotion("Turn_Right_Twice");

		// Rotate to RealTimeDir
		MainRenderer->SetRootMotion("Idle", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Jump_Back", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Jump_Left", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Jump_Right", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Walk_Front", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Walk_Left", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Walk_Right", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Combo1_Step1", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Combo1_Step2", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Combo1_Step3", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Combo2_Step1", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Combo2_Step2", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_001_Front", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_001_Right", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_001_Left", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_004", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_005", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Hit_Down_006", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Thrust", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Sweep&Sweep_Left", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Sweep&Sweep_Right", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Sweep_001", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Sweep_002", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Rush_Attack", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Rush_Attack_002", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Rush&Turn", "", Enum_RootMotionMode::RealTimeDir); // 
		MainRenderer->SetRootMotion("Rush&Hit&Turn", "", Enum_RootMotionMode::RealTimeDir);
		MainRenderer->SetRootMotion("Rush&Hit&Turn&Rush", "", Enum_RootMotionMode::RealTimeDir); // 

		MainRenderer->SetAllRootMotionMoveRatio(3.f, 3.f, 3.f);
	}

	//// Boss Collision
	{
		// BossCollision->SetCollisionType(ColType::SPHERE3D);
		// BossCollision->Transform.SetLocalPosition({ 0.0f, 0.f, 0.0f });
		// BossCollision->Transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
	}

	// physx::PxMaterial* Material = GameEnginePhysX::GetPhysics()->createMaterial(3.0f, 0.0f, 0.0f);;
	Capsule->PhysXComponentInit(320.0f, 5.0f/*, Material*/);
	// Capsule->SetMass(10000000.f);
	Capsule->SetPositioningComponent();

	if (nullptr == GameEngineGUI::FindGUIWindow<Boss_State_GUI>("Boss_State"))
	{
		GameEngineGUI::CreateGUIWindow<Boss_State_GUI>("Boss_State");
	}

	GUI = GameEngineGUI::FindGUIWindow<Boss_State_GUI>("Boss_State");
	GUI->Linked_Boss = this;
	GUI->On();

	//// Sound
	{
		GameEngineDirectory Dir;
		Dir.SetCurrentPath();
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Sound\\c2240");
		std::vector<GameEngineFile> AllFile = Dir.GetAllFile();

		for (int i = 0; i < AllFile.size(); i++)
		{
			GameEngineSound::Sound3DLoad(AllFile[i].GetStringPath());
		}
	}

	StateInit();

	// Socket Collision
	BSCol_TransitionParameter ColParameter;
	if (nullptr == BossCollision)
	{
		ColParameter.S = float4(300.f, 300.f, 300.f);
		ColParameter.R = float4(0.f);
		ColParameter.T = float4(0.f, 0.f, 0.f);

		BossCollision = CreateSocketCollision(Enum_CollisionOrder::Monster, 21, ColParameter, "Hit_Collision");
		BossCollision->SetCollisionType(ColType::SPHERE3D);
		BossCollision->On();
	}

	if (nullptr == WeaponCollision)
	{
		ColParameter.S = float4(100.f, 100.f, 500.f);
		ColParameter.R = float4(170.f);
		ColParameter.T = float4(0.f, 0.f, 1.55f);

		WeaponCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, 47, ColParameter, "Weapon");
		WeaponCollision->SetCollisionType(ColType::OBBBOX3D);
	}

	if (nullptr == BodyCollision)
	{
		ColParameter.S = float4(300.f, 300.f, 300.f);
		ColParameter.R = float4(0.f);
		ColParameter.T = float4(0.f, 0.f, -0.5f);

		BodyCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, 22, ColParameter, "Body");
		BodyCollision->SetCollisionType(ColType::SPHERE3D);
	}

	if (nullptr == HeadCollision)
	{
		ColParameter.S = float4(150.f, 150.f, 150.f);
		ColParameter.R = float4(0.f);
		ColParameter.T = float4(0.f);

		HeadCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, 76, ColParameter, "Head");
		HeadCollision->SetCollisionType(ColType::SPHERE3D);
	}

	if (nullptr == R_HandCollision)
	{
		ColParameter.S = float4(180.f, 70.f, 40.f);
		ColParameter.R = float4(0.f);
		ColParameter.T = float4(-0.5f, 0.f, -0.15f);

		R_HandCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, 57, ColParameter, "R_Hand");
		R_HandCollision->SetCollisionType(ColType::OBBBOX3D);
	}

	DS3DummyData::LoadDummyData(static_cast<int>(Enum_ActorType::Boss_Vordt));

	Stat.SetHp(BOSS_HP);
	Stat.SetAtt(1);
	Stat.SetSouls(10000);
}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{
	GUI->Linked_Boss = nullptr;
	GUI->Off();
	Death();
}

void Boss_Vordt::Start()
{
	// BaseActor::Start();
	SetID(Enum_ActorType::Boss_Vordt);
	GameEngineInput::AddInputObject(this);

	if (nullptr == MainRenderer)
	{
		MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	}

	MainRenderer->Transform.SetLocalScale({ W_SCALE, W_SCALE, W_SCALE });
	MainRenderer->Transform.SetLocalPosition({0.f, 0.f, -130.0f});

	if (nullptr == Capsule)
	{
		Capsule = CreateComponent<GameEnginePhysXCapsule>();
	}
}

void Boss_Vordt::Update(float _Delta)
{
	BaseActor::Update(_Delta);

	if (true == GameEngineInput::IsDown('B', this))
	{
		Capsule->CollisionOff();
		Capsule->ResetMove(Enum_Axies::All);
	}

	if (true == GameEngineInput::IsDown('M', this))
	{
		MainRenderer->SwitchPause();
	}

	for (std::pair<const Enum_BossState, AI_State>& _Pair : AI_States)
	{
		_Pair.second.Update(_Delta);
	}

	TargetStateUpdate();

	if (Enum_Boss_Phase::Phase_2 == mBoss_Phase)
	{
		return;
	}

	int CurHp = GetHp();
	if (BOSS_HP * 0.5f > CurHp)
	{
		mBoss_Phase = Enum_Boss_Phase::Phase_2;
	}
}

void Boss_Vordt::Release()
{
	if (nullptr != GUI)
	{
		GUI->Reset();
		GUI->Off();
		GUI = nullptr;
	}

	if (nullptr != MainRenderer)
	{
		MainRenderer->Death();
		MainRenderer = nullptr;
	}

	if (nullptr != WeaponCollision)
	{
		WeaponCollision->Death();
		WeaponCollision = nullptr;
	}

	if (nullptr != BodyCollision)
	{
		BodyCollision->Death();
		BodyCollision = nullptr;
	}

	if (nullptr != HeadCollision)
	{
		HeadCollision->Death();
		HeadCollision = nullptr;
	}

	if (nullptr != R_HandCollision)
	{
		R_HandCollision->Death();
		R_HandCollision = nullptr;
	}

	if (nullptr != BossCollision)
	{
		BossCollision->Death();
		BossCollision = nullptr;
	}

	if (nullptr != Capsule)
	{
		Capsule->Death();
		Capsule = nullptr;
	}

	AI_States.clear();

	BaseActor::Release();
}

void Boss_Vordt::TargetStateUpdate()
{
	if (false == IsTargeting())
	{
		mTargetState.mTargetDeg = Enum_TargetDeg::Deg_Null;
		mTargetState.mTargetDis = Enum_TargetDis::Dis_Null;
		return;
	}

	float CurTargetAngle = abs(GetTargetAngle());
	float CurTargetDis = GetTargetDistance();

	CurTargetAngle /= Degree_Standard;
	CurTargetDis /= Distance_Standard;

	int ICurTargetAngle = static_cast<int>(CurTargetAngle);
	int ICurTargetDis = static_cast<int>(CurTargetDis);

	if (Enum_TargetDis::Dis_Attach > ICurTargetDis)
	{
		ICurTargetDis = Enum_TargetDis::Dis_Attach;
	}
	else if (Enum_TargetDis::Dis_Far < ICurTargetDis)
	{
		ICurTargetDis = Enum_TargetDis::Dis_Far;
	}

	if (Enum_TargetDeg:: Deg_Front > ICurTargetAngle)
	{
		ICurTargetAngle = Enum_TargetDeg::Deg_Front;
	}
	else if (Enum_TargetDeg::Deg_Back < ICurTargetAngle)
	{
		ICurTargetAngle = Enum_TargetDeg::Deg_Back;
	}

	mTargetState.mTargetDeg = ICurTargetAngle;
	mTargetState.mTargetDis = ICurTargetDis;
}

bool Boss_Vordt::ChangeAI_State(Enum_BossState _State)
{
	if (false == AI_States.contains(_State))
	{
		MsgBoxAssert("존재하지 않는 Boss_State 입니다.");
		return false;
	}

	AI_State& CurAIState = AI_States[_State];

	if (0 < CurAIState.CurCoolDown)
	{
		return false;
	}

	CurAIState.CurCoolDown = CurAIState.StateCoolDown;
	MainState.ChangeState(_State);
	return true;
}

float4 Boss_Vordt::BoneWorldPos(int _BoneIndex)
{
	std::vector<float4x4>& BoneMats = MainRenderer->GetBoneSockets();
	float4x4 BoneMatrix = BoneMats.at(_BoneIndex);

	float4x4 BoneWMat = BoneMatrix * Transform.GetWorldMatrix();
	float4 S;
	float4 R;
	float4 P;
	BoneWMat.Decompose(S, R, P);

	return P;
}