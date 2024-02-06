#pragma once
#include "TreeWindow.h"


// Ό³Έν :
class LUTGUI : public TreeObject
{
public:
	// constrcuter destructer
	LUTGUI();
	~LUTGUI();

	// delete Function
	LUTGUI(const LUTGUI& _Other) = delete;
	LUTGUI(LUTGUI&& _Other) noexcept = delete;
	LUTGUI& operator=(const LUTGUI& _Other) = delete;
	LUTGUI& operator=(LUTGUI&& _Other) noexcept = delete;

protected:
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;


private:
	void LUTEditor(class GameEngineLevel* _Level);


	std::vector<const char*> CObjectNames;
};

