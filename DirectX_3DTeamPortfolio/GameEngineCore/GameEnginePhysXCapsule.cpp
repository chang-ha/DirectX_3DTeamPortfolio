#include "PreCompile.h"
#include "GameEnginePhysXCapsule.h"


GameEnginePhysXCapsule::GameEnginePhysXCapsule()
{

}

GameEnginePhysXCapsule::~GameEnginePhysXCapsule()
{

}

void GameEnginePhysXCapsule::Start()
{
	GameEnginePhysXComponent::Start();
	ParentActor = GetActor();
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
	WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	// Basically RayCastTarget is Off
	CapsuleShape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);

	physx::PxTransform Transform(Pos, Quat);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*CapsuleShape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 0.01f);
	ComponentActor->setMassSpaceInertiaTensor(physx::PxVec3(0.f));

	// Pivot Setting Test
	// physx::PxTransform Test1 = ComponentActor->getCMassLocalPose();
	// 
	// physx::PxVec3 Pivot = { 0, 0.0f - _Radius - _HalfHeight , 0 };
	// ComponentActor->setCMassLocalPose(physx::PxTransform(Pivot, Quat));
	// 
	// physx::PxTransform Test2 = ComponentActor->getCMassLocalPose();
	//

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
void GameEnginePhysXCapsule::MoveForce(const physx::PxVec3 _Force, bool _IgnoreGravity/* = false*/)
{
	physx::PxVec3 CurLV = physx::PxVec3({0.0f});
	if (false == _IgnoreGravity)
	{
		CurLV = ComponentActor->getLinearVelocity(); 
	}

	ComponentActor->setLinearVelocity({ _Force.x, _Force.y + CurLV.y, _Force.z }); // 현재 중력을 받아오기 위해
}

void GameEnginePhysXCapsule::AddForce(const physx::PxVec3 _Force)
{
	ComponentActor->addForce(_Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

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

bool GameEnginePhysXCapsule::RayCast(const float4& _Pos, const float4& _DirVector, float _MaxDisTance)
{
	physx::PxVec3 origin = ComponentActor->getGlobalPose().p + physx::PxVec3(_Pos.X, _Pos.Y, _Pos.Z);		 // [in] Ray origin
	physx::PxVec3 unitDir = physx::PxVec3({ _DirVector.X, _DirVector.Y, _DirVector.Z });                // [in] Normalized ray direction
	physx::PxReal maxDistance = _MaxDisTance;            // [in] Raycast max distance
	physx::PxRaycastBuffer hitResult;                 // [out] Raycast results

	// Raycast against all static & dynamic objects (no filtering)
	// The main result from this call is the closest hit, stored in the 'hit.block' structure
	bool status = Scene->raycast(origin, unitDir, maxDistance, hitResult);
	
	if (true ==  hitResult.hasBlock)
	{
		int a = 0;
	}

	if (true == status)
	{
		int a = 0;
	}

	return status;
}

void GameEnginePhysXCapsule::SetWorldPosition(const float4& _Pos)
{
	physx::PxVec3 Pos = { _Pos.X, _Pos.Y , _Pos.Z };

	float4 WorldDeg = Transform.GetWorldRotationEuler();
	WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	physx::PxTransform Transform(Pos, Quat);
	ComponentActor->setGlobalPose(Transform);
}

void GameEnginePhysXCapsule::SetWorldRotation(const float4& _Degree)
{
	float4 WorldDeg = { _Degree.X, _Degree.Y , _Degree.Z };

	physx::PxTransform Transform = ComponentActor->getGlobalPose();
	WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	Transform.q = Quat;
	ComponentActor->setGlobalPose(Transform);
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
		float4 Degree = float4(ComponentQuat.x, ComponentQuat.y, ComponentQuat.z, 1.0f).QuaternionToEulerDeg();
		Degree.Z -= 90.0f; // 90도 만큼 회전한 캡슐을 고려

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