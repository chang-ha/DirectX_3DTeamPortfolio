#pragma once

// Ό³Έν :
class ContentsMouseInput
{
	friend class ContentsCore;

public:
	// constrcuter destructer
	ContentsMouseInput();
	~ContentsMouseInput();

	// delete Function
	ContentsMouseInput(const ContentsMouseInput& _Other) = delete;
	ContentsMouseInput(ContentsMouseInput&& _Other) noexcept = delete;
	ContentsMouseInput& operator=(const ContentsMouseInput& _Other) = delete;
	ContentsMouseInput& operator=(ContentsMouseInput&& _Other) noexcept = delete;

	static float4 GetMouseMovePos();

protected:
	static void Reset();
	static void InputUpdate();

private:
	static float4 PrevPos;
	static float4 MovePos;
	static float4 CurPos;

};

