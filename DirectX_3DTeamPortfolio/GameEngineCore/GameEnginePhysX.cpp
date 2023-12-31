#include "PreCompile.h"
#include "GameEnginePhysX.h"

PhysXErrorCallback  GameEnginePhysX::gErrorCallback = {};
physx::PxDefaultAllocator  GameEnginePhysX::gDefaultAllocatorCallback = {};
physx::PxFoundation* GameEnginePhysX::mFoundation = nullptr;
physx::PxPvd* GameEnginePhysX::mPvd = nullptr;
physx::PxPhysics* GameEnginePhysX::mPhysics = nullptr;
physx::PxCooking* GameEnginePhysX::mCooking = nullptr;
physx::PxDefaultCpuDispatcher* GameEnginePhysX::CpuDispatcher = nullptr;

std::map<std::string, physx::PxScene*> GameEnginePhysX::AllLevelScene;

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


	mCooking = PxCreateCooking(PX_PHYSICS_VERSION, *mFoundation, physx::PxCookingParams(mPhysics->getTolerancesScale()));

	if (nullptr == mCooking)
	{
		MsgBoxAssert("Cooking 생성에 실패했습니다.");
	}
}

physx::PxScene* GameEnginePhysX::CreateLevelScene()
{
	std::string UpperName = GameEngineString::ToUpperReturn(GameEngineCore::GetCurLevel()->GetName());

	if (true == AllLevelScene.contains(UpperName))
	{
		return AllLevelScene[UpperName];
	}

	physx::PxSceneDesc SceneDesc = physx::PxSceneDesc(mPhysics->getTolerancesScale());

	SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader;
	
	// Set Scenes Limit Datas
	physx::PxSceneLimits SceneLimitsData = physx::PxSceneLimits();
	SceneLimitsData.maxNbActors = 512/*UINT32_MAX - 1*/;
	SceneLimitsData.maxNbBodies = 512/*UINT32_MAX - 1*/;
	SceneLimitsData.maxNbStaticShapes = 0;
	SceneLimitsData.maxNbDynamicShapes = 0;
	SceneLimitsData.maxNbAggregates = 0;
	SceneLimitsData.maxNbConstraints = 0;
	SceneLimitsData.maxNbRegions = 255; // Maxmum 256
	SceneLimitsData.maxNbBroadPhaseOverlaps = 0;
	
	SceneDesc.limits = SceneLimitsData;

	// Cpu Dispatcher
	CpuDispatcher = physx::PxDefaultCpuDispatcherCreate(0);
	SceneDesc.cpuDispatcher = CpuDispatcher;

	physx::PxScene* Scene = mPhysics->createScene(SceneDesc);

	AllLevelScene[UpperName] = Scene;
	return Scene;
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

	if (nullptr != CpuDispatcher)
	{
		CpuDispatcher->release();
		CpuDispatcher = nullptr;
	}

	if (nullptr != mFoundation)
	{
		mFoundation->release();
		mFoundation = nullptr;
	}
}
