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
		WallCollision->CollisionOff();
	}

	if (nullptr == DetectCollision)
	{
		// 해당 콜리전과 충돌 시 플레이어가 상호작용 가능
		DetectCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Detect);
		DetectCollision->Transform.SetLocalScale({10.f, 10.f, 10.f});
		DetectCollision->Transform.SetLocalPosition({0.f, -300.f, -20.f});
	}

	GameEngineInput::AddInputObject(this);
}

void Object_FogWall::Update(float _Delta)
{
	if (false == DetectCollision->Collision(Enum_CollisionOrder::Player_Body))
	{
		return;
	}

	if (true == GameEngineInput::IsDown('E', this))
	{
		// // 플레이어 애니메이션 쪽에서 하기
		// // 들어가는 애니메이션 시작 시 
		// GameEnginePhysX::PushSkipCollisionPair(2, Enum_CollisionOrder::Player, Enum_CollisionOrder::Fog_Wall);
		// // 들어가는 애니메이션 끝날 시
		// GameEnginePhysX::PopSkipCollisionPair(2, Enum_CollisionOrder::Player, Enum_CollisionOrder::Fog_Wall);
	}
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
}

