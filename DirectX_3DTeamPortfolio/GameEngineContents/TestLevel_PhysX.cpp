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
	ContentLevel::LevelStart(_PrevLevel);
}

void TestLevel_PhysX::LevelEnd(GameEngineLevel* _NextLevel)
{
	ContentLevel::LevelEnd(_NextLevel);
}

void TestLevel_PhysX::Start()
{
	ContentLevel::Start();
	//// Test Code
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();
	//														정적마찰, 동적마찰, 복원
	//physx::PxMaterial* gMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);

	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eSCALE, 1.0f);
	Scene->setVisualizationParameter(physx::PxVisualizationParameter::eACTOR_AXES, 2.0f);

	// create simulation
	physx::PxMaterial* mMaterial = Physics->createMaterial(0.5f, 0.5f, 0.6f);
	// Ground
	physx::PxRigidStatic* groundPlane = PxCreatePlane(*Physics, physx::PxPlane(0, 1, 0, 50), *mMaterial);
	Scene->addActor(*groundPlane);

	// Box
	float halfExtent = 10.5f;
	physx::PxShape* Boxshape = Physics->createShape(physx::PxBoxGeometry(halfExtent, halfExtent, halfExtent), *mMaterial);
	physx::PxShape* Sphereshape = Physics->createShape(physx::PxSphereGeometry(10), *mMaterial);
	physx::PxShape* CapsuleShape = Physics->createShape(physx::PxCapsuleGeometry(5, 20), *mMaterial); // 캡슐이 똑바로 서있는 모양은 1/4Pi 만큼 회전 필요
	physx::PxTransform t(physx::PxVec3(0));
	physx::PxQuat Quat = physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1));
	physx::PxTransform localTm(physx::PxVec3(0.0f, 3.0f, -100.0f), Quat);
	physx::PxRigidDynamic* DynamicActor = Physics->createRigidDynamic(localTm);
	DynamicActor->attachShape(*CapsuleShape);
	physx::PxRigidBodyExt::updateMassAndInertia(*DynamicActor, 10.0f);
	Scene->addActor(*DynamicActor);

	//physx::PxRigidStatic* StaticActor = Physics->createRigidStatic(localTm);
	//StaticActor->attachShape(*CapsuleShape);
	//Scene->addActor(*StaticActor);

	// physx::PxU32 size = 30;
	//for (physx::PxU32 i = 0; i < size; i++) {
	//	for (physx::PxU32 j = 0; j < size - i; j++) {
	//		physx::PxTransform localTm(physx::PxVec3(physx::PxReal(j * 2) - physx::PxReal(size - i), physx::PxReal(i * 2 + 1), 0) * halfExtent);
	//		physx::PxRigidDynamic* body = Physics->createRigidDynamic(t.transform(localTm));
	//		body->attachShape(*shape);
	//		physx::PxRigidBodyExt::updateMassAndInertia(*body, 10.0f);
	//		Scene->addActor(*body);
	//	}
	//}

	Boxshape->release();
	Sphereshape->release();
	CapsuleShape->release();

}

void TestLevel_PhysX::Update(float _Delta)
{
	ContentLevel::Update(_Delta);
}

void TestLevel_PhysX::Release()
{

}