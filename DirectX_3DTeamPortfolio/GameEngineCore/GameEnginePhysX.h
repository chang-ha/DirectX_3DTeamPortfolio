#pragma once

#include <PxPhysicsAPI.h>

class PhysXErrorCallback : public physx::PxErrorCallback
{
private:
	void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
	{

	}
};

class GameEnginePhysX
{
public:
	// constructer destructer
	GameEnginePhysX();
	~GameEnginePhysX();

	// delete function
	GameEnginePhysX(const GameEnginePhysX& _Ohter) = delete;
	GameEnginePhysX(GameEnginePhysX&& _Ohter) noexcept = delete;
	GameEnginePhysX& operator=(const GameEnginePhysX& _Other) = delete;
	GameEnginePhysX& operator=(GameEnginePhysX&& _Other) noexcept = delete;

	static void PhysXInit();
	static void PhysXRelease();
protected:

private:
	static PhysXErrorCallback  gErrorCallback;
	static physx::PxDefaultAllocator  gDefaultAllocatorCallback;
	static physx::PxFoundation* mFoundation;

};