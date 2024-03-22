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

void UIHandler::ScaleUpdate(float _Delta, GameEngineSpriteRenderer* _pRenderer, void* _Pointer)
{
	if (nullptr == _Pointer)
	{
		MsgBoxAssert("Null포인터를 참조했습니다.");
		return;
	}

	float4 ImgScale = _pRenderer->GetAutoScaleRatio();

	const float Speed = 1.0f;
	const float AddValue = Speed * _Delta;
	if (true == GameEngineInput::IsPress(VK_LEFT, _Pointer))
	{
		const float4 Scale = ImgScale + float4(-1.0f, 0.0f) * AddValue;
		_pRenderer->SetAutoScaleRatio(Scale);
	}
	if (true == GameEngineInput::IsPress(VK_RIGHT, _Pointer))
	{
		const float4 Scale = ImgScale + float4(1.0f, 0.0f) * AddValue;
		_pRenderer->SetAutoScaleRatio(Scale);
	}
	if (true == GameEngineInput::IsPress(VK_UP, _Pointer))
	{
		const float4 Scale = ImgScale + float4(0.0f, 1.0f) * AddValue;
		_pRenderer->SetAutoScaleRatio(Scale);
	}
	if (true == GameEngineInput::IsPress(VK_DOWN, _Pointer))
	{
		const float4 Scale = ImgScale + float4(0.0f, -1.0f) * AddValue;
		_pRenderer->SetAutoScaleRatio(Scale);
	}

	if (true == GameEngineInput::IsDown('K', _Pointer))
	{
		float4 ImgScale = _pRenderer->GetAutoScaleRatio();
		ContentsDebug::OutputString("Tex Scale", ImgScale.ToString());
	}
}