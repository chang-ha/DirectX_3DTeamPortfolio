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
	Renderer->Transform.SetLocalPosition(float4(100.0f, 0.0f, 0.0f ));
	Renderer->Transform.SetLocalScale(float4(50.0f, 50.0f, 50.0f));
	Renderer->Transform.SetLocalRotation(float4(0.0f, 0.0f, -90.0f));

	Renderer->CreateFBXAnimation("DH_Aiming", "c1280_DH_Aiming.fbx", { AnimationInter , true });
	Renderer->CreateFBXAnimation("Idle_RH_Guarding", "c1280_Idle_RH_Guarding.fbx", { AnimationInter , true });
	Renderer->CreateFBXAnimation("Idle_Sit", "c1280_Idle_Sit.fbx", { AnimationInter , true });
	Renderer->CreateFBXAnimation("Idle_Standing", "c1280_Idle_Standing.fbx", { AnimationInter , true });
	Renderer->CreateFBXAnimation("Idle_Standing2", "c1280_Idle_Standing2.fbx", {AnimationInter , true});
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
}