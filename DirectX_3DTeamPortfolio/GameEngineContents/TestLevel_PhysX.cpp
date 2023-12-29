#include "PreCompile.h"
#include "TestLevel_PhysX.h"


TestLevel_PhysX::TestLevel_PhysX()
{

}

TestLevel_PhysX::~TestLevel_PhysX()
{

}

void TestLevel_PhysX::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void TestLevel_PhysX::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void TestLevel_PhysX::Start()
{
	PhysXLevelInit();
	//// Test Code
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	//														정적마찰, 동적마찰, 복원
	//physx::PxMaterial* gMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);

	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 2.0f);

	// create simulation
	physx::PxMaterial* mMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);
}

void TestLevel_PhysX::Update(float _Delta)
{
	RunSimulation(_Delta);
}

void TestLevel_PhysX::Release()
{

}