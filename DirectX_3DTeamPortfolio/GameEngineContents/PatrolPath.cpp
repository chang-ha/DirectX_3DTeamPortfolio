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

void PatrolPath::Init(const std::vector<float4>& _Paths, int _Index /*= 0*/, bool _IsOneWay /*= false*/)
{
	if (static_cast<int>(_Paths.size()) <= _Index)
	{
		CurIndex = 0;
	}
	if (1 == _Paths.size())
	{
		MsgBoxAssert("하나의 점으로 정찰을 진행할 수 없습니다.");
		return;
	}

	Paths = _Paths;
	bOneWay = _IsOneWay;

	ValidityCheck();
}

float4 PatrolPath::GetCurPath()
{
	ValidityCheck();
	return Paths.at(CurIndex);
}

static constexpr float CognizanceRange = 20.0f;

bool PatrolPath::IsArrive(const float4& _ActorPos) const
{
	float4 TargetPos = Paths.at(CurIndex);
	float4 ActorPos = _ActorPos;
	TargetPos.Y = 0.0f;
	ActorPos.Y = 0.0f;

	const float4 Dist = DirectX::XMVector3LengthEst((ActorPos - TargetPos).DirectXVector);
	if (Dist.X < CognizanceRange)
	{
		return true;
	}

	return false;
}

void PatrolPath::ChangePath()
{
	CurIndex += iDir;

	if (true == OverIndex())
	{
		if (true == bOneWay)
		{
			CurIndex = 0;
		}
		else
		{
			iDir *= -1;
			CurIndex += iDir * 2;
		}
	}
}

bool PatrolPath::OverIndex()
{
	const int PathSize = static_cast<int>(Paths.size());
	if (CurIndex < 0 || CurIndex >= PathSize)
	{
		return true;
	}

	return false;
}