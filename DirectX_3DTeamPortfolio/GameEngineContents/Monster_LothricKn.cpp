#include "PreCompile.h"
#include "Monster_LothricKn.h"


Monster_LothricKn::Monster_LothricKn() 
{
}

Monster_LothricKn::~Monster_LothricKn() 
{
}


void Monster_LothricKn::Start()
{
	if (nullptr == GameEngineFBXMesh::Find("c1280.fbx"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources\\Mesh\\Monster\\HighWall_LothricKnight");
		std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fbx" });
		for (GameEngineFile& pFile : Files)
		{
			GameEngineFBXMesh::Load(pFile.GetStringPath());
		}
	}


	BodyRenderer = CreateComponent<GameEngineFBXRenderer>();
	BodyRenderer->SetFBXMesh("c1280.fbx", "FBXTexture");
	BodyRenderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	BodyRenderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));

	BodyRenderer->CreateFBXAnimation("Idle", "Ani002.fbx", {0.1f, true}, 0);
	BodyRenderer->ChangeAnimation("Idle");
}

void Monster_LothricKn::Update(float _Delta)
{
}


void Monster_LothricKn::Release()
{
	BodyRenderer = nullptr;
}

void Monster_LothricKn::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}