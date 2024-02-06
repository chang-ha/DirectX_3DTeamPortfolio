#pragma once


enum class Enum_InputDirection
{
	CENTER,
	UP,
	RIGHTUP,
	RIGHT,
	RIGHTDOWN,
	DOWN,
	LEFTDOWN,
	LEFT,
	LEFTUP,
};

enum class Enum_HORIZONTAL_KEY_STATE
{
	Left,
	Center,
	Right,
};


enum class Enum_VERTICAL_KEY_STATE
{
	Up,
	Center,
	Down,
};

// Ό³Έν :
class ContentsControlInput
{
public:
	// constrcuter destructer
	ContentsControlInput();
	~ContentsControlInput();

	// delete Function
	ContentsControlInput(const ContentsControlInput& _Other) = delete;
	ContentsControlInput(ContentsControlInput&& _Other) noexcept = delete;
	ContentsControlInput& operator=(const ContentsControlInput& _Other) = delete;
	ContentsControlInput& operator=(ContentsControlInput&& _Other) noexcept = delete;

	float4 GetInputVector();

	inline void SetPointer(void* _p)
	{
		pParent = _p;
	}

protected:
	float4 DetectMovement();
	bool DetectVerticalMovement();
	bool DetectHorizontalMovement();
	

private:
	void* pParent = nullptr;
	Enum_HORIZONTAL_KEY_STATE HorizontalInputKey = Enum_HORIZONTAL_KEY_STATE::Center;
	Enum_VERTICAL_KEY_STATE VerticalInputKey = Enum_VERTICAL_KEY_STATE::Center;

};

