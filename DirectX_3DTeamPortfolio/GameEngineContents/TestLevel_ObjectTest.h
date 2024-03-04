#pragma once
#include "ContentLevel.h"

// Ό³Έν :
class TestLevel_ObjectTest :public ContentLevel
{
public:
	// constrcuter destructer
	TestLevel_ObjectTest();
	~TestLevel_ObjectTest();

	// delete Function
	TestLevel_ObjectTest(const TestLevel_ObjectTest& _Other) = delete;
	TestLevel_ObjectTest(TestLevel_ObjectTest&& _Other) noexcept = delete;
	TestLevel_ObjectTest& operator=(const TestLevel_ObjectTest& _Other) = delete;
	TestLevel_ObjectTest& operator=(TestLevel_ObjectTest&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
private:

};

