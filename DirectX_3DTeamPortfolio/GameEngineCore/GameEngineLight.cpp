#include "PreCompile.h"
#include "GameEngineLight.h"

GameEngineLight::GameEngineLight() 
{
}

GameEngineLight::~GameEngineLight() 
{
}

void GameEngineLight::Start()
{
	GetLevel()->PushLight(GetDynamic_Cast_This<GameEngineLight>());
}

void GameEngineLight::Update(float _DeltaTime)
{

}


void GameEngineLight::LightUpdate(GameEngineCamera* _Camera, float _DeltaTime)
{

}