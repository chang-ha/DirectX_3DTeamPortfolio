#pragma once

// Ό³Έν :
class ContentsAO
{
public:
	// constrcuter destructer
	ContentsAO();
	~ContentsAO();

	// delete Function
	ContentsAO(const ContentsAO& _Other) = delete;
	ContentsAO(ContentsAO&& _Other) noexcept = delete;
	ContentsAO& operator=(const ContentsAO& _Other) = delete;
	ContentsAO& operator=(ContentsAO&& _Other) noexcept = delete;

protected:

private:

};

