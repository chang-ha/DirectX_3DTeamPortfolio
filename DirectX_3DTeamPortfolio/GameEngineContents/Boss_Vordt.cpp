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

}

void Boss_Vordt::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void Boss_Vordt::Start()
{
	// Boss Mesh
	{
		if (nullptr == GameEngineFBXMesh::Find("Mesh_Vordt.fbx"))
		{
			GameEngineFile File;
			File.MoveParentToExistsChild("ContentsResources");
			File.MoveChild("ContentsResources\\Mesh\\Boss\\Mesh_Vordt.fbx");
			std::shared_ptr<GameEngineFBXMesh> Mesh = GameEngineFBXMesh::Load(File.GetStringPath());
		}

		if (nullptr == BossFBXRenderer)
		{
			BossFBXRenderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
		}

		BossFBXRenderer->SetFBXMesh("Mesh_Vordt.FBX", "FBXTexture"); // Bone 136
		BossFBXRenderer->Transform.SetLocalScale({ 50.0f, 50.0f, 50.0f });
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
			std::shared_ptr<GameEngineFBXAnimation> Mesh = GameEngineFBXAnimation::Load(Files[i].GetStringPath());
		}

		BossFBXRenderer->CreateFBXAnimation("Run", "Ani_002.FBX", { 0.1f, true });
		BossFBXRenderer->ChangeAnimation("Run");
	}

	{
		BossCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::MonsterAttack);
		BossCollision->SetCollisionType(ColType::SPHERE2D);
		BossCollision->Transform.SetLocalScale({ 100.0f, 100.0f, 1.0f });
	}
}

void Boss_Vordt::Update(float _Delta)
{
	BossState.Update(_Delta);
}

void Boss_Vordt::Release()
{

}