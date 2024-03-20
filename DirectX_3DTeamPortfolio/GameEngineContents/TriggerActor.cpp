#include "PreCompile.h"
#include "TriggerActor.h"

TriggerActor::TriggerActor() 
{
}

TriggerActor::~TriggerActor() 
{
}

void TriggerActor::Start()
{
	EventCollision = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::Trigger);
	EventCollision->SetCollisionType(ColType::AABBBOX3D);
	EventCollision->SetCollisionColor(float4::BLUE);
}

void TriggerActor::Release()
{
	EventCollision = nullptr;
}

void TriggerActor::Trigger()
{
	if (nullptr != Event)
	{
		Event();
	}

	Off();
}

void TriggerActor::SetWorldPosition(const float4& _Pos)
{
	EventCollision->Transform.SetWorldPosition(_Pos);
}

void TriggerActor::SetWorldScale(const float4& _Scale)
{
	EventCollision->Transform.SetWorldScale(_Scale);
}