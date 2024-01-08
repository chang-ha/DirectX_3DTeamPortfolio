#include "PreCompile.h"
#include "Boss_Vordt.h"

#define BOSS_ANI_SPEED 0.033f

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

		if (nullptr == BossFBXRenderer)
		{
			BossFBXRenderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
		}

		BossFBXRenderer->SetFBXMesh("Mesh_Vordt.FBX", "FBX_Animation"); // Bone 136
		BossFBXRenderer->Transform.SetLocalScale({ 10.0f, 10.0f, 10.0f });
		BossFBXRenderer->Transform.SetLocalRotation({ 0.0f, 0.0f, 180.0f });
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
		BossFBXRenderer->ChangeAnimation("Idle");
	}

	//// Boss Collision
	//{
	//	if (nullptr == BossCollision)
	//	{
	//		BossCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);
	//	}
	//	BossCollision->SetCollisionType(ColType::SPHERE2D);
	//	BossCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	//}

	Capsule = CreateComponent<GameEnginePhysXCapsule>();
	Capsule->Transform.SetLocalPosition({0.0f, 500.0f, 0.0f});
	Capsule->PhysXComponentInit(50.0f, 60.0f);
	Capsule->SetMaxSpeed(150.0f);
	Capsule->SetPositioningComponent();
	// Capsule->GravityOff();
	// Capsule->ResetMove(Enum_Axies::All);

	std::shared_ptr<GameEngineFBXRenderer> Renderer;
	Renderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
	Renderer->SetFBXMesh("SmallMap.fbx", "FBXStaticColor");
	
	TriMesh = CreateComponent<GameEnginePhysXTriMesh>();
	TriMesh->Transform.SetLocalPosition({0.0f, 0.0f, 800.0f});
	TriMesh->PhysXComponentInit("SmallMap.fbx");

}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Boss_Vordt::Start()
{
	GameEngineInput::AddInputObject(this);
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
		// Capsule->ResetForce();
	}

	if (true == GameEngineInput::IsPress('W', this))
	{
		Capsule->MoveForce({ 0.0f, 0.0f, SPEED, 0.0f });
	}

	if (true == GameEngineInput::IsPress('S', this))
	{
		Capsule->MoveForce({ 0.0f, 0.0f, -SPEED, 0.0f });
	}

	if (true == GameEngineInput::IsPress('A', this))
	{
		Capsule->MoveForce({ SPEED, 0.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsPress('D', this))
	{
		Capsule->MoveForce({ -SPEED, 0.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('Q', this))
	{
		Capsule->AddForce({ 0.0f, 0.0f, 1000.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		Capsule->AddForce({ 0.0f, 0.0f, -1000.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown(VK_SPACE, this))
	{
		Capsule->AddForce({ 0.0f, 2000.0f, 0.0f, 0.0f });
	}

	if (true == GameEngineInput::IsDown('V', this))
	{
		Capsule->SetWorldPosition({ 0.0f, 0.0f, 0.0f, 0.0f });
	}

	Capsule->RayCast({1.0f, }, 10.0f);

	physx::PxVec3 Vec = Capsule->GetLinearVelocity();
	std::string Result = "X : " + std::to_string(Vec.x) + " Y : " + std::to_string(Vec.y) + " Z : " + std::to_string(Vec.z) + "\n";
	OutputDebugString(Result.c_str());
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

	if (nullptr != TriMesh)
	{
		TriMesh->Death();
		TriMesh = nullptr;
	}
}