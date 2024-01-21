#include "PreCompile.h"
#include "Boss_Vordt.h"

#define BOSS_ANI_SPEED 0.033f

void Boss_State_GUI::Start()
{
	
}

void Boss_State_GUI::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
	if (nullptr == Linked_Boss)
	{
		return;
	}

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

		//if (nullptr == BossFBXRenderer)
		//{
		//	BossFBXRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
		//}

		BossFBXRenderer->SetFBXMesh("Mesh_Vordt.FBX", "FBX_Animation"); // Bone 136
		BossFBXRenderer->Transform.SetLocalScale({ 100.0f, 100.0f, 100.0f });
		BossFBXRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, -90.0f });
	}

	// Boss Animation
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Mesh\\Boss\\Animation");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" }, true);

		for (size_t i = 0; i < Files.size(); i++)
		{
			GameEngineFBXAnimation::Load(Files[i].GetStringPath());
		}

		BossFBXRenderer->CreateFBXAnimation("Breath", "Breath.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step1", "Combo1_Step1.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step2", "Combo1_Step2.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step3", "Combo1_Step3.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Combo2_Step1", "Combo2_Step1.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Combo2_Step2", "Combo2_Step2.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Death", "Death.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Death_Groggy", "Death_Groggy.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit&Sweep", "Hit&Sweep.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_001", "Hit_001.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_002", "Hit_002.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_003_Left", "Hit_003_Left.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_003_Right", "Hit_003_Right.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_004_Groggy", "Hit_004_Groggy.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_001", "Hit_Down_001.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_002", "Hit_Down_002.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_003", "Hit_Down_003.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_004", "Hit_Down_004.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_005", "Hit_Down_005.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_006", "Hit_Down_006.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Groggy", "Hit_Groggy.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Howling", "Howling.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Idle", "Idle.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Back", "Jump_Back.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Left", "Jump_Left.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Right", "Jump_Right.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Hit&Turn&Rush", "Rush&Hit&Turn&Rush.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Hit&Turn", "Rush&Hit&Turn.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Turn", "Rush&Turn.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Attack", "Rush_Attack.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Attack_002", "Rush_Attack_002.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Front", "Rush_Front.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep&Sweep", "Sweep&Sweep.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep_001", "Sweep_001.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep_002", "Sweep_002.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Thrust", "Thrust.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Left", "Turn_Left.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Left_Twice", "Turn_Left_Twice.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Right", "Turn_Right.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Right_Twice", "Turn_Right_Twice.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Front", "Walk_Front.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Left", "Walk_Left.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Right", "Walk_Right.FBX", { BOSS_ANI_SPEED, true });
		BossFBXRenderer->ChangeAnimation("Rush&Hit&Turn&Rush");
	}

	// Root Motion
	BossFBXRenderer->SetRootMotionComponent(Capsule.get());
	BossFBXRenderer->SetRootMotion("Breath");
	BossFBXRenderer->SetRootMotion("Combo1_Step1");
	BossFBXRenderer->SetRootMotion("Combo1_Step2");
	BossFBXRenderer->SetRootMotion("Combo1_Step3");
	BossFBXRenderer->SetRootMotion("Combo2_Step1");
	BossFBXRenderer->SetRootMotion("Combo2_Step2");
	BossFBXRenderer->SetRootMotion("Death");
	BossFBXRenderer->SetRootMotion("Death_Groggy");
	BossFBXRenderer->SetRootMotion("Hit&Sweep");
	BossFBXRenderer->SetRootMotion("Hit_001");
	BossFBXRenderer->SetRootMotion("Hit_002");
	BossFBXRenderer->SetRootMotion("Hit_003_Left");
	BossFBXRenderer->SetRootMotion("Hit_003_Right");
	BossFBXRenderer->SetRootMotion("Hit_004_Groggy");
	BossFBXRenderer->SetRootMotion("Hit_Down_001");
	BossFBXRenderer->SetRootMotion("Hit_Down_002");
	BossFBXRenderer->SetRootMotion("Hit_Down_003");
	BossFBXRenderer->SetRootMotion("Hit_Down_004");
	BossFBXRenderer->SetRootMotion("Hit_Down_005");
	BossFBXRenderer->SetRootMotion("Hit_Down_006");
	BossFBXRenderer->SetRootMotion("Hit_Groggy");
	BossFBXRenderer->SetRootMotion("Howling");
	BossFBXRenderer->SetRootMotion("Idle");
	BossFBXRenderer->SetRootMotion("Jump_Back");
	BossFBXRenderer->SetRootMotion("Jump_Left");
	BossFBXRenderer->SetRootMotion("Jump_Right");
	BossFBXRenderer->SetRootMotion("Rush&Hit&Turn&Rush");
	BossFBXRenderer->SetRootMotion("Rush&Hit&Turn");
	BossFBXRenderer->SetRootMotion("Rush&Turn");
	BossFBXRenderer->SetRootMotion("Rush_Attack");
	BossFBXRenderer->SetRootMotion("Rush_Attack_002");
	BossFBXRenderer->SetRootMotion("Rush_Front");
	BossFBXRenderer->SetRootMotion("Sweep&Sweep");
	BossFBXRenderer->SetRootMotion("Sweep_001");
	BossFBXRenderer->SetRootMotion("Sweep_002");
	BossFBXRenderer->SetRootMotion("Thrust");
	BossFBXRenderer->SetRootMotion("Turn_Left");
	BossFBXRenderer->SetRootMotion("Turn_Left_Twice");
	BossFBXRenderer->SetRootMotion("Turn_Right");
	BossFBXRenderer->SetRootMotion("Turn_Right_Twice");
	BossFBXRenderer->SetRootMotion("Walk_Front");
	BossFBXRenderer->SetRootMotion("Walk_Left");
	BossFBXRenderer->SetRootMotion("Walk_Right");

	//// Boss Collision
	{
		if (nullptr == BossCollision)
		{
			BossCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);
		}
		BossCollision->SetCollisionType(ColType::SPHERE3D);
		BossCollision->Transform.SetLocalScale({ 1.0f, 1.0f, 1.0f });
	}

	//if (nullptr == Capsule)
	//{
	//	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	//}
	Capsule->PhysXComponentInit(100.0f, 50.0f);
	// Capsule->SetMaxSpeed(150.0f);
	Capsule->SetPositioningComponent();
	// Capsule->GravityOff();


	GUI = GameEngineGUI::CreateGUIWindow<Boss_State_GUI>("Boss_State");
	GUI->Linked_Boss = this;

	CreateStateParameter Idle;
	Idle.Start = std::bind(&Boss_Vordt::IdleStart, this);
	Idle.Stay = std::bind(&Boss_Vordt::IdleUpdate, this, std::placeholders::_1);
	Idle.End = std::bind(&Boss_Vordt::IdleEnd, this);

	BossState.CreateState(Enum_BossState::Idle, Idle);
	BossState.ChangeState(Enum_BossState::Idle);
}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{
	GUI->Linked_Boss = nullptr;
	Death();
}

void Boss_Vordt::Start()
{
	GameEngineInput::AddInputObject(this);

	if (nullptr == BossFBXRenderer)
	{
		BossFBXRenderer = CreateComponent<GameContentsFBXRenderer>(Enum_RenderOrder::Monster);
	}

	if (nullptr == Capsule)
	{
		Capsule = CreateComponent<GameEnginePhysXCapsule>();
	}
}

#define SPEED 100.0f
void Boss_Vordt::Update(float _Delta)
{
	BossState.Update(_Delta);

	if (false == GameEngineInput::IsPress('W', this)
		&& false == GameEngineInput::IsPress('A', this)
		&& false == GameEngineInput::IsPress('S', this)
		&& false == GameEngineInput::IsPress('D', this))
	{
		// Capsule->ResetMove(Enum_Axies::X | Enum_Axies::Z);
	}

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
		// Capsule->SetWorldPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('B', this))
	{
		Capsule->CollisionOff();
		Capsule->ResetMove(Enum_Axies::All);
	}
}

void Boss_Vordt::Release()
{
	if (nullptr != BossFBXRenderer)
	{
		BossFBXRenderer->Death();
		BossFBXRenderer = nullptr;
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

}