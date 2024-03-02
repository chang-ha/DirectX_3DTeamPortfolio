#pragma once
#include <GameEngineCore/GameEngineActor.h>


// Ό³Έν :
class ObjectTest : public GameEngineGUIWindow
{
	// TestLevelMemeber
	int Select = 0;
	std::shared_ptr<GameEngineObject> SelectObject = nullptr;
	void Start() override;
	void OnGUI(GameEngineLevel* _Level, float _DeltaTime) override;

public:
	class TestMapObjcet* Object0 = nullptr;
	float PositionX = 0.0f;
	float PositionY = 0.0f;
	float PositionZ = 0.0f;
};

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

	float4 CameraPos1;
	
protected:
	void Start() override;
	void Update(float _Delta) override;

private:
	std::shared_ptr<GameContentsFBXRenderer> FBXRenderer;
	std::shared_ptr<ObjectTest> GUI = nullptr;
};

