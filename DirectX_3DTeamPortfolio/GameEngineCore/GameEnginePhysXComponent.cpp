#include "PreCompile.h"
#include "GameEnginePhysXComponent.h"


GameEnginePhysXComponent::GameEnginePhysXComponent()
{

}

GameEnginePhysXComponent::~GameEnginePhysXComponent()
{

}

void GameEnginePhysXComponent::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXComponent::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXComponent::Start()
{
	Scene = GameEnginePhysX::FindScene(GetLevel()->GetName());
}

void GameEnginePhysXComponent::Update(float _Delta)
{
	
}

void GameEnginePhysXComponent::Release()
{

}