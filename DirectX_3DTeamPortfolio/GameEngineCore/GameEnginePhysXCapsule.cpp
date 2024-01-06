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
	physx::PxTransform Transform = ComponentActor->getGlobalPose();

	physx::PxVec3 ComponentPos = Transform.p;
	physx::PxQuat ComponentQuat = Transform.q;

	float4 ParentPos = { ComponentPos.x, ComponentPos.y, ComponentPos.z };
	float4 Degree = float4(ComponentQuat.x, ComponentQuat.y, ComponentQuat.z, 1.0f).QuaternionToEulerDeg();

	ParentActor->Transform.SetWorldPosition(ParentPos);
	ParentActor->Transform.SetWorldRotation(Degree);

	RayCastUpdate();
}

void GameEnginePhysXCapsule::Release()
{

}

void GameEnginePhysXCapsule::PhysXComponentInit(float _Radius, float _HalfHeight, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldDeg = Transform.GetWorldRotationEuler();
	
	physx::PxShape* CapsuleShape = Physics->createShape(physx::PxCapsuleGeometry(_Radius, _HalfHeight), *_Material); // 캡슐이 똑바로 서있는 모양은 1/4Pi 만큼 회전 필요

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	WorldDeg.Z += physx::PxHalfPi * GameEngineMath::R2D;
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxQuat RotQuat = physx::PxQuat(physx::PxHalfPi, physx::PxVec3(0, 0, 1));

	physx::PxTransform Transform(Pos, Quat);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*CapsuleShape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 0.01f);
	physx::PxReal Mass = ComponentActor->getMass();
	ComponentActor->setMassSpaceInertiaTensor(physx::PxVec3(0.f));

	// Pivot Setting Test
	physx::PxTransform Test1 = ComponentActor->getCMassLocalPose();

	physx::PxVec3 Pivot = { 0, 0.0f - _Radius - _HalfHeight , 0 };
	ComponentActor->setCMassLocalPose(physx::PxTransform(Pivot, Quat));

	physx::PxTransform Test2 = ComponentActor->getCMassLocalPose();
	//

	// ComponentActor->setRigidDynamicLockFlags
	// (
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_X |
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Y |
	// 	physx::PxRigidDynamicLockFlag::eLOCK_ANGULAR_Z
	// );

	Scene->addActor(*ComponentActor);
	CapsuleShape->release();
}

/*
physx::PxForceMode
eFORCE == unit of mass * distance/ time^2, i.e. a force
eIMPULSE  == unit of mass * distance /time
eVELOCITY_CHANGE  == unit of distance / time, i.e. the effect is mass independent: a velocity change. // ignore mass
eACCELERATION  == unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.
*/
void GameEnginePhysXCapsule::MoveForce(const physx::PxVec3 _Force)
{
	// physx::PxVec3 Speed = ComponentActor->getLinearVelocity();
	// ComponentActor->setLinearVelocity({ 0, Speed.y, 0 });
	ComponentActor->addForce(_Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

void GameEnginePhysXCapsule::AddForce(const physx::PxVec3 _Force)
{
	ComponentActor->addForce(_Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

void GameEnginePhysXCapsule::ResetForce()
{
	physx::PxVec3 Speed = ComponentActor->getLinearVelocity();
	ComponentActor->setLinearVelocity({ 0, Speed.y, 0 });
	// ComponentActor->clearForce(physx::PxForceMode::eFORCE);
}

void GameEnginePhysXCapsule::RayCastUpdate()
{
	Scene;

	float4 WolrdPos = Transform.GetWorldPosition();
	physx::PxVec3 origin = ComponentActor->getGlobalPose().p;		 // [in] Ray origin
	physx::PxVec3 unitDir = physx::PxVec3({0.0f, 0.0f, 1.0f});                // [in] Normalized ray direction
	physx::PxReal maxDistance = 0.1f;            // [in] Raycast max distance
	physx::PxRaycastBuffer hitResult;                 // [out] Raycast results

	// Raycast against all static & dynamic objects (no filtering)
	// The main result from this call is the closest hit, stored in the 'hit.block' structure
	bool status = Scene->raycast(origin, unitDir, maxDistance, hitResult);
	if (true == status)
	{
		int a = 0;
	}
}

