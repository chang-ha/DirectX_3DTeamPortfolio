#include "PreCompile.h"
#include "PatrolPath.h"

PatrolPath::PatrolPath() 
{
}

PatrolPath::~PatrolPath() 
{
}

void PatrolPath::Init(const std::vector<float4>& _Paths)
{
	Paths = _Paths;
}

float4 PatrolPath::GetNextPath(const float4& _ActorPos)
{

	return CurPath;
}

bool PatrolPath::IsArrive() const
{
	//float4 ActorPos = _ActorPos;
	//ActorPos.Y = 0.0f;

	//DirectX::XMVector2LengthEst(ActorPos - );
	//if (true)
	//{

	//}

	CognizanceRange;

	return false;
}

void PatrolPath::ChangePath()
{
	// CognizanceRange
}