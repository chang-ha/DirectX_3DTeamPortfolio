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