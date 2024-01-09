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

bool GameEnginePhysXLevel::RayCast(const float4& _Pos, const float4& _DirVector, float _MaxDisTance)
{
	float4 DirVector = _DirVector;
	DirVector.Normalize();
	physx::PxVec3 origin = physx::PxVec3(_Pos.X, _Pos.Y, _Pos.Z);		 // [in] Ray origin
	physx::PxVec3 unitDir = physx::PxVec3({ DirVector.X, DirVector.Y, DirVector.Z });                // [in] Normalized ray direction
	physx::PxReal maxDistance = _MaxDisTance;            // [in] Raycast max distance
	physx::PxRaycastBuffer hitResult;                 // [out] Raycast results

	// Raycast against all static & dynamic objects (no filtering)
	// The main result from this call is the closest hit, stored in the 'hit.block' structure
	bool status = Scene->raycast(origin, unitDir, maxDistance, hitResult);
	return status;
}