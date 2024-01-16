#pragma once

// Ό³Έν :
class ContentsMath
{
public:
	static float GetDegreeTo2f(float _X, float _Y);
	static float GetDegreeTo2f(const float4& _Vec);

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

