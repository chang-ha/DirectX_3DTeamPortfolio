#include "PreCompile.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXLevel::GameEnginePhysXLevel()
{
}

GameEnginePhysXLevel::~GameEnginePhysXLevel()
{
	Release();
}

void GameEnginePhysXLevel::PhysXLevelInit()
{
	Scene = GameEnginePhysX::CreateLevelScene();

	ControllerManager = PxCreateControllerManager(*Scene);
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

void GameEnginePhysXLevel::Release()
{
	if (nullptr != ControllerManager)
	{
		ControllerManager->release();
		ControllerManager = nullptr;
	}
}
