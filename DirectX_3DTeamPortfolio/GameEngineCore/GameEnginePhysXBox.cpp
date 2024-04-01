#include "PreCompile.h"
#include "GameEnginePhysXBox.h"


GameEnginePhysXBox::GameEnginePhysXBox()
{

}

GameEnginePhysXBox::~GameEnginePhysXBox()
{

}

void GameEnginePhysXBox::Start()
{
	GameEnginePhysXComponent::Start();
}

void GameEnginePhysXBox::Update(float _Delta)
{
	GameEnginePhysXComponent::Update(_Delta);
}

void GameEnginePhysXBox::Release()
{
	GameEnginePhysXComponent::Release();
}

void GameEnginePhysXBox::PhysXComponentInit(float _hX, float _hY, float _hZ, bool _IsMovingBox /*= false*/, const physx::PxMaterial* _Material /*= GameEnginePhysX::GetDefaultMaterial()*/)
{
	if (nullptr != ComponentActor)
	{
		return;
	}

	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldQuat = Transform.GetWorldRotationEuler().EulerDegToQuaternion();

	Shape = Physics->createShape(physx::PxBoxGeometry(_hX, _hY, _hZ), *_Material);
	Shape->setFlag(physx::PxShapeFlag::eSCENE_QUERY_SHAPE, false);
	Material = (physx::PxMaterial* const*)_Material;

	physx::PxVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);
	physx::PxTransform Transform(Pos, Quat);
	if (false == _IsMovingBox)
	{
		ComponentActor = Physics->createRigidStatic(Transform);
	}
	else
	{
		physx::PxRigidDynamic* BoxActor = Physics->createRigidDynamic(Transform);
		BoxActor->setMassSpaceInertiaTensor(physx::PxVec3(0.f));

		ComponentActor = BoxActor;
	}


	ComponentActor->attachShape(*Shape);

	Scene->lockWrite();
	Scene->addActor(*ComponentActor);
	Scene->unlockWrite();
}