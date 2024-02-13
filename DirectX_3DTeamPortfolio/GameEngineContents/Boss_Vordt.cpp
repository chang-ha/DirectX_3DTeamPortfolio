﻿#include "PreCompile.h"
#include "Boss_Vordt.h"

#define BOSS_ANI_SPEED 0.033333f

void Boss_State_GUI::Start()
{

}

void Boss_State_GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == Linked_Boss)
	{
		return;
	}

	int AniIndex = 0;

	if (0 == AniNames.size())
	{
		const std::map<int, State>* AllStates = Linked_Boss->MainState.GetAllStates();

		if (0 == AniNames.capacity())
		{
			AniNames.reserve(AllStates->size());
		}

		std::map<int, State>::const_iterator StartIter = AllStates->begin();
		std::map<int, State>::const_iterator EndIter = AllStates->end();
		for (; StartIter != EndIter; ++StartIter)
		{
			AniNames.push_back(StartIter->second.Name.c_str());
		}

		//std::map<std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& AniInfo = Linked_Boss->MainRenderer->GetAnimationInfos();

		//if (0 == AniNames.capacity())
		//{
		//	AniNames.reserve(AniInfo.size());
		//}

		//for (std::pair<const std::string, std::shared_ptr<GameContentsFBXAnimationInfo>>& _Pair : AniInfo)
		//{
		//	AniNames.push_back(_Pair.first.data());
		//}
	}

	{
		if (ImGui::ListBox("State", &AniIndex, &AniNames[0], static_cast<int>(AniNames.size())))
		{
			Linked_Boss->MainState.ChangeState(AniIndex);
		}
	}

	ImGui::NewLine();

	{
		int Frame = Linked_Boss->MainRenderer->GetCurAnimationFrame();
		std::string String = "AniFrame\n";
		String += std::to_string(Frame);
		ImGui::Text(String.c_str());
	}

	//{
	//	if (true == ImGui::Checkbox("ChasingCamera", &IsChasingCamera))
	//	{
	//		if (false == IsChasingCamera)
	//		{
	//			Linked_Boss->GetLevel()->GetMainCamera()->Transform.SetWorldPosition(PrevCameraPos);
	//			Linked_Boss->GetLevel()->GetMainCamera()->Transform.SetWorldRotation(float4(0.f, 0.f, 0.f, 0.f));
	//		}
	//		else
	//		{
	//			ChasingCameraRot = float4(0.f, 0.f, 0.f, 0.f);
	//			PrevCameraPos = Linked_Boss->GetLevel()->GetMainCamera()->Transform.GetWorldPosition();
	//		}
	//		ChasingCameraPos = float4(0.f, 2000.f, 0.f);
	//	}
	//}

	//if (true == IsChasingCamera)
	//{
	//	Linked_Boss->GetLevel()->GetMainCamera()->Transform.SetWorldPosition(Linked_Boss->Transform.GetWorldPosition() + ChasingCameraPos);
	//	Linked_Boss->GetLevel()->GetMainCamera()->Transform.SetWorldRotation(Linked_Boss->Transform.GetWorldRotationEuler() + ChasingCameraRot);
	//}

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

	{
		float Angle = Linked_Boss->GetTargetAngle();
		std::string cAngle = "Target Angle : ";
		cAngle += std::to_string(Angle);
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
}

