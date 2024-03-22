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

void ContentsDebug::OutputString(std::string_view _Title, std::string_view _Subject)
{
	std::string OutputStr;

	if (false == _Title.empty())
	{
		OutputStr = std::string(_Title.data()) + " : ";
	}

	OutputStr += std::string(_Subject.data()) + "\n";
	OutputDebugStringA(OutputStr.c_str());
}



void ContentsDebug::NUllCheck(void* _Pointer, std::string_view _MsgBox /*= ""*/)
{
#ifdef _DEBUG

	if (nullptr == _Pointer)
	{
		if (_MsgBox.empty())
		{
			MsgBoxAssert("포인터가 존재하지 않습니다.");
		}
		else
		{
			MsgBoxAssert(_MsgBox.data());
		}
	}
#endif // _DEBUG

}