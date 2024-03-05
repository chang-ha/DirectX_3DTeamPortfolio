#pragma once


class BSCol_TransitionParameter
{
public:
	BSCol_TransitionParameter() {}
	~BSCol_TransitionParameter() {}
	BSCol_TransitionParameter(const float4& _S, const float4& _Q, const float4& _T)
		:S(_S), Q(_Q), T(_T)
	{

	}


	float4 S = float4::ONE;
	float4 Q = float4::ZERONULL;
	float4 T = float4::ZERO;
};