void Boss_State_GUI::Reset()
{
	AniNames.clear();
	Linked_Boss = nullptr;
	IsChasingCamera = false;
	ChasingCameraPos = float4(0.f, 1000.f, 0.f);
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
		if (nullptr == GameEngineFBXMesh::Find("Mesh_Vordt.fbx"))
		{
			GameEngineFile File;
			File.MoveParentToExistsChild("ContentsResources");
			File.MoveChild("ContentsResources\\Mesh\\Boss\\Mesh_Vordt.fbx");
			GameEngineFBXMesh::Load(File.GetStringPath());
		}

		//if (nullptr == MainRenderer)
		//{
		// 	MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
		//}

		MainRenderer->SetFBXMesh("Mesh_Vordt.FBX", "FBX_Animation"); // Bone 136
		MainRenderer->Transform.SetLocalScale({ 1.f, 1.f, 1.f });
		MainRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, 0.f });
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
		MainRenderer->CreateFBXAnimation("Howling", "Howling.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Idle", "Idle.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Walk_Front", "Walk_Front.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Walk_Left", "Walk_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Walk_Right", "Walk_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Jump_Back", "Jump_Back.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Jump_Left", "Jump_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Jump_Right", "Jump_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Breath", "Breath.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Combo1_Step1", "Combo1_Step1.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Combo1_Step2", "Combo1_Step2.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Combo1_Step3", "Combo1_Step3.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Combo2_Step1", "Combo2_Step1.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Combo2_Step2", "Combo2_Step2.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Death", "Death.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Death_Groggy", "Death_Groggy.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Sweep&Sweep_Left", "Sweep&Sweep_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Sweep&Sweep_Right", "Sweep&Sweep_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_001", "Hit_001.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_002", "Hit_002.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_003_Left", "Hit_003_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_003_Right", "Hit_003_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_004_Groggy", "Hit_004_Groggy.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Groggy", "Hit_Groggy.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Front", "Hit_Down_001_Front.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Right", "Hit_Down_001_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_001_Left", "Hit_Down_001_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_004", "Hit_Down_004.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_005", "Hit_Down_005.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Hit_Down_006", "Hit_Down_006.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush&Hit&Turn&Rush", "Rush&Hit&Turn&Rush.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush&Hit&Turn", "Rush&Hit&Turn.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush&Turn", "Rush&Turn.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush_Attack", "Rush_Attack.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush_Attack_002", "Rush_Attack_002.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Rush_Front", "Rush_Front.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Sweep_001", "Sweep_001.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Sweep_002", "Sweep_002.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Thrust", "Thrust.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Turn_Left", "Turn_Left.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Turn_Left_Twice", "Turn_Left_Twice.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Turn_Right", "Turn_Right.FBX", { BOSS_ANI_SPEED, true });
		MainRenderer->CreateFBXAnimation("Turn_Right_Twice", "Turn_Right_Twice.FBX", { BOSS_ANI_SPEED, true });

		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 52, [&](GameContentsFBXRenderer* _Renderer)
			{
				std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = MainRenderer->GetCurAnimation();
				AniInfo->SetStartDir(Capsule->GetDir());
				MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::StartDir);
			});

		MainRenderer->SetFrameEvent("Rush&Hit&Turn&Rush", 133, [&](GameContentsFBXRenderer* _Renderer)
			{
				// 반대로 가는현상 해결 필요
				std::shared_ptr<GameContentsFBXAnimationInfo> AniInfo = MainRenderer->GetCurAnimation();
				AniInfo->SetStartDir(Capsule->GetDir());
				MainRenderer->SetRootMotionMode("Rush&Hit&Turn&Rush", Enum_RootMotionMode::StartDir);
			});

		/////// Sound
		SoundEventInit();

		// Root Motion
		// Rotate to StartDir
		MainRenderer->SetRootMotionComponent(Capsule.get());
		MainRenderer->SetRootMotion("Breath");
		MainRenderer->SetRootMotion("Combo1_Step1");
		MainRenderer->SetRootMotion("Combo1_Step2");
		MainRenderer->SetRootMotion("Combo1_Step3");
		MainRenderer->SetRootMotion("Combo2_Step1");
		MainRenderer->SetRootMotion("Combo2_Step2");
		MainRenderer->SetRootMotion("Death");
		MainRenderer->SetRootMotion("Death_Groggy");
		MainRenderer->SetRootMotion("Hit_001");
		MainRenderer->SetRootMotion("Hit_002");
		MainRenderer->SetRootMotion("Hit_003_Left");
		MainRenderer->SetRootMotion("Hit_003_Right");
		MainRenderer->SetRootMotion("Hit_004_Groggy");
		MainRenderer->SetRootMotion("Hit_Groggy");
		MainRenderer->SetRootMotion("Hit_Down_001_Front");
		MainRenderer->SetRootMotion("Hit_Down_001_Right");
		MainRenderer->SetRootMotion("Hit_Down_001_Left");
		MainRenderer->SetRootMotion("Hit_Down_004");
		MainRenderer->SetRootMotion("Hit_Down_005");
		MainRenderer->SetRootMotion("Hit_Down_006");
		MainRenderer->SetRootMotion("Howling");
		MainRenderer->SetRootMotion("Rush&Hit&Turn"); 
		MainRenderer->SetRootMotion("Rush&Turn"); // 
		MainRenderer->SetRootMotion("Rush_Attack");
		MainRenderer->SetRootMotion("Rush_Attack_002");
		MainRenderer->SetRootMotion("Rush_Front");
		MainRenderer->SetRootMotion("Sweep&Sweep_Left");
		MainRenderer->SetRootMotion("Sweep&Sweep_Right");
		MainRenderer->SetRootMotion("Sweep_001");
		MainRenderer->SetRootMotion("Sweep_002");
		MainRenderer->SetRootMotion("Thrust");
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
		MainRenderer->SetRootMotion("Rush&Hit&Turn&Rush", "", Enum_RootMotionMode::RealTimeDir); // 
	}

	//// Boss Collision
	{
		//BossCollision->SetCollisionType(ColType::SPHERE3D);
		//BossCollision->Transform.SetLocalPosition({ 0.0f, 200.f, 0.0f });
		//BossCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
	}

	//// Detect Collision
