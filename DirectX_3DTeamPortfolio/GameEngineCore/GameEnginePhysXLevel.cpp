#include "PreCompile.h"
#include "GameEnginePhysXLevel.h"

std::list<void*> GameEnginePhysXLevel::AllData;

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
	if (nullptr == Scene)
	{
		MsgBoxAssert("PhysX Scene 지우지 마세요.");
	}

	if (0.0f >= _Delta)
	{
		return;
	}

	Scene->simulate(1.f/60.f);
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

bool GameEnginePhysXLevel::RayCast(const float4& _Pos, const float4& _DirVector, float _MaxDisTance)
{
	float4 DirVector = _DirVector;
	DirVector.Normalize();
	physx::PxVec3 origin = physx::PxVec3(_Pos.X, _Pos.Y, _Pos.Z);	// Raycast Pos
	physx::PxVec3 unitDir = physx::PxVec3({ DirVector.X, DirVector.Y, DirVector.Z });	// Normalized ray direction
	physx::PxReal maxDistance = _MaxDisTance;            // Raycast max distance
	physx::PxRaycastBuffer hitResult;                 // Raycast results

	bool status = Scene->raycast(origin, unitDir, maxDistance, hitResult);
	return status;
}