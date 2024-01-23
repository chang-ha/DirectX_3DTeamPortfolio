#pragma once
#include "ContentLevel.h"

class TestLevel_Boss : public ContentLevel
{
public:
	// constructer destructer
	TestLevel_Boss();
	~TestLevel_Boss();

	// delete function
	TestLevel_Boss(const TestLevel_Boss& _Ohter) = delete;
	TestLevel_Boss(TestLevel_Boss&& _Ohter) noexcept = delete;
	TestLevel_Boss& operator=(const TestLevel_Boss& _Other) = delete;
	TestLevel_Boss& operator=(TestLevel_Boss&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<class Boss_Vordt> Boss_Object;
	std::shared_ptr<class ContentsLight> Test_Light;
	std::shared_ptr<class TestObject> TestObj;
};

