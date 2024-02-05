#include "PreCompile.h"
#include "ContentsMath.h"

int ContentsRandom::Seed = 0;
int ContentsRandom::RandomInt(int _iMin, int _iMax)
{
	if (_iMin > _iMax)
	{
		MsgBoxAssert("최소값은 최대값보다 클 수 없습니다.");
		return 0;
	}

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GetSeed());
	int iChance = RandomClass.RandomInt(_iMin, _iMax);
	return iChance;
}

float ContentsRandom::Randomfloat(float _fMin, float _fMax)
{
	if (_fMin > _fMax)
	{
		MsgBoxAssert("최소값은 최대값보다 클 수 없습니다.");
		return 0.0f;
	}

	GameEngineRandom RandomClass;
	RandomClass.SetSeed(GetSeed());
	float fChance = RandomClass.RandomFloat(_fMin, _fMax);
	return fChance;
}

int ContentsRandom::GetSeed()
{
	++Seed;
	AdjustSeed();
	return Seed;
}

void ContentsRandom::AdjustSeed()
{
	if (Seed < INT_MAX)
	{
		Seed = 0;
	}
}

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

float ContentsMath::GetDegreeToVec2(const float4& _Vec)
{
	return GetDegreeTo2f(_Vec.X, _Vec.Y);
}

float4 ContentsMath::GetVector3Length(const float4& _V)
{
	return DirectX::XMVector3Length(_V.DirectXVector);
}

float ContentsMath::ClampDeg(float _D)
{
	while (_D < 0.0f || _D >= 360.0f)
	{
		if (_D < 0.0f)
		{
			_D += 360.0f;
		}

		if (_D >= 360.0f)
		{
			_D -= 360.0f;
		}
	}

	return _D;
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