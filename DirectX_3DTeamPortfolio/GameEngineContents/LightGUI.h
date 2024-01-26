#pragma once
#include "TreeWindow.h"


// ���� :
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
	void Start() override;
	void OnGUI(class GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

private:
	void ShowLightList(GameEngineLevel* _Level);
	void LightEditor();




	class ContentsLight* SelectActor = nullptr;

	std::vector<std::string> ActorNames;
	//std::vector<ContentsLight*> ActorPointer;
	std::vector<const char*> CObjectNames;
};

