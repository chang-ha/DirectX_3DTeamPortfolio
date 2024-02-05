#pragma once
#include "ContentLevel.h"

class TestLevel_Monster;
class MonsterGUITab
{
	friend class MonsterGUI;

public:
	void Init(MonsterGUI* _GUI);
	virtual void Start() {}
	virtual void OnGUI(GameEngineLevel* _Level, float _DeltaTime) = 0;

protected:
	std::string Name;
	class MonsterGUI* pParentGUI = nullptr;

};

class DummyTab : public MonsterGUITab
{
private:
	void Start() override {}
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

private:
	class DummyActor* pActor = nullptr;

	bool IsUpdate = false;
	bool bCameraFocus = false;

};


class MonsterGUI : public GameEngineGUIWindow
{
public:
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;


	TestLevel_Monster* GetLevel() { return CurLevel; }

private:
	template<typename ObjectType>
	void CreateTab(std::string_view _TabName)
	{
		std::shared_ptr<ObjectType> NewTab = std::make_shared<ObjectType>();
		NewTab->Name = _TabName.data();
		NewTab->Init(this);
		Tabs.push_back(NewTab);
	}

private:
	std::vector<std::shared_ptr<MonsterGUITab>> Tabs;
	TestLevel_Monster* CurLevel = nullptr;

	float DummySpeed = 0.0f;

};

// ���� :
class TestLevel_Monster : public ContentLevel
{
	friend class MonsterGUI;

public:
	// constrcuter destructer
	TestLevel_Monster();
	~TestLevel_Monster();

	// delete Function
	TestLevel_Monster(const TestLevel_Monster& _Other) = delete;
	TestLevel_Monster(TestLevel_Monster&& _Other) noexcept = delete;
	TestLevel_Monster& operator=(const TestLevel_Monster& _Other) = delete;
	TestLevel_Monster& operator=(TestLevel_Monster&& _Other) noexcept = delete;

	class DummyActor* GetDummyActorPointer() const;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;


	template<typename ObjectType, typename OrderType>
	void AllDeathObjectGroupConvert(OrderType _Order)
	{
		std::vector<std::shared_ptr<ObjectType>> Objects = GetObjectGroupConvert<ObjectType>(_Order);
		for (const std::shared_ptr<ObjectType>& ObjectPointer : Objects)
		{
			ObjectPointer->Death();
		}

		if (bool OutputMsg = true)
		{
			OutputDebugStringA((std::to_string(Objects.size()) + "\t" + std::string(typeid(ObjectType).name()) + " have been released. \n").c_str());
		}
	}

private:
	std::shared_ptr<MonsterGUI> pMonsterGUI;
	std::shared_ptr<class DummyActor> pDummyActor;

};

