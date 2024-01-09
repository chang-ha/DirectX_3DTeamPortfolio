#pragma once
#include "ContentLevel.h"

class TestLevel_Shader : public ContentLevel
{
public:
	// constrcuter destructer
	TestLevel_Shader();
	~TestLevel_Shader();

	// delete Function
	TestLevel_Shader(const TestLevel_Shader& _Other) = delete;
	TestLevel_Shader(TestLevel_Shader&& _Other) noexcept = delete;
	TestLevel_Shader& operator=(const TestLevel_Shader& _Other) = delete;
	TestLevel_Shader& operator=(TestLevel_Shader&& _Other) noexcept = delete;

protected:
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;

	void Start() override;
	void Update(float _Delta) override;
	void Release() override;

private:
	std::shared_ptr<class Monster_HollowSoldier> HollowSoldier;
	std::shared_ptr<class ContentsLight> Test_Light1;
	//std::shared_ptr<class Boss_Vordt> Boss_Object;
};

