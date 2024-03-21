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

	//Capsule_02 = CreateComponent<GameEnginePhysXCapsule>();

	Capsule_02 = CreateComponent<GameEnginePhysXBox>();

}

void CameraCapsule::Update(float _Delta)
{
	
	Capsule_02->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z});
	Capsule_02->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });


	Capsule->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y ,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
	Capsule->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });
}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule->PhysXComponentInit(30.0f, 30.0f);
	Capsule->GravityOff(); 
	Capsule->SetPositioningComponent();
	Capsule->SetFiltering(Enum_CollisionOrder::Camera, Enum_CollisionOrder::Player);


	//Capsule_02 = CreateComponent<GameEnginePhysXBox>(Enum_CollisionOrder::Big_Camera);
	Capsule_02->PhysXComponentInit(60.f, 60.f, 60.f);
	//Capsule_02->SetPositioningComponent();
	Capsule_02->SetFiltering(Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Player);


}
