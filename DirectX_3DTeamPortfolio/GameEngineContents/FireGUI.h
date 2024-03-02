#pragma once
#include "TreeWindow.h"

// Ό³Έν :
class FireGUI : public TreeObject
{
public:
	// constrcuter destructer
	FireGUI();
	~FireGUI();

	// delete Function
	FireGUI(const FireGUI& _Other) = delete;
	FireGUI(FireGUI&& _Other) noexcept = delete;
	FireGUI& operator=(const FireGUI& _Other) = delete;
	FireGUI& operator=(FireGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

private:
	void ShowList(GameEngineLevel* _Level);
	void FireEditor();

	
};

