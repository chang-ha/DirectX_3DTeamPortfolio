#include "PreCompile.h"
#include "CameraCapsule.h"

CameraCapsule::CameraCapsule()
{
}

CameraCapsule::~CameraCapsule()
{
}

void CameraCapsule::Start()
{
	Capsule = CreateComponent<GameEnginePhysXCapsule>();

}

void CameraCapsule::Update(float _Delta)
{
	Capsule->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition() });
	Capsule->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler()});

}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(20.0f, 20.0f);
	Capsule->SetPositioningComponent();
	Capsule->SetFiltering(Enum_CollisionOrder::Camera, Enum_CollisionOrder::Map);

}
