#include "PreCompile.h"
#include "ContentsDebug.h"


void ContentsDebug::DistanceCheck(const float4& _f4Pos, float _fDist, const float4& _f4Color/* = float4::RED*/)
{
#ifdef _DEBUG
	if (true == GameEngineLevel::IsDebug)
	{
		float4 MyPos = _f4Pos;
		GameEngineDebug::DrawSphere2D(float4(_fDist), float4::ZERO, MyPos);
	}
#endif // _DEBUG
}