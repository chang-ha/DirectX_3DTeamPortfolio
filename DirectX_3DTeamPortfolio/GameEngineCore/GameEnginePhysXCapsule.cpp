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
	Positioning(_Delta);

	physx::PxVec3 Vec = CapsuleActor->getLinearVelocity();

	float VecScale = Vec.magnitude();
	if (0.1f < VecScale && -0.5f < Vec.y)
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
	if (nullptr != CapsuleActor)
	{
		CapsuleActor->release();
		CapsuleActor = nullptr;
	}
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

	Scene->addActor(*ComponentActor);
	// CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	// CapsuleShape->release();
}

void GameEnginePhysXCapsule::Positioning(float _Delta)
{
	switch (IsPositioningComponent)
	{
	case 0:
	{
		// Set MyPos to Reflect ParentPos
		const TransformData& LocalTransform = GameEngineObject::Transform.GetConstTransformDataRef();
		SetWorldPosition(LocalTransform.WorldPosition);
		SetWorldRotation(LocalTransform.WorldRotation);
		break;
	}
	default:
	{
		// Set ParentPos to Reflect MyPos
		// Component's Local Transform
		physx::PxTransform Transform = ComponentActor->getGlobalPose();
 		const TransformData& LocalTransform = GameEngineObject::Transform.GetConstTransformDataRef();

		physx::PxVec3 ComponentPos = Transform.p;
		physx::PxQuat ComponentQuat = Transform.q;

		float4 ParentPos = { ComponentPos.x, ComponentPos.y, ComponentPos.z , 1.0f };
		float4 Degree = float4(ComponentQuat.x, ComponentQuat.y, ComponentQuat.z, ComponentQuat.w).QuaternionToEulerDeg();
		// Degree.Z -= 90.0f; // 90도 만큼 회전한 캡슐을 고려

		ParentPos -= LocalTransform.LocalPosition; // Component Local Pos

		ParentActor->Transform.SetWorldRotation(Degree);
		ParentActor->Transform.SetWorldPosition(ParentPos);
		break;
	}
	}
}

float4 GameEnginePhysXCapsule::GetLinearVelocity_f()
{
	physx::PxVec3 Vector = GetLinearVelocity();

	float4 Result = float4(Vector.x, Vector.y, Vector.z);

	return Result;
}