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
	if (nullptr != ComponentActor)
	{
		ComponentActor->release();
		ComponentActor = nullptr;
	}
}

void GameEnginePhysXSphere::PhysXComponentInit(float _Radius, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	if (nullptr != ComponentActor)
	{
		return;
	}

	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler().EulerDegToQuaternion();

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform Transform(Pos, Quat);

	physx::PxShape* Sphereshape = Physics->createShape(physx::PxSphereGeometry(_Radius), *_Material);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*Sphereshape);

	Scene->addActor(*ComponentActor);

	Sphereshape->release();
}