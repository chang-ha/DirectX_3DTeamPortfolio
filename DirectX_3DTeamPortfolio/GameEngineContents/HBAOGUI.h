#pragma once
#include "TreeWindow.h"


// Ό³Έν :
class HBAOGUI : public TreeObject
{
public:
	// constrcuter destructer
	HBAOGUI();
	~HBAOGUI();

	// delete Function
	HBAOGUI(const HBAOGUI& _Other) = delete;
	HBAOGUI(HBAOGUI&& _Other) noexcept = delete;
	HBAOGUI& operator=(const HBAOGUI& _Other) = delete;
	HBAOGUI& operator=(HBAOGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

private:

	void HBAOEditor(class GameEngineLevel* _Level);

};

