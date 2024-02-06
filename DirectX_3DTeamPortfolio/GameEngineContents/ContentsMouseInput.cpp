#include "PreCompile.h"
#include "ContentsMouseInput.h"

float4 ContentsMouseInput::PrevPos = float4::ZERO;
float4 ContentsMouseInput::MovePos = float4::ZERO;
float4 ContentsMouseInput::CurPos = float4::ZERO;
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

float4 ContentsMouseInput::GetMouseMovePos() 
{ 
	float4 Pos = MovePos;
	Pos.Y *= -1.0f;
	return Pos;
}