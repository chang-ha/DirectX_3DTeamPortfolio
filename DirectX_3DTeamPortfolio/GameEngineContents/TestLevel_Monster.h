#pragma once
#include "ContentLevel.h"


// TestLevel_Monster에서만 쓰이는 GUI입니다.
class MonsterGUI : public GameEngineGUIWindow
{
	friend class TestLevel_Monster;
private:
	void Start() override {}

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
	void Release();

	void CopyAnimationName(class TestLevel_Monster* _Level);

private:
	std::vector<std::string> AnimationNames; // Store Value
	std::vector<const char*> CAnimationNames; // Use 'AnimationNames' Pointer
	int SelectItem = -1;

};


// 설명 :
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
	std::shared_ptr<MonsterGUI> MonsterWindow;
	std::shared_ptr<class MonsterEditorActor> EditorActor;

};

