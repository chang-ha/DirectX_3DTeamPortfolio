#pragma once
#include <GameEngineCore/GameEngineGUI.h>


class Tab
{
public:
	std::string Name;
	int Index;

	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

	Tab(std::string_view _Name)
	{
		Name = _Name;
	}
};

class TestTab : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	TestTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

class TestTabA : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	TestTabA(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

class TestTabB : public Tab
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	TestTabB(std::string_view _Name)
		: Tab(_Name)
	{
	}
};

class MapEditorTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime)
	{

	}

public:
	MapEditorTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


class LevelChangeTab : public Tab
{
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime);

public:
	LevelChangeTab(std::string_view _Name)
		: Tab(_Name)
	{
	}
};


// Ό³Έν :
class ContentsControlWindow : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

	std::shared_ptr<Tab> CurTab = nullptr;
	std::vector<std::shared_ptr<Tab>> Tabs;

};

