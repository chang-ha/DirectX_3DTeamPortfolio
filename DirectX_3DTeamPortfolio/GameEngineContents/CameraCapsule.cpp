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
}

void CameraCapsule::LevelStart(GameEngineLevel* _PrevLevel)
{
}
