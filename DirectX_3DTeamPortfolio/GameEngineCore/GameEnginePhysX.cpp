#include "PreCompile.h"
#include "GameEnginePhysX.h"

PhysXErrorCallback  GameEnginePhysX::gErrorCallback = {};
physx::PxDefaultAllocator  GameEnginePhysX::gDefaultAllocatorCallback = {};
physx::PxFoundation* GameEnginePhysX::mFoundation = nullptr;

GameEnginePhysX::GameEnginePhysX()
{

}

GameEnginePhysX::~GameEnginePhysX()
{

}

void GameEnginePhysX::PhysXInit()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gErrorCallback);
}

void GameEnginePhysX::PhysXRelease()
{
	mFoundation->release();
}
