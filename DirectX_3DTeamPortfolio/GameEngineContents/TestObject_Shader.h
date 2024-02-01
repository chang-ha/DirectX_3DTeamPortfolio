#pragma once
#include"BaseMonster.h"

// Ό³Έν :
class TestObject_Shader : public BaseMonster
{
public:
	// constrcuter destructer
	TestObject_Shader();
	~TestObject_Shader();

	// delete Function
	TestObject_Shader(const TestObject_Shader& _Other) = delete;
	TestObject_Shader(TestObject_Shader&& _Other) noexcept = delete;
	TestObject_Shader& operator=(const TestObject_Shader& _Other) = delete;
	TestObject_Shader& operator=(TestObject_Shader&& _Other) noexcept = delete;


	std::shared_ptr<GameContentsFBXRenderer> GetMainRenderer()
	{
		return MainRenderer;
	}
	//std::map<int, std::shared_ptr<BoneSocketCollision>> Collisions;

protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
	void LevelStart(class GameEngineLevel* _NextLevel) override {}
	void LevelEnd(class GameEngineLevel* _NextLevel) override;
private:


	std::shared_ptr<class GameEngineUIRenderer> HpBar;



};

