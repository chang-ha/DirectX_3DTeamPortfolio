#include "PreCompile.h"
#include "Object_FogWall.h"
#include "ContentsFogWallRenderer.h"

Object_FogWall::Object_FogWall() 
{
}

Object_FogWall::~Object_FogWall()
{
}

void Object_FogWall::Start()
{
	if (nullptr == FogWallRenderer)
	{
		FogWallRenderer = CreateComponent<ContentsFogWallRenderer>();
		FogWallRenderer->Transform.SetLocalScale({ 600.0f,1000.0f,1.0f });
	}

	if (nullptr == WallCollision)
	{
		WallCollision = CreateComponent<GameEnginePhysXBox>(Enum_CollisionOrder::Fog_Wall);
		WallCollision->PhysXComponentInit(600.f, 1000.f, 3.f);
		WallCollision->SetFiltering(Enum_CollisionOrder::Fog_Wall);
	}

	if (nullptr == InDetectCollision)
	{
		// 해당 콜리전과 충돌 시 플레이어가 상호작용 가능
		InDetectCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Fog_Wall);
		InDetectCollision->Transform.SetLocalScale({20.f, 20.f, 20.f});
		InDetectCollision->Transform.SetLocalPosition({0.f, -350.f, -30.f});
	}

	if (nullptr == OutDetectCollision)
	{
		OutDetectCollision = CreateComponent<GameEngineCollision> (Enum_CollisionOrder::Fog_Wall);
		OutDetectCollision->Transform.SetLocalScale({ 20.f, 20.f, 20.f });
		OutDetectCollision->Transform.SetLocalPosition({ 0.f, -350.f, 30.f });
	}

	GameEngineInput::AddInputObject(this);
}

void Object_FogWall::Update(float _Delta)
{
	OutDetect();
}

void Object_FogWall::Release()
{
	if (nullptr != FogWallRenderer)
	{
		FogWallRenderer->Death();
		FogWallRenderer = nullptr;
	}

	if (nullptr != WallCollision)
	{
		WallCollision->Death();
		WallCollision = nullptr;
	}

	if (nullptr != InDetectCollision)
	{
		InDetectCollision->Death();
		InDetectCollision = nullptr;
	}

	if (nullptr != OutDetectCollision)
	{
		OutDetectCollision->Death();
		OutDetectCollision = nullptr;
	}
}
void Object_FogWall::OutDetect()
{
	if (false == OutDetectCollision->IsUpdate())
	{
		return;
	}

	if (false == OutDetectCollision->Collision(Enum_CollisionOrder::Player_Body))
	{
		return;
	}

	InDetectCollision->Off();
	OutDetectCollision->Off();
	Start_Boss();
}
