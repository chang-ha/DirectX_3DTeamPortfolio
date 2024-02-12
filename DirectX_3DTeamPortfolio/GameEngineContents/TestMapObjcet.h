#pragma once
#include <GameEngineCore/GameEngineActor.h>

// Ό³Έν :
class TestMapObjcet : public GameEngineActor
{
public:
	// constrcuter destructer
	TestMapObjcet();
	~TestMapObjcet();

	// delete Function
	TestMapObjcet(const TestMapObjcet& _Other) = delete;
	TestMapObjcet(TestMapObjcet&& _Other) noexcept = delete;
	TestMapObjcet& operator=(const TestMapObjcet& _Other) = delete;
	TestMapObjcet& operator=(TestMapObjcet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
};

