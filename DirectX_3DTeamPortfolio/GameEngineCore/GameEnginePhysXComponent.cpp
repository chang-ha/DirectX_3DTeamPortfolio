#include "PreCompile.h"
#include "GameEnginePhysXComponent.h"
#include "GameEnginePhysXLevel.h"

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
	CurPhysXLevel = dynamic_cast<GameEnginePhysXLevel*>(GetLevel());
	if (nullptr == CurPhysXLevel)
	{
		MsgBoxAssert("PhysX 객체는 PhysXLevel에서만 생성할 수 있습니다.");
		return;
	}

	// Scene = GameEnginePhysX::FindScene(GetLevel()->GetName());
	Scene = CurPhysXLevel->GetScene();
}

void GameEnginePhysXComponent::Update(float _Delta)
{
	
}

void GameEnginePhysXComponent::Release()
{

}