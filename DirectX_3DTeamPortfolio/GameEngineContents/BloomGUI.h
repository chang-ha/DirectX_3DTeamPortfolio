#pragma once
#include "TreeWindow.h"

// Ό³Έν :
class BloomGUI : public TreeObject
{
public:
	// constrcuter destructer
	BloomGUI();
	~BloomGUI();

	// delete Function
	BloomGUI(const BloomGUI& _Other) = delete;
	BloomGUI(BloomGUI&& _Other) noexcept = delete;
	BloomGUI& operator=(const BloomGUI& _Other) = delete;
	BloomGUI& operator=(BloomGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

private:

	void Editor(class GameEngineLevel* _Level);
};

