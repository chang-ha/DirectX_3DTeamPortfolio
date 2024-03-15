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
	FogWallRenderer = CreateComponent<ContentsFogWallRenderer>();

	FogWallRenderer->Transform.SetLocalScale({ 600.0f,1000.0f,1.0f });
}

void Object_FogWall::Update(float _Delta)
{

}

