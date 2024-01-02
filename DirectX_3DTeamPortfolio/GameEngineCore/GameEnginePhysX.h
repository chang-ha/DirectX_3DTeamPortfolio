#pragma once

#include <PxPhysicsAPI.h>

#define SCENE_MAX_ACTOR 512
#define GRAVITY_FORCE 98.0f

#define PVD_HOST "127.0.0.1"	//Set this to the IP address of the system running the PhysX Visual Debugger that you want to connect to.

class PhysXErrorCallback : public physx::PxErrorCallback
{
private:
	void reportError(physx::PxErrorCode::Enum code, const char* message, const char* file, int line) override
	{
		std::string ErrorResult = "Error : ";
		switch (code)
		{
		case physx::PxErrorCode::eNO_ERROR:
			ErrorResult += "No Error";
			break;
		case physx::PxErrorCode::eDEBUG_INFO:
			ErrorResult += "An informational message.";
			break;
		case physx::PxErrorCode::eDEBUG_WARNING:
			ErrorResult += "a warning message for the user to help with debugging";
			break;
		case physx::PxErrorCode::eINVALID_PARAMETER:
			ErrorResult += "method called with invalid parameter(s)";
			break;
		case physx::PxErrorCode::eINVALID_OPERATION:
			ErrorResult += "method was called at a time when an operation is not possible";
			break;
		case physx::PxErrorCode::eOUT_OF_MEMORY:
			ErrorResult += "method failed to allocate some memory";
			break;
		case physx::PxErrorCode::eINTERNAL_ERROR:
			ErrorResult += "The library failed for some reason.\nPossibly you have passed invalid values like NaNs, which are not checked for.";
			break;
		case physx::PxErrorCode::eABORT:
			ErrorResult += "An unrecoverable error, execution should be halted and log output flushed";
			break;
		case physx::PxErrorCode::ePERF_WARNING:
			ErrorResult += "The SDK has determined that an operation may result in poor performance.";
			break;
		case physx::PxErrorCode::eMASK_ALL:
			ErrorResult += "A bit mask for including all errors";
			break;
		default:
			MsgBoxAssert("존재하지 않는 ErrorCode입니다.");
			break;
		}

		ErrorResult += "\nMessage : " + std::string(message);
		ErrorResult += "\nPath : " + std::string(file);
		ErrorResult += "\nLine : " + std::to_string(line);

		MsgBoxAssert(ErrorResult);
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
	static physx::PxScene* CreateLevelScene();

	static inline  physx::PxPhysics* GetPhysics()
	{
		return Physics;

	}

	static inline  physx::PxMaterial* GetDefaultMaterial()
	{
		return Material;
	}

	static physx::PxScene* FindScene(std::string_view _SceneName);
protected:

private:
	static PhysXErrorCallback  ErrorCallback;
	static physx::PxDefaultAllocator  DefaultAllocatorCallback;
	static physx::PxFoundation* Foundation;
	static physx::PxPvd* Pvd;
	static physx::PxPhysics* Physics;
	static physx::PxCooking* Cooking;
	static physx::PxDefaultCpuDispatcher* CpuDispatcher;
	static physx::PxMaterial* Material;

	static std::map<std::string, physx::PxScene*> AllLevelScene;
};