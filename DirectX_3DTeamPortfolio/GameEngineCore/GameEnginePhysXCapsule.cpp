﻿#include "PreCompile.h"
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
}

void GameEnginePhysXCapsule::Release()
{
	if (nullptr != CapsuleShape)
	{
		CapsuleShape->release();
		CapsuleShape = nullptr;
	}

	if (nullptr != ComponentActor)
	{
		ComponentActor->release();
		ComponentActor = nullptr;
	}
}

void GameEnginePhysXCapsule::PhysXComponentInit(float _Radius, float _HalfHeight, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	// Before Init Set Transform
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldDeg = Transform.GetWorldRotationEuler();
	
	CapsuleShape = Physics->createShape(physx::PxCapsuleGeometry(_Radius, _HalfHeight), *_Material); // 캡슐이 똑바로 서있는 모양은 1/4Pi 만큼 회전 필요

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	// WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	// Basically RayCastTarget is Off
	CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	// Pivot to Bottom
	physx::PxVec3 Pivot = { 0, 0.0f + _Radius * 0.5f + _HalfHeight , 0 };
	CapsuleShape->setLocalPose(physx::PxTransform(Pivot, physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1))));

	physx::PxTransform Transform(Pos, Quat);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*CapsuleShape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 0.01f);
	ComponentActor->setMassSpaceInertiaTensor(physx::PxVec3(0.f));

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

/*
physx::PxForceMode
eFORCE == unit of mass * distance/ time^2, i.e. a force
eIMPULSE  == unit of mass * distance /time
eVELOCITY_CHANGE  == unit of distance / time, i.e. the effect is mass independent: a velocity change. // ignore mass
eACCELERATION  == unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.
*/

void GameEnginePhysXCapsule::ResetMove(int _Axies)
{
	physx::PxVec3 CurLV = ComponentActor->getLinearVelocity();

	if (Enum_Axies::X & _Axies)
	{
		CurLV.x = 0.0f;
	}

	if (Enum_Axies::Y & _Axies)
	{
		CurLV.y = 0.0f;
	}

	if (Enum_Axies::Z & _Axies)
	{
		CurLV.z = 0.0f;
	}

	ComponentActor->setLinearVelocity({ CurLV.x, CurLV.y, CurLV.z });
	// ComponentActor->clearForce(physx::PxForceMode::eFORCE);
}

void GameEnginePhysXCapsule::SetMaxSpeed(float _MaxSpeed)
{
	ComponentActor->setMaxLinearVelocity(_MaxSpeed);
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

void GameEnginePhysXCapsule::GravityOn()
{
	ComponentActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, false);
}

void GameEnginePhysXCapsule::GravityOff()
{
	ComponentActor->setActorFlag(physx::PxActorFlag::eDISABLE_GRAVITY, true);
}

void GameEnginePhysXCapsule::RayCastTargetOn()
{
	ComponentActor->detachShape(*CapsuleShape);
	CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, true);
	ComponentActor->attachShape(*CapsuleShape);
}

void GameEnginePhysXCapsule::RayCastTargetOff()
{
	ComponentActor->detachShape(*CapsuleShape);
	CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	ComponentActor->attachShape(*CapsuleShape);
}

void GameEnginePhysXCapsule::CollisionOn(bool _GravityOn /*= true*/)
{
	ComponentActor->detachShape(*CapsuleShape);
	CapsuleShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	ComponentActor->attachShape(*CapsuleShape);

	if (true == _GravityOn)
	{
		GravityOn();
	}
}

void GameEnginePhysXCapsule::CollisionOff(bool _GravityOff /*= true*/)
{
	ComponentActor->detachShape(*CapsuleShape);
	CapsuleShape->setFlag(physx::PxShapeFlag::eSIMULATION_SHAPE, false);
	ComponentActor->attachShape(*CapsuleShape);

	if (true == _GravityOff)
	{
		GravityOff();
	}
}