#pragma once

class ContentsRandom
{
public:
	static int GetSeed();
	static int RandomInt(int _iMin, int _iMax);
	static float Randomfloat(float _fMin, float _fMax);

private:
	static void AdjustSeed();

	ContentsRandom() {}
	~ContentsRandom() {}

	// delete Function
	ContentsRandom(const ContentsRandom& _Other) = delete;
	ContentsRandom(ContentsRandom&& _Other) noexcept = delete;
	ContentsRandom& operator=(const ContentsRandom& _Other) = delete;
	ContentsRandom& operator=(ContentsRandom&& _Other) noexcept = delete;

	static int Seed;
};

// Ό³Έν :
class ContentsMath
{
public:
	static float GetDegreeTo2f(float _X, float _Y);
	static float GetDegreeToVec2(const float4& _Vec);

	static float ClampDeg(float _D);

	static float4 GetVector3Length(const float4& _V);

protected:

private:
	// constrcuter destructer
	ContentsMath();
	~ContentsMath();

	// delete Function
	ContentsMath(const ContentsMath& _Other) = delete;
	ContentsMath(ContentsMath&& _Other) noexcept = delete;
	ContentsMath& operator=(const ContentsMath& _Other) = delete;
	ContentsMath& operator=(ContentsMath&& _Other) noexcept = delete;

};

class BitMethod
{
public:
	
	static bool IsOnFlag(int _Flag, int _iValue);
	static void SetFlag(int* _pFlag, int _iValue, bool _bOn);
	static void AddFlag(int* _pFlag, int _iValue);
	static void SubFlag(int* _pFlag, int _iValue);

private:
	BitMethod() {}
	~BitMethod() {}

	// delete Function
	BitMethod(const BitMethod& _Other) = delete;
	BitMethod(BitMethod&& _Other) noexcept = delete;
	BitMethod& operator=(const BitMethod& _Other) = delete;
	BitMethod& operator=(BitMethod&& _Other) noexcept = delete;

};

