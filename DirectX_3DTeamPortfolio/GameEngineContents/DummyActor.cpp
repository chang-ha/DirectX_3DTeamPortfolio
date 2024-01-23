#include "PreCompile.h"
#include "DummyActor.h"

DummyActor::DummyActor() 
{
}

DummyActor::~DummyActor() 
{
}



void DummyActor::Start()
{
	FbxRenderer = CreateComponent<GameEngineFBXRenderer>();
	FbxRenderer->SetMesh("Sphere");
	FbxRenderer->SetMaterial("FBXStaticColor");
	FbxRenderer->Transform.SetLocalScale(float4(100,100,100));
	FbxRenderer->Transform.SetLocalPosition(float4(0,50,0));

	DummyCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Dummy);
}

void DummyActor::Update(float _Delta)
{

}

void DummyActor::Release()
{
	FbxRenderer = nullptr;
}