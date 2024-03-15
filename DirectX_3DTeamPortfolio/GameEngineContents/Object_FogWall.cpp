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

	if (nullptr == DetectCollision)
	{

	}
}

void Object_FogWall::Update(float _Delta)
{

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

