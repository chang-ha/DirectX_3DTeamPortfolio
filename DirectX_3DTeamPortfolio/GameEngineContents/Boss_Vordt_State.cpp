#include "PreCompile.h"
#include "Boss_Vordt.h"

void Boss_Vordt::Idle_Start()
{
	int a = 0;
}

void Boss_Vordt::Idle_Update(float _Delta)
{
	int a = 0;
}

void Boss_Vordt::Idle_End()
{
	int a = 0;
}

void Boss_Vordt::Hit_Down_004_Start()
{
	BossFBXRenderer->ChangeAnimation("Hit_Down_004");
}

void Boss_Vordt::Hit_Down_004_Update(float _Delta)
{
	// Capsule->AddWorldRotation({0.f, 50.f * _Delta, 0.f, 0.f});
}

void Boss_Vordt::Hit_Down_004_End()
{

}