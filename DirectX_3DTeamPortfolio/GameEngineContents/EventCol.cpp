#include "PreCompile.h"
#include "EventCol.h"

EventCol::EventCol()
{
}

EventCol::~EventCol()
{
}

void EventCol::Start()
{
	Ev_Col = CreateComponent<GameEngineCollision>(Enum_CollisionOrder::EventCol);
	Ev_Col->SetCollisionType(ColType::AABBBOX3D);

}

void EventCol::Update(float _Delta)
{

}

void EventCol::SetWorldPosition(const float4& _Pos)
{
	Ev_Col->Transform.SetWorldPosition(_Pos);
}

void EventCol::SetWorldScale(const float4& _Scale)
{
	Ev_Col->Transform.SetWorldScale(_Scale);
}
