#pragma once
#include "TreeWindow.h"

// Ό³Έν :
class DummyGUI : public TreeObject
{
public:
	// constrcuter destructer
	DummyGUI();
	~DummyGUI();

	// delete Function
	DummyGUI(const DummyGUI& _Other) = delete;
	DummyGUI(DummyGUI&& _Other) noexcept = delete;
	DummyGUI& operator=(const DummyGUI& _Other) = delete;
	DummyGUI& operator=(DummyGUI&& _Other) noexcept = delete;


protected:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

	void HelpString();

private:
	class DummyActor* pActor = nullptr;
	bool bUpdate = false;
	bool bCameraControl = false;

};