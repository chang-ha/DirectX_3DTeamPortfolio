#include "PreCompile.h"
#include "ContentsMouseInput.h"

ContentsMouseInput::ContentsMouseInput()
{
}

ContentsMouseInput::~ContentsMouseInput()
{
}

void ContentsMouseInput::InputUpdate()
{
	CurPos = GameEngineCore::MainWindow.GetMousePos();
	MovePos = PrevPos - CurPos;
	PrevPos = CurPos;
}

void ContentsMouseInput::Reset()
{
	float4 MousePos = GameEngineCore::MainWindow.GetMousePos();
	PrevPos = CurPos = MousePos;
	MovePos = float4::ZERO;
}