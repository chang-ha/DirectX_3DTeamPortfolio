#include "PreCompile.h"
#include "ContentsDebug.h"


void ContentsDebug::DistanceCheck(const float4& _f4Pos, float _fDist, const float4& _f4Color/* = float4::RED*/)
{
#ifdef _DEBUG
	if (true == GameEngineLevel::IsDebug)
	{
		GameEngineDebug::DrawSphere2D(float4(_fDist), float4::ZERO, _f4Pos, _f4Color);
	}
#endif // _DEBUG
}