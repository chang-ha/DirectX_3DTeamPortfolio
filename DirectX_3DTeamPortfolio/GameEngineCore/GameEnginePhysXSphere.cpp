#include "PreCompile.h"
#include "GameEnginePhysXSphere.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXSphere::GameEnginePhysXSphere()
{

}

GameEnginePhysXSphere::~GameEnginePhysXSphere()
{

}

void GameEnginePhysXSphere::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXSphere::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXSphere::Start()
{
	GameEnginePhysXComponent::Start();
	ParentActor = GetActor();
}

void GameEnginePhysXSphere::Update(float _Delta)
{
	physx::PxTransform Transform = ComponentActor->getGlobalPose();

	physx::PxVec3 ComponentPos = Transform.p;
	physx::PxQuat ComponentQuat = Transform.q;

	float4 ParentPos = {ComponentPos.x, ComponentPos.y, ComponentPos.z};
	float4 Degree = float4(ComponentQuat.x, ComponentQuat.y, ComponentQuat.z, 1.0f).QuaternionToEulerDeg();

	ParentActor->Transform.SetWorldPosition(ParentPos);
	ParentActor->Transform.SetWorldRotation(Degree);
}

void GameEnginePhysXSphere::Release()
{

}

void GameEnginePhysXSphere::PhysXComponentInit(float _Radius, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler().EulerDegToQuaternion();

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform Transform(Pos, Quat);

	physx::PxShape* Sphereshape = Physics->createShape(physx::PxSphereGeometry(_Radius), *_Material);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*Sphereshape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 0.001f);
	physx::PxReal Mass = ComponentActor->getMass();

	Scene->addActor(*ComponentActor);

	Sphereshape->release();
}

/*
physx::PxForceMode
eFORCE == unit of mass * distance/ time^2, i.e. a force
eIMPULSE  == unit of mass * distance /time
eVELOCITY_CHANGE  == unit of distance / time, i.e. the effect is mass independent: a velocity change.
eACCELERATION  == unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.
*/
void GameEnginePhysXSphere::MoveForce(const physx::PxVec3 _Force)
{
	physx::PxVec3 Speed = ComponentActor->getLinearVelocity();
	ComponentActor->setLinearVelocity({0, Speed.y, 0 });
	ComponentActor->addForce(_Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

void GameEnginePhysXSphere::AddForce(const physx::PxVec3 _Force)
{
	ComponentActor->addForce(_Force, physx::PxForceMode::eFORCE);
}
