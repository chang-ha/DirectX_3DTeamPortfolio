#pragma once
#include "ContentLevel.h"
#include <GameEngineCore\GameEnginePhysXLevel.h>
class TestLevel_PhysX : public ContentLevel
{
public:
	// constructer destructer
	TestLevel_PhysX();
	~TestLevel_PhysX();

	// delete function
	TestLevel_PhysX(const TestLevel_PhysX& _Ohter) = delete;
	TestLevel_PhysX(TestLevel_PhysX&& _Ohter) noexcept = delete;
	TestLevel_PhysX& operator=(const TestLevel_PhysX& _Other) = delete;
	TestLevel_PhysX& operator=(TestLevel_PhysX&& _Other) noexcept = delete;

	void CookingTestCode();

protected:

private:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
};

