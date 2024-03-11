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

	Capsule_02 = CreateComponent<GameEnginePhysXCapsule>();


}

void CameraCapsule::Update(float _Delta)
{
	Capsule->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition() });
	Capsule->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler()});

	Capsule_02->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition() });
	Capsule_02->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });

}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(20.0f, 20.0f);
	Capsule->SetPositioningComponent();
	Capsule->SetFiltering(Enum_CollisionOrder::Camera, Enum_CollisionOrder::Player);

	Capsule_02->PhysXComponentInit(60.0f, 60.0f);
	Capsule_02->SetFiltering(Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Player);

	

}
