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
	const TransformData& LocalTransform = GameEngineObject::Transform.GetConstTransformDataRef();
	SetWorldPosition(LocalTransform.WorldPosition);
	SetWorldRotation(LocalTransform.WorldRotation);
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
	ComponentActor = Physics->createRigidStatic(Transform);
	ComponentActor->attachShape(*Boxshape);

	Scene->addActor(*ComponentActor);

	Boxshape->release();
}