#include "PreCompile.h"
#include "UI_Utils.h"


void UIHandler::Update(float _Delta, GameEngineObject* _pObject, void* _Pointer)
{
	if (nullptr == _Pointer)
	{
		MsgBoxAssert("Null포인터를 참조했습니다.");
		return;
	}

	const float MoveSpeed = 100.0f;
	const float MoveForce = MoveSpeed * _Delta;
	if (true == GameEngineInput::IsPress(VK_LEFT, _Pointer))
	{
		_pObject->Transform.AddWorldPosition(float4::LEFT * MoveForce);
	}
	if (true == GameEngineInput::IsPress(VK_RIGHT, _Pointer))
	{
		_pObject->Transform.AddWorldPosition(float4::RIGHT * MoveForce);
	}
	if (true == GameEngineInput::IsPress(VK_UP, _Pointer))
	{
		_pObject->Transform.AddWorldPosition(float4::UP * MoveForce);
	}
	if (true == GameEngineInput::IsPress(VK_DOWN, _Pointer))
	{
		_pObject->Transform.AddWorldPosition(float4::DOWN * MoveForce);
	}

	if (true == GameEngineInput::IsDown('K', _Pointer))
	{
		float4 TexwPos = _pObject->Transform.GetWorldPosition();
		ContentsDebug::OutputString("Tex Pos", TexwPos.ToString());
	}
}