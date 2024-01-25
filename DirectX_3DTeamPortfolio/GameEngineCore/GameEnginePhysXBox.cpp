#include "PreCompile.h"
#include "GameEnginePhysXBox.h"


GameEnginePhysXBox::GameEnginePhysXBox()
{

}

GameEnginePhysXBox::~GameEnginePhysXBox()
{

}

void GameEnginePhysXBox::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXBox::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXBox::Start()
{
	GameEnginePhysXComponent::Start();
}

void GameEnginePhysXBox::Update(float _Delta)
{
	physx::PxTransform Transform = ComponentActor->getGlobalPose();

	physx::PxVec3 ComponentPos = Transform.p;
	physx::PxQuat ComponentQuat = Transform.q;

	float4 ParentPos = { ComponentPos.x, ComponentPos.y, ComponentPos.z };
	float4 Degree = float4(ComponentQuat.x, ComponentQuat.y, ComponentQuat.z, 1.0f).QuaternionToEulerDeg();

	ParentActor->Transform.SetWorldPosition(ParentPos);
	ParentActor->Transform.SetWorldRotation(Degree);
}

void GameEnginePhysXBox::Release()
{
	if (nullptr != ComponentActor)
	{
		ComponentActor->release();
		ComponentActor = nullptr;
	}
}

void GameEnginePhysXBox::PhysXComponentInit(float _hX, float _hY, float _hZ, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler().EulerDegToQuaternion();

	physx::PxShape* Boxshape = Physics->createShape(physx::PxBoxGeometry(_hX, _hY, _hZ), *_Material);

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform Transform(Pos, Quat);
	ComponentActor = Physics->createRigidDynamic(Transform);
	ComponentActor->attachShape(*Boxshape);
	physx::PxRigidBodyExt::updateMassAndInertia(*ComponentActor, 0.001f);
	physx::PxReal Mass = ComponentActor->getMass();

	Scene->addActor(*ComponentActor);

	Boxshape->release();
}