#include "PreCompile.h"
#include "Boss_Vordt.h"


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

		BossFBXRenderer->SetFBXMesh("Mesh_Vordt.FBX", "FBXTexture"); // Bone 136
		// BossFBXRenderer->Transform.SetLocalScale({ 50.0f, 50.0f, 50.0f });
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

		BossFBXRenderer->CreateFBXAnimation("Breath", "Breath.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step1", "Combo1_Step1.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step2", "Combo1_Step2.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Combo1_Step3", "Combo1_Step3.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Combo2_Step1", "Combo2_Step1.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Combo2_Step2", "Combo2_Step2.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Death", "Death.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Death_Groggy", "Death_Groggy.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit&Sweep", "Hit&Sweep.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_001", "Hit_001.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_002", "Hit_002.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_003_Left", "Hit_003_Left.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_003_Right", "Hit_003_Right.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_004_Groggy", "Hit_004_Groggy.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_001", "Hit_Down_001.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_002", "Hit_Down_002.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_003", "Hit_Down_003.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_004", "Hit_Down_004.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_005", "Hit_Down_005.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Down_006", "Hit_Down_006.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Hit_Groggy", "Hit_Groggy.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Howling", "Howling.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Idle", "Idle.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Back", "Jump_Back.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Left", "Jump_Left.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Jump_Right", "Jump_Right.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Hit&Turn&Rush", "Rush&Hit&Turn&Rush.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Hit&Turn", "Rush&Hit&Turn.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush&Turn", "Rush&Turn.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Attack", "Rush_Attack.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Attack_002", "Rush_Attack_002.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Rush_Front", "Rush_Front.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep&Sweep", "Sweep&Sweep.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep_001", "Sweep_001.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Sweep_002", "Sweep_002.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Thrust", "Thrust.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Left", "Turn_Left.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Left_Twice", "Turn_Left_Twice.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Right", "Turn_Right.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Turn_Right_Twice", "Turn_Right_Twice.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Front", "Walk_Front.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Left", "Walk_Left.FBX", { 0.05f, true });
		BossFBXRenderer->CreateFBXAnimation("Walk_Right", "Walk_Right.FBX", { 0.05f, true });
		BossFBXRenderer->ChangeAnimation("Turn_Left");
	}

	{
		if (nullptr == BossCollision)
		{
			BossCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);
		}
		BossCollision->SetCollisionType(ColType::SPHERE2D);
		BossCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}
}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}

void Boss_Vordt::Start()
{

}

void Boss_Vordt::Update(float _Delta)
{
	BossState.Update(_Delta);
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
}