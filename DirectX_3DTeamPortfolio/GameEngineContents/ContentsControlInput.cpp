#include "PreCompile.h"
#include "ContentsControlInput.h"

// #define _ArrowInput 1
#if defined(_ArrowInput)
#define MYINPUT_LEFT VK_LEFT
#define MYINPUT_UP VK_UP
#define MYINPUT_DOWN VK_DOWN
#define MYINPUT_RIGHT VK_RIGHT
#else
#define MYINPUT_LEFT 'A'
#define MYINPUT_UP 'W'
#define MYINPUT_DOWN 'S'
#define MYINPUT_RIGHT 'D'
#endif


ContentsControlInput::ContentsControlInput() 
{
}

ContentsControlInput::~ContentsControlInput() 
{
}

float4 ContentsControlInput::GetInputVector()
{
	if (nullptr == pParent)
	{
		MsgBoxAssert("부모를 알지 못하면 사용할수 없는 기능입니다.");
		return float4::ZERO;
	}

	return DetectMovement();
}

float4 ContentsControlInput::DetectMovement()
{
	bool isVeritcalInput = DetectVerticalMovement();
	bool isHorizontalInput = DetectHorizontalMovement();

	if (true == isVeritcalInput || true == isHorizontalInput)
	{
		if (Enum_HORIZONTAL_KEY_STATE::Center == HorizontalInputKey)
		{
			if (Enum_VERTICAL_KEY_STATE::Down == VerticalInputKey)
			{
				return float4(0.0f,0.0f, -1.0f);
			}
			else
			{
				return float4(0.0f, 0.0f, 1.0f);
			}
		}
		else if (Enum_HORIZONTAL_KEY_STATE::Left == HorizontalInputKey)
		{
			if (Enum_VERTICAL_KEY_STATE::Down == VerticalInputKey)
			{
				return float4(-1.0f, 0.0f, -1.0f).NormalizeReturn();
			}
			else if (Enum_VERTICAL_KEY_STATE::Up == VerticalInputKey)
			{
				return float4(-1.0f, 0.0f, 1.0f).NormalizeReturn();
			}
			else
			{
				return float4(-1.0f, 0.0f, 0.0f);
			}
		}
		else
		{
			if (Enum_VERTICAL_KEY_STATE::Down == VerticalInputKey)
			{
				return float4(1.0f, 0.0f, -1.0f).NormalizeReturn();
			}
			else if (Enum_VERTICAL_KEY_STATE::Up == VerticalInputKey)
			{
				return float4(1.0f, 0.0f, 1.0f).NormalizeReturn();
			}
			else
			{
				return float4(1.0f, 0.0f, 0.0f);
			}
		}
	}

	return float4(0.0f, 0.0f, 0.0f);
}


bool ContentsControlInput::DetectVerticalMovement()
{
	VerticalInputKey = Enum_VERTICAL_KEY_STATE::Center;

	bool isPressUp = false;
	bool isPressDown = false;

	bool isMoveVertical = false;

	if (true == GameEngineInput::IsPress(MYINPUT_UP, pParent))
	{
		isPressUp = true;
		isMoveVertical = true;
	}

	if (true == GameEngineInput::IsPress(MYINPUT_DOWN, pParent))
	{
		isPressDown = true;
		isMoveVertical = true;
	}

	if (true == isMoveVertical && true == isPressUp && true == isPressDown)
	{
		isMoveVertical = false;
	}

	if (true == isMoveVertical)
	{
		if (true == isPressUp)
		{
			VerticalInputKey = Enum_VERTICAL_KEY_STATE::Up;
		}

		if (true == isPressDown)
		{
			VerticalInputKey = Enum_VERTICAL_KEY_STATE::Down;
		}
	}

	return isMoveVertical;
}


bool ContentsControlInput::DetectHorizontalMovement()
{
	HorizontalInputKey = Enum_HORIZONTAL_KEY_STATE::Center;

	bool isPressLeft = false;
	bool isPressRight = false;

	bool isMoveHorizontal = false;

	if (true == GameEngineInput::IsPress(MYINPUT_LEFT, pParent))
	{
		isPressLeft = true;
		isMoveHorizontal = true;
	}

	if (true == GameEngineInput::IsPress(MYINPUT_RIGHT, pParent))
	{
		isPressRight = true;
		isMoveHorizontal = true;
	}

	if (true == isPressLeft && true == isPressRight)
	{
		isMoveHorizontal = false;
	}

	if (true == isMoveHorizontal)
	{
		if (true == isPressLeft)
		{
			HorizontalInputKey = Enum_HORIZONTAL_KEY_STATE::Left;
		}

		if (true == isPressRight)
		{
			HorizontalInputKey = Enum_HORIZONTAL_KEY_STATE::Right;
		}
	}

	return isMoveHorizontal;
}
