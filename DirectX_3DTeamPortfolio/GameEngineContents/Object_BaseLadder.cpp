#include "PreCompile.h"
#include "Object_BaseLadder.h"
#include "GameContentsFBXRenderer.h"


Object_BaseLadder::Object_BaseLadder()
{	
}

Object_BaseLadder::~Object_BaseLadder()
{
}


void Object_BaseLadder::Start()
{

	
}

void Object_BaseLadder::Update(float _Delta)
{

}

float4 Object_BaseLadder::GetRotation()
{
	LadderRotation = this->Transform.GetWorldRotationEuler();
	return LadderRotation;
}