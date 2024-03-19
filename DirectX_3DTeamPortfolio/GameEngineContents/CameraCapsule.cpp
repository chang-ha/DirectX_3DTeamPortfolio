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

	Capsule_02->SetWorldPosition({GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y - 40.0f ,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
	Capsule_02->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });

}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(30.0f, 30.0f);
	Capsule->GravityOff(); 
	Capsule->SetPositioningComponent();
	Capsule->SetFiltering(Enum_CollisionOrder::Camera, Enum_CollisionOrder::Player);

	Capsule_02->PhysXComponentInit(70.0f, 70.0f);

	Capsule_02->GravityOff();
	Capsule_02->SetPositioningComponent();
	Capsule_02->SetFiltering(Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Player);

	

}
