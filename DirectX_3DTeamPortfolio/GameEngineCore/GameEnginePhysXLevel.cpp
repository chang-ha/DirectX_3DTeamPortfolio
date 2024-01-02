#include "PreCompile.h"
#include "GameEnginePhysXLevel.h"

physx::PxScene* GameEnginePhysXLevel::CurScene;

GameEnginePhysXLevel::GameEnginePhysXLevel()
{
}

GameEnginePhysXLevel::~GameEnginePhysXLevel()
{

}

void GameEnginePhysXLevel::PhysXLevelInit()
{
	Scene = GameEnginePhysX::CreateLevelScene();
}

void GameEnginePhysXLevel::RunSimulation(float _Delta)
{
	if (0.0f >= _Delta)
	{
		return;
	}

	Scene->simulate(_Delta);
	Scene->fetchResults(true);
}
