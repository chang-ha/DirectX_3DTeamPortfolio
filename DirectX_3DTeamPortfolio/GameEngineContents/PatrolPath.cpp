#include "PreCompile.h"
#include "PatrolPath.h"

PatrolPath::PatrolPath() 
{
}

PatrolPath::~PatrolPath() 
{
}

void PatrolPath::ValidityCheck(std::string_view _MSG)
{
	int Size = static_cast<int>(Paths.size());
	if (0 == Size
		|| Size <= CurIndex)
	{
		if (_MSG.empty())
		{
			MsgBoxAssert("경로의 Index가 잘못된 값이 들어왔습니다.");
		}
		else
		{
			MsgBoxAssert(_MSG.data());
		}
	}
}

void PatrolPath::Init(const std::vector<float4>& _Paths, int _Index /*= 0*/)
{
	if (static_cast<int>(_Paths.size()) <= _Index)
	{
		CurIndex = 0;
	}

	Paths = _Paths;

	ValidityCheck();
}

float4 PatrolPath::GetNextPath(const float4& _ActorPos)
{
	if (true == IsArrive(_ActorPos))
	{
		ChangePath();
	}

	ValidityCheck();

	return Paths.at(CurIndex);
}

bool PatrolPath::IsArrive(const float4& _ActorPos) const
{
	float4 PathPos = Paths.at(CurIndex);
	float4 ActorPos = _ActorPos;
	PathPos.Y = 0.0f;
	ActorPos.Y = 0.0f;

	const float4 Dist = DirectX::XMVector2LengthEst((ActorPos - PathPos).DirectXVector);
	return (Dist.X < CognizanceRange);
}

void PatrolPath::ChangePath()
{
	++CurIndex;
	int Size = static_cast<int>(Paths.size());
	if (Size <= CurIndex)
	{
		CurIndex = 0;
	}
}