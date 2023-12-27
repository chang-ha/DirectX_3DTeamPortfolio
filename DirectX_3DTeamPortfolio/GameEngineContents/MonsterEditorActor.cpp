#include "PreCompile.h"
#include "MonsterEditorActor.h"

MonsterEditorActor::MonsterEditorActor() 
{
}

MonsterEditorActor::~MonsterEditorActor() 
{
}


void MonsterEditorActor::Start()
{
	Renderer = CreateComponent<GameEngineFBXRenderer>(Enum_RenderOrder::Monster);
	Renderer->SetFBXMesh("c1280.fbx", "FBXTexture");
	Renderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	Renderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));
}

void MonsterEditorActor::Update(float _Delta)
{

}

void MonsterEditorActor::Release()
{
	Renderer = nullptr;
}

void MonsterEditorActor::LevelEnd(class GameEngineLevel* _NextLevel)
{
	Death();
}