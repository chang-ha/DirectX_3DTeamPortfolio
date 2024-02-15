#pragma once
#include "ContentLevel.h"

// Ό³Έν :
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


private:

};