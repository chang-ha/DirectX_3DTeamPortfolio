#pragma once
#include "TreeWindow.h"

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

	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

protected:
	void ActorCheck(GameEngineLevel* _Level);

private:
	std::shared_ptr<class DummyActor> pDummy;

	bool IsActive = false;
	bool IsCameraFocus = false;

};