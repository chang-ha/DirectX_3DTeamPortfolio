#pragma once

class UIHandler
{
public:
	static void Update(float _Delta, GameEngineObject* _pObject, void* _Pointer);
	static void ScaleUpdate(float _Delta, GameEngineSpriteRenderer* _pRenderer, void* _Pointer);

private:

private:
		// constrcuter destructer
	UIHandler() {}
	~UIHandler() {}

	// delete Function
	UIHandler(const UIHandler& _Other) = delete;
	UIHandler(UIHandler&& _Other) noexcept = delete;
	UIHandler& operator=(const UIHandler& _Other) = delete;
	UIHandler& operator=(UIHandler&& _Other) noexcept = delete;
};