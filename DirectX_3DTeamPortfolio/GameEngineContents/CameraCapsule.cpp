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
	Capsule_01 = CreateComponent<GameEnginePhysXBox>();

	//Capsule_02 = CreateComponent<GameEnginePhysXCapsule>();

	Capsule_02 = CreateComponent<GameEnginePhysXBox>();

}

void CameraCapsule::Update(float _Delta)
{
	
	Capsule_02->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z});
	Capsule_02->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });


	Capsule_01->SetWorldPosition({ GetLevel()->GetMainCamera()->Transform.GetWorldPosition().X,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Y ,GetLevel()->GetMainCamera()->Transform.GetWorldPosition().Z });
	Capsule_01->SetWorldRotation({ GetLevel()->GetMainCamera()->Transform.GetWorldRotationEuler() });
}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
	Capsule_01->PhysXComponentInit(50.f,50.0f,50.0f,true);
	Capsule_01->GravityOff();
	Capsule_01->SetPositioningComponent();
	Capsule_01->SetFiltering(Enum_CollisionOrder::Camera, Enum_CollisionOrder::Player);


	Capsule_02->PhysXComponentInit(80.f,80.0f,80.0f,true);
	Capsule_02->SetPositioningComponent();
	Capsule_02->SetFiltering(Enum_CollisionOrder::Big_Camera, Enum_CollisionOrder::Player);


}
