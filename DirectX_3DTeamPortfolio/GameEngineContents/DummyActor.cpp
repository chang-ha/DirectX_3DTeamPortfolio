#include "PreCompile.h"
#include "DummyActor.h"


DummyActor::DummyActor() 
{
	GameEngineInput::AddInputObject(this);
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

	BodyCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Dummy);
	BodyCollision->SetCollisionType(ColType::SPHERE3D);

	ControlInput.SetPointer(this);

	Transform.SetLocalPosition(float4(0, 50, 0));
}

void DummyActor::Update(float _Delta)
{
	MoveUpdate(_Delta);
}

void DummyActor::Release()
{
	FbxRenderer = nullptr;
	BodyCollision = nullptr;

	BaseActor::Release();
}


void DummyActor::MoveUpdate(float _Delta)
{
	float4 DirVector = ControlInput.GetInputVector();
	Transform.AddLocalPosition(DirVector * Speed * _Delta);
}