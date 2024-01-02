#pragma once
#include "ContentLevel.h"

class TestLevel_Map : public ContentLevel
{
public:
	// constructer destructer
	TestLevel_Map();
	~TestLevel_Map();

	// delete function
	TestLevel_Map(const TestLevel_Map& _Ohter) = delete;
	TestLevel_Map(TestLevel_Map&& _Ohter) noexcept = delete;
	TestLevel_Map& operator=(const TestLevel_Map& _Other) = delete;
	TestLevel_Map& operator=(TestLevel_Map&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	

};

