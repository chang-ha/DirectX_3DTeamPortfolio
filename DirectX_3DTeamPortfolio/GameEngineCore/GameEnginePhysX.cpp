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
	mPvd = PxCreatePvd(*mFoundation);

	if (nullptr == mPvd)
	{
		MsgBoxAssert("Pvd 생성에 실패했습니다.");
	}

	// If Use PhysX Visual Debugger use this (NetWork)
	// Default listening port is 5425 
	// physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	//mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);

#endif

	physx::PxTolerancesScale Scale = physx::PxTolerancesScale(); // Default Length = 1(cm), Speed = 10(cm/s)

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

	// Scene Gravity
	SceneDesc.gravity = physx::PxVec3(0.0f, -GRAVITY_FORCE, 0.0f);
	physx::PxVec3 vec = SceneDesc.gravity;

	// FilterShader
	SceneDesc.filterShader = physx::PxDefaultSimulationFilterShader; // 추후 자체 함수 만들어서 포인터 넘길 예정
	
	// Set Scenes Limit Datas
	physx::PxSceneLimits SceneLimitsData = physx::PxSceneLimits();
	SceneLimitsData.maxNbActors = SCENE_MAX_ACTOR/*UINT32_MAX - 1*/;
	// SceneLimitsData.maxNbBodies = 0/*UINT32_MAX - 1*/;
	// SceneLimitsData.maxNbStaticShapes = 0;
	// SceneLimitsData.maxNbDynamicShapes = 0;
	// SceneLimitsData.maxNbAggregates = 0;
	// SceneLimitsData.maxNbConstraints = 0;
	SceneLimitsData.maxNbRegions = 255; // Maxmum 256
	// SceneLimitsData.maxNbBroadPhaseOverlaps = 0;
	
	SceneDesc.limits = SceneLimitsData;

	// Cpu Dispatcher
	CpuDispatcher = physx::PxDefaultCpuDispatcherCreate(0);

	if (nullptr == CpuDispatcher)
	{
		MsgBoxAssert("CpuDispatcher 생성에 실패했습니다.");
	}

	SceneDesc.cpuDispatcher = CpuDispatcher;

	physx::PxScene* Scene = mPhysics->createScene(SceneDesc);
	physx::PxMaterial* gMaterial = mPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	// Test Code
	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 2.0f);

	physx::PxRigidStatic* groundPlane = PxCreatePlane(*mPhysics, physx::PxPlane(0, 1, 0, 0), *gMaterial);
	Scene->addActor(*groundPlane);
	groundPlane->setGlobalPose({0.0f, 0.0f, 0.0f});

	//

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
