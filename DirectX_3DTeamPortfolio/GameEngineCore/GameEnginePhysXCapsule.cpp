#include "PreCompile.h"
#include "GameEnginePhysXCapsule.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXCapsule::GameEnginePhysXCapsule()
{

}

GameEnginePhysXCapsule::~GameEnginePhysXCapsule()
{

}

void GameEnginePhysXCapsule::Start()
{
	GameEnginePhysXComponent::Start();
}

void GameEnginePhysXCapsule::Update(float _Delta)
{
	GameEnginePhysXComponent::Update(_Delta);

	physx::PxVec3 Vec = CapsuleActor->getLinearVelocity();

	float VecScale = Vec.magnitude();
	if (0.5f < VecScale && -0.5f < Vec.y)
	{
		ChangeMaterial(GameEnginePhysX::GetConstClimbMaterial());
	}
	else
	{
		ChangeMaterial(GameEnginePhysX::GetConstDefaultMaterial());
	}
}

void GameEnginePhysXCapsule::Release()
{
	GameEnginePhysXComponent::Release();
}

void GameEnginePhysXCapsule::PhysXComponentInit(float _Radius, float _HalfHeight, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	// Before Init Set Transform
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldDeg = Transform.GetWorldRotationEuler();
	
	Shape = Physics->createShape(physx::PxCapsuleGeometry(_Radius, _HalfHeight), *_Material); // 캡슐이 똑바로 서있는 모양은 1/4Pi 만큼 회전 필요

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	// WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	// Basically RayCastTarget is Off
	Shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	// Pivot to Bottom
	physx::PxVec3 Pivot = { 0, 0.0f + _Radius * 1.f + _HalfHeight , 0 };
	Shape->setLocalPose(physx::PxTransform(Pivot, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1))));

	physx::PxTransform Transform(Pos, Quat);
	CapsuleActor = Physics->createRigidDynamic(Transform);
	CapsuleActor->attachShape(*Shape);
	physx::PxRigidBodyExt::updateMassAndInertia(*CapsuleActor, 0.01f);
	CapsuleActor->setMassSpaceInertiaTensor(physx::PxVec3(0.f));

	ComponentActor = CapsuleActor;

	// 축 고정 기능 (추후 필요시 사용)
	// ComponentActor->setRigidDynamicLockFlags
	// (
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z
	// );

	Scene->lockWrite();
	Scene->addActor(*ComponentActor);
	Scene->unlockWrite();
	// CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	// CapsuleShape->release();
}

float4 GameEnginePhysXCapsule::GetLinearVelocity_f()
{
	physx::PxVec3 Vector = GetLinearVelocity();

	float4 Result = float4(Vector.x, Vector.y, Vector.z);

	return Result;
}