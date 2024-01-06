#include "PreCompile.h"
#include "GameEnginePhysXCharacterController.h"
#include <GameEngineCore\GameEnginePhysXLevel.h>

GameEnginePhysXCharacterController::GameEnginePhysXCharacterController()
{

}

GameEnginePhysXCharacterController::~GameEnginePhysXCharacterController()
{

}

void GameEnginePhysXCharacterController::LevelStart(GameEngineLevel* _PrevLevel)
{

}

void GameEnginePhysXCharacterController::LevelEnd(GameEngineLevel* _NextLevel)
{

}

void GameEnginePhysXCharacterController::Start()
{
	GameEnginePhysXComponent::Start();
}

void GameEnginePhysXCharacterController::Update(float _Delta)
{
	GameEnginePhysXComponent::Update(_Delta);
	MoveCallTime += _Delta;

	physx::PxVec3 Gravity = { 0.0f, -9.8f * _Delta, 0.0f };
	Controller->move(Gravity, physx::PxF32(0.0f), MoveCallTime, nullptr);
	MoveCallTime = 0.0f;
}

void GameEnginePhysXCharacterController::Release()
{
	GameEnginePhysXComponent::Release();
}

void GameEnginePhysXCharacterController::PhysXComponentInit(
	float _Radius, 
	float _HalfHeight, 
	physx::PxMaterial* _Material/* = GameEnginePhysX::GetDefaultMaterial()*/)
{
	physx::PxPhysics* Physics = GameEnginePhysX::GetPhysics();

	float4 WolrdPos = Transform.GetWorldPosition();
	float4 WorldDeg = Transform.GetWorldRotationEuler();

	physx::PxExtendedVec3 Pos = { WolrdPos.X, WolrdPos.Y , WolrdPos.Z };

	// Create Controller
	physx::PxControllerManager* ControllerManager = CurPhysXLevel->GetControllerManager();

	physx::PxCapsuleControllerDesc Desc;
	Desc.material = _Material;
	Desc.climbingMode = physx::PxCapsuleClimbingMode::eCONSTRAINED;
	Desc.radius = _Radius;
	Desc.height = _HalfHeight * 2.0f;
	// Desc.stepOffset = 0.0f;
	Desc.stepOffset = Desc.height + Desc.radius * 1.9f;
	Desc.position = Pos;
	Desc.nonWalkableMode = physx::PxControllerNonWalkableMode::ePREVENT_CLIMBING;
	Desc.contactOffset = 0.5f;

	if (false == Desc.isValid())
	{
		MsgBoxAssert("Controller 생성에 실패했습니다. 인자값을 확인해주세요.");
	}

	Controller = ControllerManager->createController(Desc);
	physx::PxExtendedVec3 FootPos = Controller->getFootPosition();
}

void GameEnginePhysXCharacterController::Move(const physx::PxVec3 _Force)
{
	physx::PxVec3 Gravity = {0.0f, -9.8f, 0.0f};
	Controller->move(_Force + Gravity, physx::PxF32(0.0f), MoveCallTime, nullptr);
	MoveCallTime = 0.0f;
}