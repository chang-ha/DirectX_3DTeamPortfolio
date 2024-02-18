#pragma once
#include "TreeWindow.h"


// Ό³Έν :
class FogGUI : public TreeObject
{
public:
	// constrcuter destructer
	FogGUI();
	~FogGUI();

	// delete Function
	FogGUI(const FogGUI& _Other) = delete;
	FogGUI(FogGUI&& _Other) noexcept = delete;
	FogGUI& operator=(const FogGUI& _Other) = delete;
	FogGUI& operator=(FogGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;


private:
	void LUTEditor(class GameEngineLevel* _Level);

};

