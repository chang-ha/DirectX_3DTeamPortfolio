#pragma once
#include "TreeWindow.h"

// Ό³Έν :
class MonsterInfoGUI : public TreeObject
{
public:
	// constrcuter destructer
	MonsterInfoGUI();
	~MonsterInfoGUI();

	// delete Function
	MonsterInfoGUI(const MonsterInfoGUI& _Other) = delete;
	MonsterInfoGUI(MonsterInfoGUI&& _Other) noexcept = delete;
	MonsterInfoGUI& operator=(const MonsterInfoGUI& _Other) = delete;
	MonsterInfoGUI& operator=(MonsterInfoGUI&& _Other) noexcept = delete;

	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	void LevelEnd() override;

protected:
	void SelectMonsterList(GameEngineLevel* _Level);
	void MonsterInfo();

private:
	class GameEngineLevel* CurLevel = nullptr;

	std::vector<std::string> LevelActorList;
	std::vector<const char*> CLevelActorList;
	int SelectActorIndex = -1;

	class BaseMonster* pMonster = nullptr;

	float4 MonsterPos = float4::ZERO;	
	float4 MonsterScale = float4(100.0f, 100.0f, 100.0f);

	bool bFixPos = false;
	bool bPause = false;

};

