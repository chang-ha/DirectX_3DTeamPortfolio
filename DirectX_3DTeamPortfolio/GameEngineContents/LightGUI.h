#pragma once
#include "TreeWindow.h"


// Ό³Έν :
class LightGUI : public TreeObject
{
public:
	// constrcuter destructer
	LightGUI();
	~LightGUI();

	// delete Function
	LightGUI(const LightGUI& _Other) = delete;
	LightGUI(LightGUI&& _Other) noexcept = delete;
	LightGUI& operator=(const LightGUI& _Other) = delete;
	LightGUI& operator=(LightGUI&& _Other) noexcept = delete;

protected:
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;

private:

	class ContentsLight* SelectActor = nullptr;

	void ShowLightList(GameEngineLevel* _Level);

	std::vector<std::string> ActorNames;
	std::vector<const char*> CObjectNames;
};

