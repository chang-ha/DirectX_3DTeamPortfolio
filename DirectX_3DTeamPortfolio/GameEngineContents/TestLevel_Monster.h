#pragma once


class MonsterGUI : public GameEngineGUIWindow
{
private:
	void Start() override {}

	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;
};


// Ό³Έν :
class TestLevel_Monster : public GameEngineLevel
{
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
	void AllDeathChildObjects(OrderType _Order)
	{
		std::vector<std::shared_ptr<ObjectType>> Objects = GetObjectGroupConvert<ObjectType>(_Order);
		for (const std::shared_ptr<ObjectType>& ObjectPointer : Objects)
		{
			ObjectPointer->Death();
		}

		if (bool OutputMsg = true)
		{
			OutputDebugStringA((std::string(typeid(ObjectType).name()) + " is Death. \n").c_str());
		}
	}

private:
	std::shared_ptr<MonsterGUI> MonsterWindow;

};

