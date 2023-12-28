#include "PreCompile.h"
#include "GameEnginePhysX.h"

PhysXErrorCallback  GameEnginePhysX::gErrorCallback = {};
physx::PxDefaultAllocator  GameEnginePhysX::gDefaultAllocatorCallback = {};
physx::PxFoundation* GameEnginePhysX::mFoundation = nullptr;
physx::PxPvd* GameEnginePhysX::mPvd = nullptr;
physx::PxPhysics* GameEnginePhysX::mPhysics = nullptr;
physx::PxCooking* GameEnginePhysX::mCooking = nullptr;

GameEnginePhysX::GameEnginePhysX()
{

}

GameEnginePhysX::~GameEnginePhysX()
{

}

void GameEnginePhysX::PhysXInit()
{
	mFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gErrorCallback);
	
	if (nullptr == mFoundation)
	{
		MsgBoxAssert("Foundation 생성에 실패했습니다.");
	}

	bool  RecordMemoryAllocations = true; // 메모리 프로파일 On

#ifdef _DEBUG
	//mPvd = PxCreatePvd(*mFoundation);

	//if (nullptr == mPvd)
	//{
	//	MsgBoxAssert("Pvd 생성에 실패했습니다.");
	//}

	// Default listening port is 5425 
	// physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	//mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

#endif

	physx::PxTolerancesScale Scale = physx::PxTolerancesScale(); // Default Length = 1cm, Speed = 10(1m/s)

	mPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *mFoundation, Scale, RecordMemoryAllocations, mPvd);

	if (nullptr == mPhysics)
	{
		MsgBoxAssert("Physics 생성에 실패했습니다.");
	}

	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, physx::PxCookingParams(Scale));

	if (nullptr == mCooking)
	{
		MsgBoxAssert("Cooking 생성에 실패했습니다.");
	}
}

void GameEnginePhysX::PhysXRelease()
{
	if (nullptr != mCooking)
	{
		mCooking->release();
		mCooking = nullptr;
	}

	if (nullptr != mPhysics)
	{
		mPhysics->release();
		mPhysics = nullptr;
	}

	if (nullptr != mPvd)
	{
		mPvd->release();
		mPvd = nullptr;
	}

	if (nullptr != mFoundation)
	{
		mFoundation->release();
		mFoundation = nullptr;
	}
}