#define DETECT_SCALE 15
	{
		DetectCollision->SetCollisionType(ColType::SPHERE3D);
		DetectCollision->Transform.SetLocalPosition({ 0.f, 0.f, DETECT_SCALE * 0.3f });
		DetectCollision->Transform.SetLocalScale({ DETECT_SCALE, DETECT_SCALE, DETECT_SCALE });
		// GameEngineDebug::DrawSphere2D(Transform, float4::GREEN, GetLevel()->GetMainCamera().get());
	}

	Capsule->PhysXComponentInit(100.0f, 50.0f);
	// Capsule->SetMass(100.f);
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

	// State
	{
		// Move & Others
		CreateStateParameter Howling;
		Howling.Start = std::bind(&Boss_Vordt::Howling_Start, this);
		Howling.Stay = std::bind(&Boss_Vordt::Howling_Update, this, std::placeholders::_1);
		Howling.End = std::bind(&Boss_Vordt::Howling_End, this);

		CreateStateParameter Idle;
		Idle.Start = std::bind(&Boss_Vordt::Idle_Start, this);
		Idle.Stay = std::bind(&Boss_Vordt::Idle_Update, this, std::placeholders::_1);
		Idle.End = std::bind(&Boss_Vordt::Idle_End, this);

		CreateStateParameter Walk_Front;
		Walk_Front.Start = std::bind(&Boss_Vordt::Walk_Front_Start, this);
		Walk_Front.Stay = std::bind(&Boss_Vordt::Walk_Front_Update, this, std::placeholders::_1);
		Walk_Front.End = std::bind(&Boss_Vordt::Walk_Front_End, this);

		CreateStateParameter Walk_Right;
		Walk_Right.Start = std::bind(&Boss_Vordt::Walk_Right_Start, this);
		Walk_Right.Stay = std::bind(&Boss_Vordt::Walk_Right_Update, this, std::placeholders::_1);
		Walk_Right.End = std::bind(&Boss_Vordt::Walk_Right_End, this);

		CreateStateParameter Walk_Left;
		Walk_Left.Start = std::bind(&Boss_Vordt::Walk_Left_Start, this);
		Walk_Left.Stay = std::bind(&Boss_Vordt::Walk_Left_Update, this, std::placeholders::_1);
		Walk_Left.End = std::bind(&Boss_Vordt::Walk_Left_End, this);

		CreateStateParameter Rush_Front;
		Rush_Front.Start = std::bind(&Boss_Vordt::Rush_Front_Start, this);
		Rush_Front.Stay = std::bind(&Boss_Vordt::Rush_Front_Update, this, std::placeholders::_1);
		Rush_Front.End = std::bind(&Boss_Vordt::Rush_Front_End, this);

		CreateStateParameter Jump_Back;
		Jump_Back.Start = std::bind(&Boss_Vordt::Jump_Back_Start, this);
		Jump_Back.Stay = std::bind(&Boss_Vordt::Jump_Back_Update, this, std::placeholders::_1);
		Jump_Back.End = std::bind(&Boss_Vordt::Jump_Back_End, this);

		CreateStateParameter Jump_Right;
		Jump_Right.Start = std::bind(&Boss_Vordt::Jump_Right_Start, this);
		Jump_Right.Stay = std::bind(&Boss_Vordt::Jump_Right_Update, this, std::placeholders::_1);
		Jump_Right.End = std::bind(&Boss_Vordt::Jump_Right_End, this);

		CreateStateParameter Jump_Left;
		Jump_Left.Start = std::bind(&Boss_Vordt::Jump_Left_Start, this);
		Jump_Left.Stay = std::bind(&Boss_Vordt::Jump_Left_Update, this, std::placeholders::_1);
		Jump_Left.End = std::bind(&Boss_Vordt::Jump_Left_End, this);

		CreateStateParameter Turn_Right;
		Turn_Right.Start = std::bind(&Boss_Vordt::Turn_Right_Start, this);
		Turn_Right.Stay = std::bind(&Boss_Vordt::Turn_Right_Update, this, std::placeholders::_1);
		Turn_Right.End = std::bind(&Boss_Vordt::Turn_Right_End, this);

		CreateStateParameter Turn_Left;
		Turn_Left.Start = std::bind(&Boss_Vordt::Turn_Left_Start, this);
		Turn_Left.Stay = std::bind(&Boss_Vordt::Turn_Left_Update, this, std::placeholders::_1);
		Turn_Left.End = std::bind(&Boss_Vordt::Turn_Left_End, this);

		CreateStateParameter Turn_Right_Twice;
		Turn_Right_Twice.Start = std::bind(&Boss_Vordt::Turn_Right_Twice_Start, this);
		Turn_Right_Twice.Stay = std::bind(&Boss_Vordt::Turn_Right_Twice_Update, this, std::placeholders::_1);
		Turn_Right_Twice.End = std::bind(&Boss_Vordt::Turn_Right_Twice_End, this);

		CreateStateParameter Turn_Left_Twice;
		Turn_Left_Twice.Start = std::bind(&Boss_Vordt::Turn_Left_Twice_Start, this);
		Turn_Left_Twice.Stay = std::bind(&Boss_Vordt::Turn_Left_Twice_Update, this, std::placeholders::_1);
		Turn_Left_Twice.End = std::bind(&Boss_Vordt::Turn_Left_Twice_End, this);

		CreateStateParameter Hitten;
		Hitten.Start = std::bind(&Boss_Vordt::Hitten_Start, this);
		Hitten.Stay = std::bind(&Boss_Vordt::Hitten_Update, this, std::placeholders::_1);
		Hitten.End = std::bind(&Boss_Vordt::Hitten_End, this);

		CreateStateParameter Groggy;
		Groggy.Start = std::bind(&Boss_Vordt::Groggy_Start, this);
		Groggy.Stay = std::bind(&Boss_Vordt::Groggy_Update, this, std::placeholders::_1);
		Groggy.End = std::bind(&Boss_Vordt::Groggy_End, this);

		CreateStateParameter Death;
		Death.Start = std::bind(&Boss_Vordt::Death_Start, this);
		Death.Stay = std::bind(&Boss_Vordt::Death_Update, this, std::placeholders::_1);
		Death.End = std::bind(&Boss_Vordt::Death_End, this);

		// Attack
		CreateStateParameter Breath;
		Breath.Start = std::bind(&Boss_Vordt::Breath_Start, this);
		Breath.Stay = std::bind(&Boss_Vordt::Breath_Update, this, std::placeholders::_1);
		Breath.End = std::bind(&Boss_Vordt::Breath_End, this);

		CreateStateParameter Combo1;
		Combo1.Start = std::bind(&Boss_Vordt::Combo1_Start, this);
		Combo1.Stay = std::bind(&Boss_Vordt::Combo1_Update, this, std::placeholders::_1);
		Combo1.End = std::bind(&Boss_Vordt::Combo1_End, this);

		CreateStateParameter Combo2;
		Combo2.Start = std::bind(&Boss_Vordt::Combo2_Start, this);
		Combo2.Stay = std::bind(&Boss_Vordt::Combo2_Update, this, std::placeholders::_1);
		Combo2.End = std::bind(&Boss_Vordt::Combo2_End, this);

		CreateStateParameter Sweap_Twice_Right;
		Sweap_Twice_Right.Start = std::bind(&Boss_Vordt::Sweap_Twice_Right_Start, this);
		Sweap_Twice_Right.Stay = std::bind(&Boss_Vordt::Sweap_Twice_Right_Update, this, std::placeholders::_1);
		Sweap_Twice_Right.End = std::bind(&Boss_Vordt::Sweap_Twice_Right_End, this);

		CreateStateParameter Sweap_Twice_Left;
		Sweap_Twice_Left.Start = std::bind(&Boss_Vordt::Sweap_Twice_Left_Start, this);
		Sweap_Twice_Left.Stay = std::bind(&Boss_Vordt::Sweap_Twice_Left_Update, this, std::placeholders::_1);
		Sweap_Twice_Left.End = std::bind(&Boss_Vordt::Sweap_Twice_Left_End, this);

		CreateStateParameter Hit_Down_001_Front;
		Hit_Down_001_Front.Start = std::bind(&Boss_Vordt::Hit_Down_001_Front_Start, this);
		Hit_Down_001_Front.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Front_Update, this, std::placeholders::_1);
		Hit_Down_001_Front.End = std::bind(&Boss_Vordt::Hit_Down_001_Front_End, this);

		CreateStateParameter Hit_Down_001_Right;
		Hit_Down_001_Right.Start = std::bind(&Boss_Vordt::Hit_Down_001_Right_Start, this);
		Hit_Down_001_Right.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Right_Update, this, std::placeholders::_1);
		Hit_Down_001_Right.End = std::bind(&Boss_Vordt::Hit_Down_001_Right_End, this);

		CreateStateParameter Hit_Down_001_Left;
		Hit_Down_001_Left.Start = std::bind(&Boss_Vordt::Hit_Down_001_Left_Start, this);
		Hit_Down_001_Left.Stay = std::bind(&Boss_Vordt::Hit_Down_001_Left_Update, this, std::placeholders::_1);
		Hit_Down_001_Left.End = std::bind(&Boss_Vordt::Hit_Down_001_Left_End, this);

		CreateStateParameter Hit_Down_004;
		Hit_Down_004.Start = std::bind(&Boss_Vordt::Hit_Down_004_Start, this);
		Hit_Down_004.Stay = std::bind(&Boss_Vordt::Hit_Down_004_Update, this, std::placeholders::_1);
		Hit_Down_004.End = std::bind(&Boss_Vordt::Hit_Down_004_End, this);

		CreateStateParameter Hit_Down_005;
		Hit_Down_005.Start = std::bind(&Boss_Vordt::Hit_Down_005_Start, this);
		Hit_Down_005.Stay = std::bind(&Boss_Vordt::Hit_Down_005_Update, this, std::placeholders::_1);
		Hit_Down_005.End = std::bind(&Boss_Vordt::Hit_Down_005_End, this);

		CreateStateParameter Hit_Down_006;
		Hit_Down_006.Start = std::bind(&Boss_Vordt::Hit_Down_006_Start, this);
		Hit_Down_006.Stay = std::bind(&Boss_Vordt::Hit_Down_006_Update, this, std::placeholders::_1);
		Hit_Down_006.End = std::bind(&Boss_Vordt::Hit_Down_006_End, this);

		CreateStateParameter Thrust;
		Thrust.Start = std::bind(&Boss_Vordt::Thrust_Start, this);
		Thrust.Stay = std::bind(&Boss_Vordt::Thrust_Update, this, std::placeholders::_1);
		Thrust.End = std::bind(&Boss_Vordt::Thrust_End, this);

		CreateStateParameter Sweep_001;
		Sweep_001.Start = std::bind(&Boss_Vordt::Sweep_001_Start, this);
		Sweep_001.Stay = std::bind(&Boss_Vordt::Sweep_001_Update, this, std::placeholders::_1);
		Sweep_001.End = std::bind(&Boss_Vordt::Sweep_001_End, this);

		CreateStateParameter Sweep_002;
		Sweep_002.Start = std::bind(&Boss_Vordt::Sweep_002_Start, this);
		Sweep_002.Stay = std::bind(&Boss_Vordt::Sweep_002_Update, this, std::placeholders::_1);
		Sweep_002.End = std::bind(&Boss_Vordt::Sweep_002_End, this);

		CreateStateParameter Rush_Attack_001;
		Rush_Attack_001.Start = std::bind(&Boss_Vordt::Rush_Attack_001_Start, this);
		Rush_Attack_001.Stay = std::bind(&Boss_Vordt::Rush_Attack_001_Update, this, std::placeholders::_1);
		Rush_Attack_001.End = std::bind(&Boss_Vordt::Rush_Attack_001_End, this);

		CreateStateParameter Rush_Attack_002;
		Rush_Attack_002.Start = std::bind(&Boss_Vordt::Rush_Attack_002_Start, this);
		Rush_Attack_002.Stay = std::bind(&Boss_Vordt::Rush_Attack_002_Update, this, std::placeholders::_1);
		Rush_Attack_002.End = std::bind(&Boss_Vordt::Rush_Attack_002_End, this);

		CreateStateParameter Rush_Turn;
		Rush_Turn.Start = std::bind(&Boss_Vordt::Rush_Turn_Start, this);
		Rush_Turn.Stay = std::bind(&Boss_Vordt::Rush_Turn_Update, this, std::placeholders::_1);
		Rush_Turn.End = std::bind(&Boss_Vordt::Rush_Turn_End, this);

		CreateStateParameter Rush_Hit_Turn;
		Rush_Hit_Turn.Start = std::bind(&Boss_Vordt::Rush_Hit_Turn_Start, this);
		Rush_Hit_Turn.Stay = std::bind(&Boss_Vordt::Rush_Hit_Turn_Update, this, std::placeholders::_1);
		Rush_Hit_Turn.End = std::bind(&Boss_Vordt::Rush_Hit_Turn_End, this);

		CreateStateParameter Rush_Hit_Turn_Rush;
		Rush_Hit_Turn_Rush.Start = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_Start, this);
		Rush_Hit_Turn_Rush.Stay = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_Update, this, std::placeholders::_1);
		Rush_Hit_Turn_Rush.End = std::bind(&Boss_Vordt::Rush_Hit_Turn_Rush_End, this);

		// Move & Others
		MainState.CreateState(Enum_BossState::Howling, Howling, "Howling");
		MainState.CreateState(Enum_BossState::Idle, Idle, "Idle");
		MainState.CreateState(Enum_BossState::Walk_Front, Walk_Front, "Walk_Front");
		MainState.CreateState(Enum_BossState::Walk_Right, Walk_Right, "Walk_Right");
		MainState.CreateState(Enum_BossState::Walk_Left, Walk_Left, "Walk_Left");
		MainState.CreateState(Enum_BossState::Rush_Front, Rush_Front, "Rush_Front");
		MainState.CreateState(Enum_BossState::Jump_Back, Jump_Back, "Jump_Back");
		MainState.CreateState(Enum_BossState::Jump_Right, Jump_Right, "Jump_Right");
		MainState.CreateState(Enum_BossState::Jump_Left, Jump_Left, "Jump_Left");
		MainState.CreateState(Enum_BossState::Turn_Right, Turn_Right, "Turn_Right");
		MainState.CreateState(Enum_BossState::Turn_Left, Turn_Left, "Turn_Left");
		MainState.CreateState(Enum_BossState::Turn_Right_Twice, Turn_Right_Twice, "Turn_Right_Twice");
		MainState.CreateState(Enum_BossState::Turn_Left_Twice, Turn_Left_Twice, "Turn_Left_Twice");
		MainState.CreateState(Enum_BossState::Hitten, Hitten, "Hitten");
		MainState.CreateState(Enum_BossState::Groggy, Groggy, "Groggy");
		MainState.CreateState(Enum_BossState::Death, Death, "Death");

		// Attack
		MainState.CreateState(Enum_BossState::Breath, Breath, "Breath");
		MainState.CreateState(Enum_BossState::Combo1, Combo1, "Combo1");
		MainState.CreateState(Enum_BossState::Combo2, Combo2, "Combo2");
		MainState.CreateState(Enum_BossState::Sweap_Twice_Right, Sweap_Twice_Right, "Sweap_Twice_Right");
		MainState.CreateState(Enum_BossState::Sweap_Twice_Left, Sweap_Twice_Left, "Sweap_Twice_Left");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Front, Hit_Down_001_Front, "Hit_Down_001_Front");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Right, Hit_Down_001_Right, "Hit_Down_001_Right");
		MainState.CreateState(Enum_BossState::Hit_Down_001_Left, Hit_Down_001_Left, "Hit_Down_001_Left");
		MainState.CreateState(Enum_BossState::Hit_Down_004, Hit_Down_004, "Hit_Down_004");
		MainState.CreateState(Enum_BossState::Hit_Down_005, Hit_Down_005, "Hit_Down_005");
		MainState.CreateState(Enum_BossState::Hit_Down_006, Hit_Down_006, "Hit_Down_006");
		MainState.CreateState(Enum_BossState::Thrust, Thrust, "Thrust");
		MainState.CreateState(Enum_BossState::Sweep_001, Sweep_001, "Sweep_001");
		MainState.CreateState(Enum_BossState::Sweep_002, Sweep_002, "Sweep_002");
		MainState.CreateState(Enum_BossState::Rush_Attack_001, Rush_Attack_001, "Rush_Attack_001");
		MainState.CreateState(Enum_BossState::Rush_Attack_002, Rush_Attack_002, "Rush_Attack_002");
		MainState.CreateState(Enum_BossState::Rush_Turn, Rush_Turn, "Rush_Turn");
		MainState.CreateState(Enum_BossState::Rush_Hit_Turn, Rush_Hit_Turn, "Rush_Hit_Turn");
		MainState.CreateState(Enum_BossState::Rush_Hit_Turn_Rush, Rush_Hit_Turn_Rush, "Rush_Hit_Turn_Rush");

		// Start State
		MainState.ChangeState(Enum_BossState::Hitten);
	}

	if (nullptr == BossCollision)
	{
		BossCollision = CreateSocketCollision(Enum_CollisionOrder::MonsterAttack, Enum_BoneType::None);
	}

}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{
	GUI->Linked_Boss = nullptr;
	Death();
}

