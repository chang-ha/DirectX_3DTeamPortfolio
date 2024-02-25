#pragma once


namespace ContentsDebug
{	
	void DistanceCheck(const float4& _f4Pos, float _fDist, const float4& _f4Color = float4::RED);

	template<typename DataType>
	void DebugOuput(DataType _Value, std::string_view _Title = nullptr)
	{
		std::string OutputStr;

		if (false == _Title.empty())
		{
			OutputStr = std::string(_Title.data()) + " : ";
		}

		OutputStr += std::to_string(_Value) + "\n";
		OutputDebugStringA(OutputStr.c_str());
	}
}