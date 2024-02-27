#include "PreCompile.h"
#include "GameEnginePhysXComponent.h"
#include "GameEnginePhysXLevel.h"

GameEnginePhysXComponent::GameEnginePhysXComponent()
{

}

GameEnginePhysXComponent::~GameEnginePhysXComponent()
{

}

void GameEnginePhysXComponent::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXComponent::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXComponent::Start()
{
	CurPhysXLevel = dynamic_cast<GameEnginePhysXLevel*>(GetLevel());
	if (nullptr == CurPhysXLevel)
	{
		MsgBoxAssert("PhysX 객체는 PhysXLevel에서만 생성할 수 있습니다.");
		return;
	}

	Scene = CurPhysXLevel->GetScene();
	ParentActor = GetActor();
}

void GameEnginePhysXComponent::Update(float _Delta)
{
	
}

void GameEnginePhysXComponent::Release()
{
	if (nullptr != ComponentActor)
	{
		ComponentActor->release();
		ComponentActor = nullptr;
	}
}

/*
physx::PxForceMode
eFORCE == unit of mass * distance/ time^2, i.e. a force
eIMPULSE  == unit of mass * distance /time
eVELOCITY_CHANGE  == unit of distance / time, i.e. the effect is mass independent: a velocity change. // ignore mass
eACCELERATION  == unit of distance/ time^2, i.e. an acceleration. It gets treated just like a force except the mass is not divided out before integration.
*/

void GameEnginePhysXComponent::MoveForce(const physx::PxVec3 _Force, bool _IgnoreGravity/* = false*/)
{
	if (false == JudgeDynamic())
	{
		MsgBoxAssert("Dynamic객체만 움직일 수 있습니다.");
	}

	physx::PxRigidDynamic* DynamicActor = ComponentActor->is<physx::PxRigidDynamic>();

	physx::PxVec3 CurLV = physx::PxVec3({ 0.0f });
	if (false == _IgnoreGravity)
	{
		CurLV = DynamicActor->getLinearVelocity();
	}

	DynamicActor->setLinearVelocity({ _Force.x, _Force.y + CurLV.y, _Force.z }); // 현재 중력을 받아오기 위해
}

void GameEnginePhysXComponent::AddForce(const physx::PxVec3 _Force)
{
	if (false == JudgeDynamic())
	{
		MsgBoxAssert("Dynamic객체만 움직일 수 있습니다.");
	}
	physx::PxRigidDynamic* DynamicActor = ComponentActor->is<physx::PxRigidDynamic>();

	DynamicActor->addForce(_Force, physx::PxForceMode::eVELOCITY_CHANGE);
}

void GameEnginePhysXComponent::SetWorldPosition(const float4& _Pos)
{
	physx::PxVec3 Pos = { _Pos.X, _Pos.Y , _Pos.Z };

	float4 WorldDeg = Transform.GetWorldRotationEuler();
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	physx::PxTransform Transform(Pos, Quat);
	ComponentActor->setGlobalPose(Transform);
}

void GameEnginePhysXComponent::SetWorldRotation(const float4& _Degree)
{
	float4 WorldDeg = { _Degree.X, _Degree.Y , _Degree.Z };

	SetDir(WorldDeg.Y);

	physx::PxTransform Transform = ComponentActor->getGlobalPose();
	float4 WorldQuat = WorldDeg.EulerDegToQuaternion();
	physx::PxQuat Quat = physx::PxQuat(WorldQuat.X, WorldQuat.Y, WorldQuat.Z, WorldQuat.W);

	Transform.q = Quat;
	ComponentActor->setGlobalPose(Transform);
}

void GameEnginePhysXComponent::AddWorldRotation(const float4& _Degree)
{
	physx::PxTransform Transform = ComponentActor->getGlobalPose();
	physx::PxQuat Quat = Transform.q;
	float4 WorldDeg = { Quat.x, Quat.y, Quat.z, Quat.w };
	WorldDeg = WorldDeg.QuaternionToEulerDeg();
	WorldDeg += _Degree;
	if (0 > WorldDeg.X)
	{
		WorldDeg.X += 360.0f;
	}
	if (0 > WorldDeg.Y)
	{
		WorldDeg.Y += 360.0f;
	}
	if (0 > WorldDeg.Z)
	{
		WorldDeg.Z += 360.0f;
	}

	SetDir(WorldDeg.Y);

	WorldDeg = WorldDeg.EulerDegToQuaternion();

	Quat = physx::PxQuat(WorldDeg.X, WorldDeg.Y, WorldDeg.Z, WorldDeg.W);
	Transform.q = Quat;
	ComponentActor->setGlobalPose(Transform);
}

void GameEnginePhysXComponent::ResetMove(int _Axies)
{
	if (false == JudgeDynamic())
	{
		MsgBoxAssert("Dynamic객체만 움직일 수 있습니다.");
	}
	physx::PxRigidDynamic* DynamicActor = ComponentActor->is<physx::PxRigidDynamic>();

	physx::PxVec3 CurLV = DynamicActor->getLinearVelocity();

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

	DynamicActor->setLinearVelocity({ CurLV.x, CurLV.y, CurLV.z });
}

void GameEnginePhysXComponent::SetFiltering(int _CollisionOrder, int _TargetCollisionOrder)
{
	if (nullptr == ComponentActor)
	{
		MsgBoxAssert("Component를 Init후 사용해 주세요.");
	}

	physx::PxFilterData FilterData;
	FilterData.word0 = _CollisionOrder;
	FilterData.word1 = _TargetCollisionOrder;

	physx::PxU32 ShapeCount = ComponentActor->getNbShapes();
	
	if (0 >= ShapeCount)
	{
		return;
	}

	physx::PxShape** Shapes = (physx::PxShape**)malloc(sizeof(physx::PxShape*) * ShapeCount);

	ComponentActor->getShapes(Shapes, ShapeCount);

	for (physx::PxU32 i = 0; i < ShapeCount; i++)
	{
		physx::PxShape* CurShape = Shapes[i];
		ComponentActor->detachShape(*CurShape);
		CurShape->setSimulationFilterData(FilterData);
		ComponentActor->attachShape(*CurShape);
	}

	free(Shapes);
}

bool GameEnginePhysXComponent::JudgeDynamic()
{
	physx::PxType Type = ComponentActor->getConcreteType();

	if (physx::PxConcreteType::eRIGID_DYNAMIC != Type)
	{
		return false;
	}

	return true;
}