void Boss_Vordt::Start()
{
	// BaseActor::Start();
	SetID(Enum_ActorType::Boss_Vordt);
	GameEngineInput::AddInputObject(this);

#define RENDER_SCALE 100.f
	Transform.SetLocalScale({ RENDER_SCALE, RENDER_SCALE, RENDER_SCALE });

	if (nullptr == MainRenderer)
	{
		MainRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	}

	if (nullptr == Capsule)
	{
		Capsule = CreateComponent<GameEnginePhysXCapsule>();
	}

	if (nullptr == DetectCollision)
	{
		DetectCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
	}
}

#define SPEED 100.0f
void Boss_Vordt::Update(float _Delta)
{
	static float Cool = 3.f;
	Cool -= _Delta;
	if (0.f >= Cool)
	{
		Cool = 3.f;
	}


	BaseActor::Update(_Delta);

	if (true == GameEngineInput::IsPress('W', this))
	{
		// Capsule->MoveForce({ 0.0f, 0.0f, SPEED, 0.0f });
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		// Capsule->MoveForce({ 0.0f, 0.0f, -SPEED, 0.0f });
	}

	if (true == GameEngineInput::IsPress('A', this))
	{
		// Capsule->MoveForce({ -SPEED, 0.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		// Capsule->MoveForce({ SPEED, 0.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('Q', this))
	{
		// Capsule->AddWorldRotation({0.f, 90.f });
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		// Capsule->AddWorldRotation({ 0.f, -90.f });
	}

	if (true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		// Capsule->AddForce({ 0.0f, 2000.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('V', this))
	{

	}

	if (true == GameEngineInput::IsDown('B', this))
	{
		Capsule->CollisionOff();
		Capsule->ResetMove(Enum_Axies::All);
	}

	TargetAngle = abs(GetTargetAngle());
	if (5.f < TargetAngle)
	{
		Capsule->AddWorldRotation(float4(0.f, GetRotSpeed() * GetRotDir_f() * _Delta, 0.f));
	}
}

void Boss_Vordt::Release()
{
	if (nullptr != MainRenderer)
	{
		MainRenderer->Death();
		MainRenderer = nullptr;
	}

	//if (nullptr != BossCollision)
	//{
	//	BossCollision->Death();
	//	BossCollision = nullptr;
	//}

	if (nullptr != Capsule)
	{
		Capsule->Death();
		Capsule = nullptr;
	}

	if (nullptr != GUI)
	{
		GUI->Reset();
		GUI->Off();
		GUI = nullptr;
	}

	BaseActor::Release();
}

float4 Boss_Vordt::BoneWorldPos(int _BoneIndex)
{
	// AnimationBoneData Bone = MainRenderer->GetBoneData(_BoneIndex);
	// Bone.Pos;

	return Transform.GetWorldPosition();
}
