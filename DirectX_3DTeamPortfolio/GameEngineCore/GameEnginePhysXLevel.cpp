#include "PreCompile.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXLevel::GameEnginePhysXLevel()
{
	Scene = GameEnginePhysX::CreateLevelScene();
}

GameEnginePhysXLevel::~GameEnginePhysXLevel()
{

}

void GameEnginePhysXLevel::RunSimulation(float _Delta)
{
	if (0.0f <= _Delta)
	{
		return;
	}

	Scene->simulate(_Delta);
	Scene->fetchResults(true);
}
