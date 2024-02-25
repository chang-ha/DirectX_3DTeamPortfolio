#pragma once
#include "ContentLevel.h"

class TestLevel_MapObject : public ContentLevel
{
public:
	// constructer destructer
	TestLevel_MapObject();
	~TestLevel_MapObject();

	// delete function
	TestLevel_MapObject(const TestLevel_MapObject& _Ohter) = delete;
	TestLevel_MapObject(TestLevel_MapObject&& _Ohter) noexcept = delete;
	TestLevel_MapObject& operator=(const TestLevel_MapObject& _Other) = delete;
	TestLevel_MapObject& operator=(TestLevel_MapObject&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	

};

