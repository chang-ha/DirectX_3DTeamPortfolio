#include "PreCompile.h"
#include "ContentsMath.h"

ContentsMath::ContentsMath() 
{
}

ContentsMath::~ContentsMath() 
{
}

float ContentsMath::GetDegreeTo2f(float _X, float _Y)
{
	return std::atan2f(_X, _Y) * GameEngineMath::R2D;
}

float ContentsMath::GetDegreeTo2f(const float4& _Vec)
{
	return GetDegreeTo2f(_Vec.X, _Vec.Y);
}

float4 ContentsMath::GetVectorToOther(const float4& _MyPos, const float4& _OtherPos)
{
	return _OtherPos - _MyPos;
}

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////// 비트연산 //////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

bool BitMethod::IsOnFlag(int _Flag, int _iValue)
{
	return (_Flag / _iValue) % 2;
}

void BitMethod::SetFlag(int* _pFlag, int _iValue, bool _bOn)
{
	AddFlag(_pFlag, _iValue);

	if (false == _bOn)
	{
		(*_pFlag) -= _iValue;
	}
}

void BitMethod::AddFlag(int* _pFlag, int _iValue)
{
	(*_pFlag) |= _iValue;
}

void BitMethod::SubFlag(int* _pFlag, int _iValue)
{
	SetFlag(_pFlag, _iValue, false);
}