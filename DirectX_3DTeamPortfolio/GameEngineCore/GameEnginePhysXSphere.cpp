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

}

void GameEnginePhysXSphere::Release()
{

}

void GameEnginePhysXSphere::PhysXComponentInit(float _Radius, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler();

	physx::PxShape* Sphereshape = Physics->createShape(physx::PxSphereGeometry(10), *_Material);

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform Transform(Pos, Quat);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*Sphereshape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 10.0f);

	Scene->addActor(*ComponentActor);

	Sphereshape->release();
}
