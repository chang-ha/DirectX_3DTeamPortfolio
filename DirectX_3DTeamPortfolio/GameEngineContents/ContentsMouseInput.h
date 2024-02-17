#pragma once

// Ό³Έν :
class ContentsMouseInput
{
public:
	// constrcuter destructer
	ContentsMouseInput();
	~ContentsMouseInput();

	// delete Function
	ContentsMouseInput(const ContentsMouseInput& _Other) = delete;
	ContentsMouseInput(ContentsMouseInput&& _Other) noexcept = delete;
	ContentsMouseInput& operator=(const ContentsMouseInput& _Other) = delete;
	ContentsMouseInput& operator=(ContentsMouseInput&& _Other) noexcept = delete;

	inline float4 GetScreenMovePos() const
	{
		return MovePos;
	}

	void Reset();
	void InputUpdate();

protected:

private:
	float4 PrevPos;
	float4 MovePos;
	float4 CurPos;

};

